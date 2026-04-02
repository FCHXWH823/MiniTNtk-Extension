#include "MustNetCNF.h"
#include <cmath>
#include <chrono>
#include <queue>

// ==================== Constructor / Destructor ====================

MustNetCNF::MustNetCNF()
	: nCnfVars(0), nInputs(0), SatResult(0), AccTech1Flag(1), AccTech2Flag(1), placementFlag(0), DepthLimited(0), K(0), MaxDepth(0) {}

MustNetCNF::MustNetCNF(MustNetNtk Ntk)
	: ntk(Ntk), nCnfVars(0), nInputs(0), SatResult(0), AccTech1Flag(1), AccTech2Flag(1), placementFlag(0), DepthLimited(0), K(0), MaxDepth(0) {}

MustNetCNF::~MustNetCNF() {}

// ==================== Clause Helpers ====================

void MustNetCNF::CreateORClause(vector<int> cnfvars) {
	clauses.push_back(cnfvars);
}

void MustNetCNF::CreateAtMostOneClause(vector<int> cnfvars) {
	for (int i = 0; i < (int)cnfvars.size() - 1; i++)
		for (int j = i + 1; j < (int)cnfvars.size(); j++)
			clauses.push_back({-cnfvars[i], -cnfvars[j]});
}

void MustNetCNF::CreateXNORClause(vector<int> cnfvars1, vector<int> cnfvars2) {
	// v1 → (∨ cnfvars2)  for each v1
	for (auto v1 : cnfvars1) {
		vector<int> clause = cnfvars2;
		clause.push_back(-v1);
		clauses.push_back(clause);
	}
	// v2 → (∨ cnfvars1)  for each v2
	for (auto v2 : cnfvars2) {
		vector<int> clause = cnfvars1;
		clause.push_back(-v2);
		clauses.push_back(clause);
	}
}

// ==================== Input Parsing ====================
// (Replicates TransistorCNF::InputParser and DeriveRepPattern)

void MustNetCNF::InputParser(string onFunc, string offFunc) {
	removeSpace(onFunc);
	removeSpace(offFunc);

	vector<string> onProducts  = (onFunc.size())  ? split(onFunc,  '+') : vector<string>{};
	vector<string> offProducts = (offFunc.size()) ? split(offFunc, '+') : vector<string>{};
	vector<vector<string>> vOnProducts, vOffProducts;
	set<char> vars;
	map<char, int> VarId;

	for (auto s : onProducts)  vOnProducts.push_back(split(s, '*'));
	for (auto s : offProducts) vOffProducts.push_back(split(s, '*'));

	// Derive variables and literal polarity from ON products
	for (auto& product : vOnProducts) {
		for (auto& literal : product) {
			if (literal[0] == '!') {
				vars.insert(literal[1]);
				VarId[literal[1]] |= 1;   // negative polarity seen
			} else {
				vars.insert(literal[0]);
				VarId[literal[0]] |= 2;   // positive polarity seen
			}
		}
	}
	for (auto var : vars) svars += var;

	nInputs = vars.size();
	VarIndPos.resize(nInputs, 0);
	VarIndNeg.resize(nInputs, 0);
	for (int i = 0; i < (int)svars.size(); i++) {
		char c = svars[i];
		assert(VarId[c] != 0);
		if (VarId[c] & 0b01) VarIndNeg[i] = 1;
		if (VarId[c] & 0b10) VarIndPos[i] = 1;
		VarId[c] = i;
	}

	Onsets  = DeriveFunc(vOnProducts,  VarId);
	Offsets = DeriveFunc(vOffProducts, VarId);

	DeriveRepPattern(1); // positive patterns
	DeriveRepPattern(0); // negative patterns
}

vector<vector<int>> MustNetCNF::DeriveFunc(
	vector<vector<string>> vProducts, map<char, int> VarId)
{
	vector<vector<int>> vFunc;
	for (auto& product : vProducts) {
		vector<int> func;
		for (auto& literal : product) {
			if (literal[0] == '!')
				func.push_back(nInputs + VarId[literal[1]]);
			else
				func.push_back(VarId[literal[0]]);
		}
		if (find(vFunc.begin(), vFunc.end(), func) == vFunc.end())
			vFunc.push_back(func);
	}
	return vFunc;
}

void MustNetCNF::DeriveRepPattern(int flag) {
	unsigned unate = 0;
	if (AccTech1Flag) {
		for (int i = 0; i < nInputs; i++)
			if (VarIndPos[i] + VarIndNeg[i] == 1)
				unate |= (1 << i);
	}
	vector<vector<int>> sets = (flag) ? Onsets : Offsets;
	for (auto& onProduct : sets) {
		vector<vector<int>> patterns;
		vector<int> pattern(nInputs, 2);
		for (auto literal : onProduct) {
			int var = (literal >= nInputs) ? literal - nInputs : literal;
			pattern[var] = (literal >= nInputs) ? 0 : 1;
		}
		patterns.push_back(vector<int>(nInputs, 0));
		for (int i = 0; i < (int)pattern.size(); i++) {
			int nPa = patterns.size();
			for (int j = 0; j < nPa; j++) {
				if (pattern[i] != 2)
					patterns[j][i] = pattern[i];
				else {
					if (unate & (1 << i)) {
						if (VarIndPos[i] == 0 && VarIndNeg[i] == 1)
							patterns[j][i] = (flag) ? 1 : 0;
						else if (VarIndPos[i] == 1 && VarIndNeg[i] == 0)
							patterns[j][i] = (flag) ? 0 : 1;
						else
							assert(0);
					} else {
						patterns[j][i] = 0;
						vector<int> tmp = patterns[j];
						tmp[i] = 1;
						patterns.push_back(tmp);
					}
				}
			}
		}
		if (flag) {
			PosRepPattern.insert(PosRepPattern.end(), patterns.begin(), patterns.end());
			sort(PosRepPattern.begin(), PosRepPattern.end());
			auto last = unique(PosRepPattern.begin(), PosRepPattern.end());
			PosRepPattern.erase(last, PosRepPattern.end());
		} else {
			NegRepPattern.insert(NegRepPattern.end(), patterns.begin(), patterns.end());
			sort(NegRepPattern.begin(), NegRepPattern.end());
			auto last = unique(NegRepPattern.begin(), NegRepPattern.end());
			NegRepPattern.erase(last, NegRepPattern.end());
		}
	}
}

// ==================== SAT Variable Allocation ====================

void MustNetCNF::InitVars() {
	int T      = ntk.T;
	int nNets  = T + 1;
	int nPairs = ntk.nPairs();
	int nPos   = PosRepPattern.size();
	int nNeg   = NegRepPattern.size();
	int nPat   = nPos + nNeg;

	nCnfVars = 0;

	// 1. gateVar[m][l]  (only for existing literals)
	gateVar.resize(T);
	for (int m = 0; m < T; m++) {
		gateVar[m].assign(2 * nInputs, 0);
		for (int l = 0; l < nInputs; l++) {
			if (VarIndPos[l]) { nCnfVars++; gateVar[m][l] = nCnfVars; }
		}
		for (int l = 0; l < nInputs; l++) {
			if (VarIndNeg[l]) { nCnfVars++; gateVar[m][nInputs + l] = nCnfVars; }
		}
	}

	// 2. epVar[m][pair_idx]
	epVar.resize(T);
	for (int m = 0; m < T; m++) {
		epVar[m].resize(nPairs);
		for (int p = 0; p < nPairs; p++) {
			nCnfVars++;
			epVar[m][p] = nCnfVars;
		}
	}

	// 3. onVar[m][p]  (all patterns: pos + neg)
	onVar.resize(T);
	for (int m = 0; m < T; m++) {
		onVar[m].resize(nPat);
		for (int p = 0; p < nPat; p++) {
			nCnfVars++;
			onVar[m][p] = nCnfVars;
		}
	}

	// 4. flowL / flowR  (positive patterns only)
	flowL.resize(nPairs);
	flowR.resize(nPairs);
	for (int pi = 0; pi < nPairs; pi++) {
		flowL[pi].resize(nPos);
		flowR[pi].resize(nPos);
		for (int p = 0; p < nPos; p++) {
			nCnfVars++; flowL[pi][p] = nCnfVars;
			nCnfVars++; flowR[pi][p] = nCnfVars;
		}
	}

	// 5. epOn[m][pair_idx][p]  (positive patterns only)
	epOn.resize(T);
	for (int m = 0; m < T; m++) {
		epOn[m].resize(nPairs);
		for (int pi = 0; pi < nPairs; pi++) {
			epOn[m][pi].resize(nPos);
			for (int p = 0; p < nPos; p++) {
				nCnfVars++;
				epOn[m][pi][p] = nCnfVars;
			}
		}
	}

	// 6. label[net][neg_pat_idx]  (negative patterns only)
	label.resize(nNets);
	for (int n = 0; n < nNets; n++) {
		label[n].resize(nNeg);
		for (int p = 0; p < nNeg; p++) {
			nCnfVars++;
			label[n][p] = nCnfVars;
		}
	}

	// === Placement variables (Phase 2) ===
	if (placementFlag) {
		// 7. tpVar[m][j][f]: MOS m at column j with flip f
		tpVar.resize(T);
		for (int m = 0; m < T; m++) {
			tpVar[m].resize(T);
			for (int j = 0; j < T; j++) {
				tpVar[m][j].resize(2);
				for (int f = 0; f < 2; f++) {
					nCnfVars++;
					tpVar[m][j][f] = nCnfVars;
				}
			}
		}

		// 8. leftDiff[j][n]: left diffusion of column j is net n
		leftDiff.resize(T);
		for (int j = 0; j < T; j++) {
			leftDiff[j].resize(nNets);
			for (int n = 0; n < nNets; n++) {
				nCnfVars++;
				leftDiff[j][n] = nCnfVars;
			}
		}

		// 9. rightDiff[j][n]: right diffusion of column j is net n
		rightDiff.resize(T);
		for (int j = 0; j < T; j++) {
			rightDiff[j].resize(nNets);
			for (int n = 0; n < nNets; n++) {
				nCnfVars++;
				rightDiff[j][n] = nCnfVars;
			}
		}
	}
}

// ==================== Constraint Generation ====================

// C1: Each MOS gets exactly one gate literal
void MustNetCNF::CreateGateAssignClauses() {
	for (int m = 0; m < ntk.T; m++) {
		vector<int> litVars;
		for (int l = 0; l < 2 * nInputs; l++)
			if (gateVar[m][l] != 0)
				litVars.push_back(gateVar[m][l]);
		CreateORClause(litVars);
		CreateAtMostOneClause(litVars);
	}
}

// C2: Each MOS connects exactly one net pair
void MustNetCNF::CreateEndpointAssignClauses() {
	int nPairs = ntk.nPairs();
	for (int m = 0; m < ntk.T; m++) {
		vector<int> pairVars;
		for (int p = 0; p < nPairs; p++)
			pairVars.push_back(epVar[m][p]);
		CreateORClause(pairVars);
		CreateAtMostOneClause(pairVars);
	}
}

// C3: Derive onVar from gate assignment and input pattern
void MustNetCNF::CreateConductivityClauses() {
	int nPos = PosRepPattern.size();
	int nNeg = NegRepPattern.size();

	// Positive patterns
	for (int iP = 0; iP < nPos; iP++) {
		for (int m = 0; m < ntk.T; m++) {
			vector<int> cnfvars;
			for (int i = 0; i < nInputs; i++) {
				if (PosRepPattern[iP][i]) {
					if (VarIndPos[i]) cnfvars.push_back(gateVar[m][i]);
				} else {
					if (VarIndNeg[i]) cnfvars.push_back(gateVar[m][nInputs + i]);
				}
			}
			CreateXNORClause(cnfvars, {onVar[m][iP]});
		}
	}

	// Negative patterns
	for (int iN = 0; iN < nNeg; iN++) {
		int patIdx = nPos + iN;
		for (int m = 0; m < ntk.T; m++) {
			vector<int> cnfvars;
			for (int i = 0; i < nInputs; i++) {
				if (NegRepPattern[iN][i]) {
					if (VarIndPos[i]) cnfvars.push_back(gateVar[m][i]);
				} else {
					if (VarIndNeg[i]) cnfvars.push_back(gateVar[m][nInputs + i]);
				}
			}
			CreateXNORClause(cnfvars, {onVar[m][patIdx]});
		}
	}
}

// C4: Auxiliary  epOn[m][pi][p] = epVar[m][pi] AND onVar[m][p]
void MustNetCNF::CreateAuxEpOnClauses() {
	int nPos   = PosRepPattern.size();
	int nPairs = ntk.nPairs();

	for (int m = 0; m < ntk.T; m++) {
		for (int pi = 0; pi < nPairs; pi++) {
			for (int p = 0; p < nPos; p++) {
				int aux = epOn[m][pi][p];
				int ep  = epVar[m][pi];
				int on  = onVar[m][p];
				clauses.push_back({-aux, ep});       // aux → ep
				clauses.push_back({-aux, on});       // aux → on
				clauses.push_back({-ep, -on, aux});  // ep ∧ on → aux
			}
		}
	}
}

// C5: Flow constraints for positive (ON) patterns
void MustNetCNF::CreateFlowClauses() {
	int T      = ntk.T;
	int nNets  = T + 1;
	int nPos   = PosRepPattern.size();
	int nPairs = ntk.nPairs();

	for (int iP = 0; iP < nPos; iP++) {

		// --- Flow implies active edge ---
		for (int pi = 0; pi < nPairs; pi++) {
			// flowL → ∨_m epOn[m][pi][iP]
			vector<int> clauseL = {-flowL[pi][iP]};
			vector<int> clauseR = {-flowR[pi][iP]};
			for (int m = 0; m < T; m++) {
				clauseL.push_back(epOn[m][pi][iP]);
				clauseR.push_back(epOn[m][pi][iP]);
			}
			clauses.push_back(clauseL);
			clauses.push_back(clauseR);

			// At most one direction per virtual edge
			clauses.push_back({-flowL[pi][iP], -flowR[pi][iP]});
		}

		// --- Source (net 0): exactly one outgoing, no incoming ---
		{
			vector<int> outVars;
			for (int j = 1; j < nNets; j++) {
				int pi = ntk.pairIndex(0, j);
				outVars.push_back(flowL[pi][iP]);
			}
			CreateORClause(outVars);
			CreateAtMostOneClause(outVars);

			// Forbid incoming to source
			for (int j = 1; j < nNets; j++) {
				int pi = ntk.pairIndex(0, j);
				clauses.push_back({-flowR[pi][iP]});
			}
		}

		// --- Output (net T): at least one incoming, no outgoing ---
		{
			vector<int> inVars;
			for (int i = 0; i < T; i++) {
				int pi = ntk.pairIndex(i, T);
				inVars.push_back(flowL[pi][iP]);
			}
			CreateORClause(inVars);

			// Forbid outgoing from output
			for (int i = 0; i < T; i++) {
				int pi = ntk.pairIndex(i, T);
				clauses.push_back({-flowR[pi][iP]});
			}
		}

		// --- Internal nets (1..T-1): flow conservation ---
		for (int n = 1; n < T; n++) {
			vector<int> inVars, outVars;

			// Incoming to net n:
			//   flowL[pair(i,n)] for i < n  (flow from i to n)
			//   flowR[pair(n,j)] for j > n  (flow from j to n)
			for (int i = 0; i < n; i++) {
				int pi = ntk.pairIndex(i, n);
				inVars.push_back(flowL[pi][iP]);
			}
			for (int j = n + 1; j < nNets; j++) {
				int pi = ntk.pairIndex(n, j);
				inVars.push_back(flowR[pi][iP]);
			}

			// Outgoing from net n:
			//   flowR[pair(i,n)] for i < n  (flow from n to i)
			//   flowL[pair(n,j)] for j > n  (flow from n to j)
			for (int i = 0; i < n; i++) {
				int pi = ntk.pairIndex(i, n);
				outVars.push_back(flowR[pi][iP]);
			}
			for (int j = n + 1; j < nNets; j++) {
				int pi = ntk.pairIndex(n, j);
				outVars.push_back(flowL[pi][iP]);
			}

			CreateAtMostOneClause(inVars);
			CreateAtMostOneClause(outVars);
			CreateXNORClause(inVars, outVars);
		}
	}
}

// C6: Separation constraints for negative (OFF) patterns
void MustNetCNF::CreateSeparationClauses() {
	int T      = ntk.T;
	int nPos   = PosRepPattern.size();
	int nNeg   = NegRepPattern.size();
	int nPairs = ntk.nPairs();

	for (int iN = 0; iN < nNeg; iN++) {
		int patIdx = nPos + iN;   // index into onVar

		// Fix source label = 0 (FALSE), output label = 1 (TRUE)
		clauses.push_back({-label[0][iN]});
		clauses.push_back({ label[T][iN]});

		// For each MOS m and pair (i,j):
		//   ep[m][pair] ∧ on[m][patIdx] → label[i] = label[j]
		for (int m = 0; m < T; m++) {
			for (int pi = 0; pi < nPairs; pi++) {
				int net_i = ntk.allPairs[pi].first;
				int net_j = ntk.allPairs[pi].second;
				clauses.push_back({-epVar[m][pi], -onVar[m][patIdx],
					-label[net_i][iN],  label[net_j][iN]});
				clauses.push_back({-epVar[m][pi], -onVar[m][patIdx],
					 label[net_i][iN], -label[net_j][iN]});
			}
		}
	}
}

// ==================== Placement Constraints (Phase 2) ====================

// C7: Each MOS m is placed at exactly one (column j, flip f)
void MustNetCNF::CreateTransistorAllocClauses() {
	int T = ntk.T;
	for (int m = 0; m < T; m++) {
		vector<int> allOpts;
		for (int j = 0; j < T; j++)
			for (int f = 0; f < 2; f++)
				allOpts.push_back(tpVar[m][j][f]);
		CreateORClause(allOpts);
		CreateAtMostOneClause(allOpts);
	}
}

// C8: Each column j is occupied by exactly one (MOS m, flip f)
void MustNetCNF::CreateColumnAllocClauses() {
	int T = ntk.T;
	for (int j = 0; j < T; j++) {
		vector<int> allOpts;
		for (int m = 0; m < T; m++)
			for (int f = 0; f < 2; f++)
				allOpts.push_back(tpVar[m][j][f]);
		CreateORClause(allOpts);
		CreateAtMostOneClause(allOpts);
	}
}

// C9: Link tpVar + epVar to leftDiff / rightDiff
//   flip=0 (D-G-S): left = lower net (i), right = higher net (k)
//   flip=1 (S-G-D): left = higher net (k), right = lower net (i)
//   Plus ExactlyOne constraint on leftDiff[j] and rightDiff[j]
void MustNetCNF::CreateDiffLinkClauses() {
	int T     = ntk.T;
	int nNets = T + 1;
	int nPairs = ntk.nPairs();

	// Forward implications: tp(m,j,f) ∧ ep(m,pi) → leftDiff/rightDiff
	for (int j = 0; j < T; j++) {
		for (int m = 0; m < T; m++) {
			for (int pi = 0; pi < nPairs; pi++) {
				int net_i = ntk.allPairs[pi].first;   // lower
				int net_k = ntk.allPairs[pi].second;   // higher

				// flip=0: left = net_i, right = net_k
				clauses.push_back({-tpVar[m][j][0], -epVar[m][pi], leftDiff[j][net_i]});
				clauses.push_back({-tpVar[m][j][0], -epVar[m][pi], rightDiff[j][net_k]});

				// flip=1: left = net_k, right = net_i
				clauses.push_back({-tpVar[m][j][1], -epVar[m][pi], leftDiff[j][net_k]});
				clauses.push_back({-tpVar[m][j][1], -epVar[m][pi], rightDiff[j][net_i]});
			}
		}
	}

	// ExactlyOne for leftDiff[j] and rightDiff[j]
	for (int j = 0; j < T; j++) {
		vector<int> leftVars, rightVars;
		for (int n = 0; n < nNets; n++) {
			leftVars.push_back(leftDiff[j][n]);
			rightVars.push_back(rightDiff[j][n]);
		}
		CreateORClause(leftVars);
		CreateAtMostOneClause(leftVars);
		CreateORClause(rightVars);
		CreateAtMostOneClause(rightVars);
	}
}

// C10: Diffusion sharing — right of column j must equal left of column j+1
void MustNetCNF::CreateDiffusionSharingClauses() {
	int T     = ntk.T;
	int nNets = T + 1;

	for (int j = 0; j < T - 1; j++) {
		for (int n = 0; n < nNets; n++) {
			// rightDiff[j][n] → leftDiff[j+1][n]
			clauses.push_back({-rightDiff[j][n], leftDiff[j+1][n]});
			// leftDiff[j+1][n] → rightDiff[j][n]
			clauses.push_back({-leftDiff[j+1][n], rightDiff[j][n]});
		}
	}
}

// Calls all placement constraints (C7–C10)
void MustNetCNF::CreatePlacementClauses() {
	CreateTransistorAllocClauses();
	CreateColumnAllocClauses();
	CreateDiffLinkClauses();
	CreateDiffusionSharingClauses();
}

// Pre-assign known literals to the first few MOS (acceleration technique 2)
vector<int> MustNetCNF::CreatePriorClauses() {
	vector<int> VarInputIds;
	for (int i = 0; i < (int)VarIndPos.size(); i++)
		if (VarIndPos[i]) VarInputIds.push_back(i);
	for (int i = 0; i < (int)VarIndNeg.size(); i++)
		if (VarIndNeg[i]) VarInputIds.push_back(i + nInputs);

	for (int m = 0; m < ntk.T && m < (int)VarInputIds.size(); m++) {
		for (int l = 0; l < 2 * nInputs; l++) {
			if (gateVar[m][l] == 0) continue;
			if (l == VarInputIds[m])
				clauses.push_back({ gateVar[m][l]});
			else
				clauses.push_back({-gateVar[m][l]});
		}
	}
	return VarInputIds;
}

// ==================== Depth-Limited Path Constraints ====================

static void mustnetCombinationsHelper(vector<int>& nums, int start, int n, vector<int>& combination, vector<vector<int>>& result) {
	if (n == 0) {
		result.push_back(combination);
		return;
	}
	for (int i = start; i <= (int)nums.size() - n; i++) {
		combination.push_back(nums[i]);
		mustnetCombinationsHelper(nums, i + 1, n - 1, combination, result);
		combination.pop_back();
	}
}

static vector<vector<int>> mustnetCombinations(vector<int>& nums, int n) {
	vector<vector<int>> result;
	vector<int> combination;
	mustnetCombinationsHelper(nums, 0, n, combination, result);
	return result;
}

void MustNetCNF::CreateAtMostKClause(vector<int> cnfvars, int K) {
	if (K < (int)cnfvars.size()) {
		vector<vector<int>> vCnfvars = mustnetCombinations(cnfvars, K + 1);
		for (int j = 0; j < (int)vCnfvars.size(); j++) {
			for (int k = 0; k < (int)vCnfvars[j].size(); k++)
				vCnfvars[j][k] = -vCnfvars[j][k];
			clauses.push_back(vCnfvars[j]);
		}
	}
}

void MustNetCNF::CreateKLimitedPathConstraints(int K) {
	int nPos = PosRepPattern.size();
	int nPairs = ntk.nPairs();
	for (int iP = 0; iP < nPos; iP++) {
		vector<int> FlowCnfVars;
		for (int pi = 0; pi < nPairs; pi++) {
			FlowCnfVars.push_back(flowL[pi][iP]);
			FlowCnfVars.push_back(flowR[pi][iP]);
		}
		CreateAtMostKClause(FlowCnfVars, K);
	}
}

// Generates all constraints in order
void MustNetCNF::CreateAllClauses() {
	CreateGateAssignClauses();
	CreateEndpointAssignClauses();
	CreateConductivityClauses();
	CreateAuxEpOnClauses();
	CreateFlowClauses();
	CreateSeparationClauses();
	if (DepthLimited) {
		K = getK();
		CreateKLimitedPathConstraints(K);
	}
	if (placementFlag)
		CreatePlacementClauses();
}

// ==================== CNF Writing ====================

void MustNetCNF::WriteCnf(string cnfpath) {
	ofstream fCnf;
	fCnf.open(cnfpath.c_str());
	fCnf << "p cnf " << nCnfVars << " " << clauses.size() << endl;
	for (auto& clause : clauses) {
		for (auto v : clause) fCnf << v << " ";
		fCnf << "0" << endl;
	}
	fCnf.close();
}

// ==================== Blocking ====================

void MustNetCNF::CreateBlockClause(vector<int> vals) {
	vector<int> clause;
	// Block the current gate + endpoint assignment
	for (int m = 0; m < ntk.T; m++) {
		for (int l = 0; l < 2 * nInputs; l++) {
			if (gateVar[m][l] == 0) continue;
			int var = gateVar[m][l];
			clause.push_back(vals[var - 1] ? -var : var);
		}
	}
	for (int m = 0; m < ntk.T; m++) {
		for (int pi = 0; pi < ntk.nPairs(); pi++) {
			int var = epVar[m][pi];
			clause.push_back(vals[var - 1] ? -var : var);
		}
	}
	clauses.push_back(clause);
}

// ==================== CNF Parsing ====================

vector<string> MustNetCNF::ParseCnf(int mos, vector<transistor>& Transistors,
	int OutINV, string cnfpath, string dir)
{
	ifstream fCnf;
	string sline;
	stringstream ss;
	vector<string> Literals;

	fCnf.open(cnfpath.c_str());
	getline(fCnf, sline);
	if (sline != "SAT") {
		cout << "UNSAT" << endl;
		SatResult = 0;
		fCnf.close();
		return Literals;
	}

	SatResult = 1;
	vector<int> vals;
	getline(fCnf, sline);
	ss << sline;
	int val;
	while (ss >> val) {
		if (val > 0) vals.push_back(1);
		if (val < 0) vals.push_back(0);
	}
	fCnf.close();

	int T     = ntk.T;
	int nNets = T + 1;

	// Net names
	vector<string> netNames(nNets);
	for (int n = 0; n < nNets; n++) {
		if (n == 0)
			netNames[n] = (mos) ? "VCC" : "GND";
		else if (n == T)
			netNames[n] = (OutINV) ? "INVY" : "Y";
		else
			netNames[n] = ((mos) ? "pN" : "nN") + to_string(n);
	}

	// Extract each MOS assignment
	vector<pair<pair<int,int>, string>> transistor_pairs;
	for (int m = 0; m < T; m++) {
		// Gate literal
		string gateLit;
		for (int l = 0; l < 2 * nInputs; l++) {
			if (gateVar[m][l] == 0) continue;
			if (vals[gateVar[m][l] - 1]) {
				if (l >= nInputs)
					gateLit = "!" + string(1, svars[l - nInputs]);
				else
					gateLit = string(1, svars[l]);
				break;
			}
		}
		Literals.push_back(gateLit);

		// Endpoint pair
		int net_i = -1, net_j = -1;
		for (int pi = 0; pi < ntk.nPairs(); pi++) {
			if (vals[epVar[m][pi] - 1]) {
				net_i = ntk.allPairs[pi].first;
				net_j = ntk.allPairs[pi].second;
				break;
			}
		}
		if (net_i >= 0 && net_j >= 0)
			transistor_pairs.push_back({{net_i, net_j}, gateLit});
	}

	// Display result
	cout << "[MuSTNet] Result:" << endl;
	for (auto& tp : transistor_pairs) {
		cout << "  MOS: net" << tp.first.first
			 << " -- [" << tp.second
			 << "] -- net" << tp.first.second << endl;
	}

	// Print CG format for comparison with MiniTNtk
	{
		ostringstream oss;
		oss << "CG(nc=" << nNets << ", r=" << transistor_pairs.size() << ", tr=[";
		for (int i = 0; i < (int)transistor_pairs.size(); i++) {
			int n1 = transistor_pairs[i].first.first;
			int n2 = transistor_pairs[i].first.second;
			const string& lit = transistor_pairs[i].second;
			int litIdx;
			if (lit[0] == '!')
				litIdx = nInputs + (int)(svars.find(lit[1]));
			else
				litIdx = (int)(svars.find(lit[0]));
			oss << "(" << n1 << ", " << n2 << ", " << litIdx << ")";
			if (i + 1 < (int)transistor_pairs.size()) oss << ", ";
		}
		oss << "])";
		CGString = oss.str();
		cout << CGString << endl;
	}

	// Display placement result if placement was enabled
	if (placementFlag && !tpVar.empty()) {
		cout << "[MuSTNet] Placement (column order):" << endl;
		for (int j = 0; j < T; j++) {
			for (int m = 0; m < T; m++) {
				for (int f = 0; f < 2; f++) {
					if (vals[tpVar[m][j][f] - 1]) {
						int net_i = -1, net_k = -1;
						for (int pi = 0; pi < ntk.nPairs(); pi++) {
							if (vals[epVar[m][pi] - 1]) {
								net_i = ntk.allPairs[pi].first;
								net_k = ntk.allPairs[pi].second;
								break;
							}
						}
						string leftNet, rightNet;
						if (f == 0) {
							leftNet  = (net_i >= 0) ? netNames[net_i] : "?";
							rightNet = (net_k >= 0) ? netNames[net_k] : "?";
						} else {
							leftNet  = (net_k >= 0) ? netNames[net_k] : "?";
							rightNet = (net_i >= 0) ? netNames[net_i] : "?";
						}
						cout << "  Col " << j << ": MOS" << m
							 << " [" << transistor_pairs[m].second << "]"
							 << " flip=" << f
							 << " (" << leftNet << " | G | " << rightNet << ")"
							 << endl;
					}
				}
			}
		}
	}

	// Build adjacency for DFS path-length computation
	vector<vector<pair<int,int>>> adj(nNets);
	for (int i = 0; i < (int)transistor_pairs.size(); i++) {
		int ni = transistor_pairs[i].first.first;
		int nj = transistor_pairs[i].first.second;
		adj[ni].push_back({nj, i});
		adj[nj].push_back({ni, i});
	}

	// DFS to find all source→output paths
	map<int, int> mosMaxPathLen;
	vector<vector<int>> allPaths;
	vector<bool> visited(nNets, false);
	vector<int> currentPath;

	function<void(int)> dfs = [&](int node) {
		visited[node] = true;
		if (node == T) {
			allPaths.push_back(currentPath);
			visited[node] = false;
			return;
		}
		for (auto& [next, mosIdx] : adj[node]) {
			if (!visited[next]) {
				currentPath.push_back(mosIdx);
				dfs(next);
				currentPath.pop_back();
			}
		}
		visited[node] = false;
	};
	dfs(0);

	for (auto& path : allPaths)
		for (int mosIdx : path)
			mosMaxPathLen[mosIdx] = max(mosMaxPathLen[mosIdx], (int)path.size());

	// Compute max depth (longest source→output path)
	MaxDepth = 0;
	for (auto& path : allPaths)
		if ((int)path.size() > MaxDepth)
			MaxDepth = (int)path.size();

	// Build transistor objects
	Transistors.clear();
	for (int i = 0; i < (int)transistor_pairs.size(); i++) {
		transistor t;
		int ni = transistor_pairs[i].first.first;
		int nj = transistor_pairs[i].first.second;
		t.Source    = netNames[ni];
		t.Drain     = netNames[nj];
		t.Gate      = transistor_pairs[i].second;
		t.Mos       = (mos) ? "PMOS" : "NMOS";
		t.Substrate = (mos) ? "VCC" : "GND";
		t.maxPathLength = mosMaxPathLen.count(i) ? mosMaxPathLen[i] : 1;
		if (mos) {
			t.W    = t.lambda * t.maxPathLength * t.basicW;
			t.nFin = t.lambda * t.maxPathLength;
		} else {
			t.W    = t.maxPathLength * t.basicW;
			t.nFin = t.maxPathLength;
		}
		Transistors.push_back(t);
	}

	// Block this solution so re-solving finds a different one
	CreateBlockClause(vals);

	return Literals;
}

// ==================== Get All Literals ====================

vector<string> MustNetCNF::GetAllLiterals() {
	vector<string> lits;
	for (int i = 0; i < nInputs; i++)
		if (VarIndPos[i]) lits.push_back(string(1, svars[i]));
	for (int i = 0; i < nInputs; i++)
		if (VarIndNeg[i]) lits.push_back("!" + string(1, svars[i]));
	return lits;
}

// ==================== Synthesis Loop ====================

pair<vector<string>, pair<int, int>> MustNetExactSynthesis(
	string dir, string FuncName, vector<string> Funcs, int nTransistors,
	vector<transistor>& Transistors, int mos, int INVOUT, string& cgStringOut,
	int timeBound, int DepthLimited, int AccFlag1, int AccFlag2,
	int placementFlag)
{
	int SatFlag = 0;
	// Strip leading per-output marker characters (matches MiniTNtk convention)
	for (int i = 0; i < (int)Funcs.size(); i++)
		FuncName.erase(FuncName.begin());

	while (!SatFlag) {
		cout << endl << "[MuSTNet] " << FuncName << " with " << nTransistors
			 << " transistors: " << endl;

		if (nTransistors >= 18) {
			// Safety bail-out matching MiniTNtk limit
			MustNetCNF tmpCnf;
			tmpCnf.SetAccFlags(AccFlag1, AccFlag2);
			string posFunc = Funcs[0];
			removeSpace(posFunc);
			ofstream f1("NegFunc.eqn");
			f1 << posFunc;
			f1.close();
			system("python sis.py NegFunc.eqn");
			string negFunc = ParseEqn("NegFunc_out.eqn");
			tmpCnf.InputParser(posFunc, negFunc);
			return make_pair(tmpCnf.GetAllLiterals(), make_pair(1, 1));
		}

		// Build MuSTNet network: T MOS nodes + T+1 net nodes
		MustNetNtk ntk = ConstructMustNetNtk(nTransistors, "MSN_" + FuncName);
		MustNetCNF cnf(ntk);
		cnf.SetAccFlags(AccFlag1, AccFlag2);
		cnf.SetPlacementFlag(placementFlag);

		// Parse Boolean function (single output)
		string posFunc = Funcs[0];
		removeSpace(posFunc);
		cout << "On-Func: " << posFunc << endl;
		{
			ofstream f1("NegFunc.eqn");
			f1 << posFunc;
			f1.close();
		}
		system("python sis.py NegFunc.eqn");
		string negFunc = ParseEqn("NegFunc_out.eqn");
		cout << "Off-Func: " << negFunc << endl;

		cnf.InputParser(posFunc, negFunc);
		cnf.InitVars();

		// Acceleration 2: pre-assign known literals to first MOS nodes
		if (cnf.GetAccFlag2())
			cnf.CreatePriorClauses();

		cnf.SetDepthLimitedFlag(DepthLimited);

		// Create all constraints (includes K-limited path constraints if DepthLimited)
		cnf.CreateAllClauses();

		// Write CNF and solve
		string cnfPath    = dir + ntk.NtkName + ".cnf";
		string cnfOutPath = dir + ntk.NtkName + "_out.cnf";
		cnf.WriteCnf(cnfPath);

		string cmd = "gtimeout " + to_string(timeBound) + " minisat "
			+ cnfPath + " " + cnfOutPath;
		cout << "[MuSTNet] Running: " << cmd << endl;
		system(cmd.c_str());

		// Parse result
		vector<string> Literals = cnf.ParseCnf(mos, Transistors, INVOUT,
			cnfOutPath, dir);

		if (cnf.GetSatResult()) {
			if (!DepthLimited) {
				SatFlag = 1;
				cgStringOut = cnf.GetCGString();
				return make_pair(Literals, make_pair(1, 1));
			}
			// Depth-limited re-solve loop: if depth exceeds K, block & re-solve
			int AddBlockConstraintsTimes = 0;
			while (AddBlockConstraintsTimes < 50) {
				if (cnf.GetIsDepthLimited()) {
					cgStringOut = cnf.GetCGString();
					return make_pair(Literals, make_pair(1, 1));
				}
				cout << "[MuSTNet] Depth " << cnf.GetMaxDepth() << " > K=" << cnf.getK()
					 << ", re-solving (iter " << AddBlockConstraintsTimes << ")..." << endl;
				// ParseCnf already added a block clause; re-write and re-solve
				cnf.WriteCnf(cnfPath);
				system(cmd.c_str());
				Literals = cnf.ParseCnf(mos, Transistors, INVOUT, cnfOutPath, dir);
				if (!cnf.GetSatResult())
					break; // no more solutions at this transistor count
				AddBlockConstraintsTimes++;
			}
			// If we exhausted re-solve attempts or went UNSAT, report depth status
			if (cnf.GetSatResult() && cnf.GetIsDepthLimited()) {
				cgStringOut = cnf.GetCGString();
				return make_pair(Literals, make_pair(1, cnf.GetIsDepthLimited()));
			}
		}

		nTransistors++;
	}

	return make_pair(vector<string>{}, make_pair(0, 0));
}
