#pragma once
#ifndef __MUSTNET_CNF_H__
#define __MUSTNET_CNF_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <functional>
#include "MustNetNtk.h"
#include "../GenerateSpice.h"

using namespace std;

// Forward declarations of utilities from parent
void removeSpace(string& s);
vector<string> split(string s, char sign);
string ParseEqn(string EqnPath);

class MustNetCNF {
private:
	MustNetNtk ntk;
	int nCnfVars;
	vector<vector<int>> clauses;

	// Boolean function info
	int nInputs;
	string svars;
	vector<int> VarIndPos, VarIndNeg;
	vector<vector<int>> Onsets, Offsets;
	vector<vector<int>> PosRepPattern, NegRepPattern;

	int SatResult;
	int AccTech1Flag, AccTech2Flag;
	int placementFlag;

	// === SAT Variable arrays ===
	// gateVar[m][l]: MOS m assigned literal l (0..2*nInputs-1)
	vector<vector<int>> gateVar;
	// epVar[m][pair_idx]: MOS m connects net pair pair_idx
	vector<vector<int>> epVar;
	// onVar[m][p]: MOS m conducts under pattern p (0..nPos+nNeg-1)
	vector<vector<int>> onVar;
	// flowL[pair_idx][p]: flow lower->higher, positive pattern p
	vector<vector<int>> flowL;
	// flowR[pair_idx][p]: flow higher->lower, positive pattern p
	vector<vector<int>> flowR;
	// epOn[m][pair_idx][p]: aux = epVar AND onVar (positive patterns)
	vector<vector<vector<int>>> epOn;
	// label[net_id][neg_pat_idx]: label for cut separation
	vector<vector<int>> label;

	// === Placement SAT Variables (Phase 2) ===
	// tpVar[m][j][f]: MOS m placed at column j with flip f (0=D-G-S, 1=S-G-D)
	vector<vector<vector<int>>> tpVar;
	// leftDiff[j][n]: left diffusion of column j is net n
	vector<vector<int>> leftDiff;
	// rightDiff[j][n]: right diffusion of column j is net n
	vector<vector<int>> rightDiff;

	string CGString;

public:
	MustNetCNF();
	MustNetCNF(MustNetNtk Ntk);
	~MustNetCNF();

	// Clause helpers
	void CreateORClause(vector<int> cnfvars);
	void CreateAtMostOneClause(vector<int> cnfvars);
	void CreateXNORClause(vector<int> cnfvars1, vector<int> cnfvars2);

	// Parsing and patterns
	void InputParser(string posFunc, string negFunc);
	void DeriveRepPattern(int flag);
	vector<vector<int>> DeriveFunc(vector<vector<string>> vProducts, map<char, int> VarId);

	// SAT variable allocation
	void InitVars();

	// Constraint generation
	void CreateGateAssignClauses();
	void CreateEndpointAssignClauses();
	void CreateConductivityClauses();
	void CreateAuxEpOnClauses();
	void CreateFlowClauses();
	void CreateSeparationClauses();
	void CreateAllClauses();

	// Placement constraints (Phase 2)
	void CreateTransistorAllocClauses();   // C7: ExactlyOne(j,f) per MOS
	void CreateColumnAllocClauses();       // C8: ExactlyOne(m,f) per column
	void CreateDiffLinkClauses();          // C9: link tp+ep → leftDiff/rightDiff
	void CreateDiffusionSharingClauses();  // C10: adjacent column sharing
	void CreatePlacementClauses();         // calls C7–C10

	// Prior clauses (acceleration: pre-assign known literals)
	vector<int> CreatePriorClauses();

	// CNF I/O
	void WriteCnf(string cnfpath);
	vector<string> ParseCnf(int mos, vector<transistor>& Transistors, int OutINV,
		string cnfpath, string dir);

	// Blocking
	void CreateBlockClause(vector<int> vals);

	// Getters
	int GetSatResult() { return SatResult; }
	int GetnCnfVars() { return nCnfVars; }
	MustNetNtk GetNtk() { return ntk; }
	string GetSvars() { return svars; }
	int GetnInputs() { return nInputs; }
	vector<vector<int>> GetPosRepPattern() { return PosRepPattern; }
	vector<vector<int>> GetNegRepPattern() { return NegRepPattern; }
	vector<string> GetAllLiterals();

	void SetAccFlags(int f1, int f2) { AccTech1Flag = f1; AccTech2Flag = f2; }
	int GetAccFlag1() { return AccTech1Flag; }
	int GetAccFlag2() { return AccTech2Flag; }
	int GetNumClauses() { return (int)clauses.size(); }
	void SetPlacementFlag(int f) { placementFlag = f; }
	int GetPlacementFlag() { return placementFlag; }
	string GetCGString() { return CGString; }
};

// MuSTNet synthesis function (parallel to TransistorExactSynthesis)
pair<vector<string>, pair<int, int>> MustNetExactSynthesis(
	string dir, string FuncName, vector<string> Funcs, int nTransistors,
	vector<transistor>& Transistors, int mos, int INVOUT, string& cgStringOut,
	int timeBound, int DepthLimited, int AccFlag1, int AccFlag2,
	int placementFlag = 0);

#endif
