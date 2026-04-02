#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <cstdio>
#include "argparse.hpp"
#include "TransistorNtk.h"
#include "TransistorNtkCNF.h"
#include "PathLimitation.h"
#include "GenerateSpice.h"
#include "MuSTNet/MustNetCNF.h"
#include <set>
using namespace std;
// nTransistors: the number of transistors in the initial exact synthesis round
// nPreSetTransistors: the number of pre-determined transistors in each exact synthesis round
// vPreSetTransistors: the patterns of how to set the remaining transistors' corresponding literals
//pair<vector<int>, pair<int,int>> TransistorExactSynthesis(string dir, string FuncName, vector<string> Funcs, int nTransistors, int timeBound = 3600, int nPreSetTransistors = 0,
//	vector<vector<int>> vPreSetTransistors = {}) {
//	int SatFlag = 0;
//	vector<vector<int>> vPreSetTransistorsTmp = vPreSetTransistors;
//	for (int i = 0; i < Funcs.size(); i++)
//		FuncName.erase(FuncName.begin());
//
//	while (!SatFlag) {
//		// nTransistors = 7;
//		cout << endl << FuncName << " with " << nTransistors << " transistors: " << endl;
//		TransistorNtk TMultiOutNtk = ConstructMultiOutTransistorNtk(nTransistors, Funcs.size(), FuncName);
//		MultiOutTransistorCNF TMultiCnf(TMultiOutNtk, Funcs.size());
//		TMultiCnf.InitVecMultiOutsCnfs(Funcs, dir);
//		/*TMultiCnf.InitGlobalVars();
//		TMultiCnf.CreateGlobalClauses();*/
//		vector<int> Tran2InputVars = TMultiCnf.CreatePriorClauses();
//		int nInitTransistors = Tran2InputVars.size();
//		int nRemainTransistors = TMultiOutNtk.iTransistors.size() - Tran2InputVars.size();
//		nRemainTransistors = (nRemainTransistors < nPreSetTransistors) ? nRemainTransistors : nPreSetTransistors;
//		if (nRemainTransistors) {
//			int nCases = (!vPreSetTransistors.size()) ? int(pow(Tran2InputVars.size(), nRemainTransistors)) : vPreSetTransistors.size();
//			if (!vPreSetTransistors.size()) {
//				for (int i = 0; i < nCases; i++) {
//					int iCase = i;
//					vector<int> vIds(nRemainTransistors);
//					for (int j = 0; j < nRemainTransistors; j++) {
//						int iLiteral = iCase % Tran2InputVars.size();
//						vIds[j] = Tran2InputVars[iLiteral];
//						iCase /= Tran2InputVars.size();
//					}
//					vPreSetTransistors.push_back(vIds);
//				}
//			}
//			else {
//				vPreSetTransistors = vPreSetTransistorsTmp;
//				for (int i = 0; i < vPreSetTransistors.size(); i++)
//					for (int j = 0; j < Tran2InputVars.size(); j++)
//						vPreSetTransistors[i].erase(vPreSetTransistors[i].begin());
//			}
//			for (int i = 0; i < nCases; i++) {
//				MultiOutTransistorCNF TMultiCnfTmp = TMultiCnf;
//				vector<int> Tran2InputVarsTmp = Tran2InputVars;
//				// create priorclauses for remaining transistors
//				for (int j = 0; j < nRemainTransistors; j++) {
//					TMultiCnfTmp.CreateTransistorInputClauses(j + Tran2InputVars.size(), Tran2InputVars[vPreSetTransistors[i][j]]);
//					Tran2InputVarsTmp.push_back(Tran2InputVars[vPreSetTransistors[i][j]]);
//				}
//
//				TMultiCnfTmp.MultiOutCreateClauses(Tran2InputVarsTmp);
//				TMultiCnfTmp.GetAllClauses();
//				TMultiCnfTmp.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
//				system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//				// system(("minisat ./" + TMultiOutNtk.NtkName + ".cnf ./" + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//				Tran2InputVarsTmp = TMultiCnfTmp.ParseCnf(dir + TMultiOutNtk.NtkName + "_out.cnf", dir);
//				// TMultiCnfTmp.ParseCnf("./" + TMultiOutNtk.NtkName + "_out.cnf");
//				if (TMultiCnfTmp.GetSatResult()) {
//					SatFlag = 1;
//					return make_pair(Tran2InputVarsTmp, make_pair(TMultiCnfTmp.GetnVars(), nInitTransistors));
//					// fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVarsTmp, TMultiCnfTmp.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;
//					
//				}
//			}
//		}
//		else {
//			TMultiCnf.MultiOutCreateClauses(Tran2InputVars);
//			TMultiCnf.GetAllClauses();
//			TMultiCnf.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
//			system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//			Tran2InputVars = TMultiCnf.ParseCnf(dir + TMultiOutNtk.NtkName + "_out.cnf", dir);
//			if (TMultiCnf.GetSatResult()) {
//				SatFlag = 1;
//				return make_pair(Tran2InputVars, make_pair(TMultiCnf.GetnVars(), nInitTransistors));
//				// fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVars, TMultiCnf.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;
//			}
//		}
//		nTransistors++;
//	}
//}

// nTransistors: the number of transistors in the initial exact synthesis round
// nPreSetTransistors: the number of pre-determined transistors in each exact synthesis round
// vPreSetTransistors: the patterns of how to set the remaining transistors' corresponding literals

static void DebugTruthTables(const string& label,
	const vector<vector<int>>& targetTt,
	const vector<vector<int>>& resultTt) {
	bool match = (targetTt == resultTt);
	cout << "[TT-Check] " << label << ": " << (match ? "MATCH" : "MISMATCH") << endl;
	if (!match) {
		for (int out = 0; out < (int)targetTt.size(); out++) {
			cout << "  Output " << out << ":" << endl;
			cout << "    Target : ";
			for (int v : targetTt[out]) cout << v;
			cout << endl;
			cout << "    Synth  : ";
			for (int v : resultTt[out]) cout << v;
			cout << endl;
			cout << "    Diff   : ";
			for (int i = 0; i < (int)targetTt[out].size(); i++)
				cout << (targetTt[out][i] != resultTt[out][i] ? "^" : ".");
			cout << endl;
		}
	}
}

pair<vector<string>, pair<int, int>> TransistorExactSynthesis(string dir, string FuncName, vector<string> Funcs, int nTransistors,
	vector<transistor>& Transistors, int mos, int INVOUT, string& cgStringOut,
	int timeBound = 3600, int nPreSetTransistors = 0,
	int DepthLimited = 1, int AccFlag1 = 1, int AccFlag2 = 1, vector<vector<int>> vPreSetTransistors = {}) {
	int SatFlag = 0;
	vector<vector<int>> vPreSetTransistorsTmp = vPreSetTransistors;
	for (int i = 0; i < Funcs.size(); i++)
		FuncName.erase(FuncName.begin());

	while (!SatFlag) {
		// nTransistors = 7;
		cout << endl << FuncName << " with " << nTransistors << " transistors: " << endl;
		TransistorNtk TMultiOutNtk = ConstructMultiOutTransistorNtk(nTransistors, Funcs.size(), FuncName);
		MultiOutTransistorCNF TMultiCnf(TMultiOutNtk, Funcs.size());
		// version: 2023/5/9
		TMultiCnf.SetAccFlags(AccFlag1, AccFlag2);
		// Acceleration 1: compute representative patterns
		TMultiCnf.InitVecMultiOutsCnfs(Funcs, dir);
		TMultiCnf.SetDepthLimitedFlag(DepthLimited);
		/*TMultiCnf.InitGlobalVars();
		TMultiCnf.CreateGlobalClauses();*/
		// derive the needed literals
		// Acceleration 2: pre-define some existed literals
		vector<int> Tran2InputVars = (TMultiCnf.GetAccFlag2()) ? TMultiCnf.CreatePriorClauses() : vector<int>{};
		int nRemainTransistors = TMultiOutNtk.iTransistors.size() - Tran2InputVars.size();
		nRemainTransistors = (nRemainTransistors < nPreSetTransistors) ? nRemainTransistors : nPreSetTransistors;
		if (nRemainTransistors) {
			int nCases = (!vPreSetTransistors.size()) ? int(pow(Tran2InputVars.size(), nRemainTransistors)) : vPreSetTransistors.size();
			if (!vPreSetTransistors.size()) {
				for (int i = 0; i < nCases; i++) {
					int iCase = i;
					vector<int> vIds(nRemainTransistors);
					for (int j = 0; j < nRemainTransistors; j++) {
						int iLiteral = iCase % Tran2InputVars.size();
						vIds[j] = Tran2InputVars[iLiteral];
						iCase /= Tran2InputVars.size();
					}
					vPreSetTransistors.push_back(vIds);
				}
			}
			else {
				vPreSetTransistors = vPreSetTransistorsTmp;
				for (int i = 0; i < vPreSetTransistors.size(); i++)
					for (int j = 0; j < Tran2InputVars.size(); j++)
						vPreSetTransistors[i].erase(vPreSetTransistors[i].begin());
			}
			for (int i = 0; i < nCases; i++) {
				MultiOutTransistorCNF TMultiCnfTmp = TMultiCnf;
				vector<int> Tran2InputVarsTmp = Tran2InputVars;
				vector<string> Literals;
				// create priorclauses for remaining transistors
				for (int j = 0; j < nRemainTransistors; j++) {
					TMultiCnfTmp.CreateTransistorInputClauses(j + Tran2InputVars.size(), Tran2InputVars[vPreSetTransistors[i][j]]);
					Tran2InputVarsTmp.push_back(Tran2InputVars[vPreSetTransistors[i][j]]);
				}

				TMultiCnfTmp.MultiOutCreateClauses(Tran2InputVarsTmp);
				TMultiCnfTmp.GetAllClauses();
				TMultiCnfTmp.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
				system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
				// system(("minisat ./" + TMultiOutNtk.NtkName + ".cnf ./" + TMultiOutNtk.NtkName + "_out.cnf").c_str());
				Literals = TMultiCnfTmp.ParseCnf(mos, Transistors, INVOUT, dir + TMultiOutNtk.NtkName + "_out.cnf", dir);
				// TMultiCnfTmp.ParseCnf("./" + TMultiOutNtk.NtkName + "_out.cnf");
				if (TMultiCnfTmp.GetSatResult()) {
					SatFlag = 1;
					cgStringOut = TMultiCnfTmp.GetCGString();
					return make_pair(Literals, make_pair(TMultiCnfTmp.GetExact(), (DepthLimited) ? TMultiCnfTmp.GetIsDepthLimited() : 1));
					// fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVarsTmp, TMultiCnfTmp.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;

				}
			}
		}
		else {
			vector<string> Literals;
			// version: 2023/5/4
			/*if (nTransistors >= TMultiCnf.GetAlLiterals().size() || nTransistors >= 18) {
				return make_pair(TMultiCnf.GetAlLiterals(), make_pair(1, 1));
			}*/
			if (nTransistors >= 18) {
				return make_pair(TMultiCnf.GetAlLiterals(), make_pair(1, 1));
			}
			// set the neighbour edges' flows as 0 for positive input patterns
			TMultiCnf.MultiOutCreateClauses(Tran2InputVars);
			TMultiCnf.GetAllClauses();
			TMultiCnf.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
			system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
			Literals = TMultiCnf.ParseCnf(mos, Transistors, INVOUT, dir + TMultiOutNtk.NtkName + "_out.cnf", dir);
			if (TMultiCnf.GetSatResult()) {
				// Verify the synthesized network immediately after ParseCnf, which has
				// already removed any degenerate (short-connected) transistors from ResultPaths.
				// ActualTt = target function truth table (from Onsets/CNF formulation)
				// ResultTt = truth table derived from the actual switching paths
				{
					vector<vector<int>> ActualTt = TMultiCnf.DeriveEachCnfTruthTable();
					vector<vector<int>> ResultTt = TMultiCnf.DeriveResultFunc();
					DebugTruthTables(TMultiOutNtk.NtkName + "[post-drop]", ActualTt, ResultTt);
				}
				if (!DepthLimited) {
					SatFlag = 1;
					vector<vector<int>> ActualTt = TMultiCnf.DeriveEachCnfTruthTable();
					vector<vector<int>> ResultTt = TMultiCnf.DeriveResultFunc();
					TMultiCnf.showResultPaths();
					TMultiCnf.showResultPathIDs();
					DebugTruthTables(TMultiOutNtk.NtkName, ActualTt, ResultTt);
					if (ActualTt == ResultTt)
						TMultiCnf.SetExact(1);
					else
						TMultiCnf.SetExact(0);
					cgStringOut = TMultiCnf.GetCGString();
					return make_pair(Literals, make_pair(TMultiCnf.GetExact(), (DepthLimited) ? TMultiCnf.GetIsDepthLimited() : 1));
				}
				int AddBlockConstraintsTimes = 0;
				while (AddBlockConstraintsTimes<50) {
					vector<vector<int>> ActualTt = TMultiCnf.DeriveEachCnfTruthTable();
					vector<vector<int>> ResultTt = TMultiCnf.DeriveResultFunc();
					TMultiCnf.showResultPaths();
					TMultiCnf.showResultPathIDs();
					DebugTruthTables(TMultiOutNtk.NtkName + "(iter" + to_string(AddBlockConstraintsTimes) + ")", ActualTt, ResultTt);
					if (ActualTt == ResultTt)
						TMultiCnf.SetExact(1);
					else
						TMultiCnf.SetExact(0);
					if(TMultiCnf.GetIsDepthLimited()) {
						cgStringOut = TMultiCnf.GetCGString();
						return make_pair(Literals, make_pair(TMultiCnf.GetExact(), (DepthLimited) ? TMultiCnf.GetIsDepthLimited() : 1));
					}
					TMultiCnf.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
					system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
					Literals = TMultiCnf.ParseCnf(mos, Transistors, INVOUT, dir + TMultiOutNtk.NtkName + "_out.cnf", dir);
					AddBlockConstraintsTimes++;
				}
				

				
				// fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVars, TMultiCnf.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;
			}
		}
		nTransistors++;
	}
}

//vector<string> TransistorExactSynthesis(string dir, string FuncName, vector<string> Funcs, int nTransistors, int timeBound = 3600, int nPreSetTransistors = 0,
//	vector<vector<int>> vPreSetTransistors = {}) {
//	int SatFlag = 0;
//	vector<vector<int>> vPreSetTransistorsTmp = vPreSetTransistors;
//	for (int i = 0; i < Funcs.size(); i++)
//		FuncName.erase(FuncName.begin());
//
//	while (!SatFlag) {
//		// nTransistors = 7;
//		cout << endl << FuncName << " with " << nTransistors << " transistors: " << endl;
//		TransistorNtk TMultiOutNtk = ConstructMultiOutTransistorNtk(nTransistors, Funcs.size(), FuncName);
//		MultiOutTransistorCNF TMultiCnf(TMultiOutNtk, Funcs.size());
//		TMultiCnf.InitVecMultiOutsCnfs(Funcs, dir);
//		/*TMultiCnf.InitGlobalVars();
//		TMultiCnf.CreateGlobalClauses();*/
//		vector<int> Tran2InputVars = TMultiCnf.CreatePriorClauses();
//		int nRemainTransistors = TMultiOutNtk.iTransistors.size() - Tran2InputVars.size();
//		nRemainTransistors = (nRemainTransistors < nPreSetTransistors) ? nRemainTransistors : nPreSetTransistors;
//		if (nRemainTransistors) {
//			int nCases = (!vPreSetTransistors.size()) ? int(pow(Tran2InputVars.size(), nRemainTransistors)) : vPreSetTransistors.size();
//			if (!vPreSetTransistors.size()) {
//				for (int i = 0; i < nCases; i++) {
//					int iCase = i;
//					vector<int> vIds(nRemainTransistors);
//					for (int j = 0; j < nRemainTransistors; j++) {
//						int iLiteral = iCase % Tran2InputVars.size();
//						vIds[j] = Tran2InputVars[iLiteral];
//						iCase /= Tran2InputVars.size();
//					}
//					vPreSetTransistors.push_back(vIds);
//				}
//			}
//			else {
//				vPreSetTransistors = vPreSetTransistorsTmp;
//				for (int i = 0; i < vPreSetTransistors.size(); i++)
//					for (int j = 0; j < Tran2InputVars.size(); j++)
//						vPreSetTransistors[i].erase(vPreSetTransistors[i].begin());
//			}
//			for (int i = 0; i < nCases; i++) {
//				MultiOutTransistorCNF TMultiCnfTmp = TMultiCnf;
//				vector<int> Tran2InputVarsTmp = Tran2InputVars;
//				vector<string> Literals;
//				// create priorclauses for remaining transistors
//				for (int j = 0; j < nRemainTransistors; j++) {
//					TMultiCnfTmp.CreateTransistorInputClauses(j + Tran2InputVars.size(), Tran2InputVars[vPreSetTransistors[i][j]]);
//					Tran2InputVarsTmp.push_back(Tran2InputVars[vPreSetTransistors[i][j]]);
//				}
//
//				TMultiCnfTmp.MultiOutCreateClauses(Tran2InputVarsTmp);
//				TMultiCnfTmp.GetAllClauses();
//				TMultiCnfTmp.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
//				system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//				// system(("minisat ./" + TMultiOutNtk.NtkName + ".cnf ./" + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//				Literals = TMultiCnfTmp.ParseCnf(dir + TMultiOutNtk.NtkName + "_out.cnf", dir);
//				// TMultiCnfTmp.ParseCnf("./" + TMultiOutNtk.NtkName + "_out.cnf");
//				if (TMultiCnfTmp.GetSatResult()) {
//					SatFlag = 1;
//					return Literals;
//					// fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVarsTmp, TMultiCnfTmp.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;
//
//				}
//			}
//		}
//		else {
//			vector<string> Literals;
//			TMultiCnf.MultiOutCreateClauses(Tran2InputVars);
//			TMultiCnf.GetAllClauses();
//			TMultiCnf.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
//			system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//			map<pair<int, int>, int> AllEdges;
//			map<pair<int, int>, string> transistors;
//			map<pair<int, int>, int> transistors_cnfvars;
//			// Literals = TMultiCnf.ParseCnf(dir + TMultiOutNtk.NtkName + "_out.cnf", AllEdges, transistors, transistors_cnfvars, dir);
//			Literals = TMultiCnf.GetTCnf(0).ParseCnf(dir + TMultiOutNtk.NtkName + "_out.cnf", AllEdges, transistors, transistors_cnfvars, dir);
//			if (TMultiCnf.GetSatResult()) {
//				int KPathLimitRounds = 0;
//				while (1) {
//					vector<vector<int>> PathLimitedClauses = IncrementalAddLimitedPathConstraints(AllEdges, transistors, transistors_cnfvars, TMultiCnf.GetTransistorNtk().Nodes.size(), TMultiCnf.GetMaxPathLength(), TMultiCnf.GetTransistorNtk().GetOutputNodeIDs());
//					if (!PathLimitedClauses.size()) {
//						SatFlag = 1;
//						return Literals;
//					}
//					else {
//						for (auto clause : PathLimitedClauses)
//							TMultiCnf.AddClause(clause);
//						TMultiCnf.WriteCnf(dir + TMultiOutNtk.NtkName + ".cnf");
//						system(("gtimeout " + to_string(timeBound) + " minisat " + dir + TMultiOutNtk.NtkName + ".cnf " + dir + TMultiOutNtk.NtkName + "_out.cnf").c_str());
//						AllEdges.clear();
//						transistors.clear();
//						transistors_cnfvars.clear();
//						Literals = TMultiCnf.ParseCnf(dir + TMultiOutNtk.NtkName + "_out.cnf", AllEdges, transistors, transistors_cnfvars, dir);
//					}
//					KPathLimitRounds++;
//				}
//				/*return Literals;*/
//			}
//		}
//		nTransistors++;
//	}
//}


// 2025/3/1
//pair<vector<string>, int> InputNeg(vector<string> Funcs, string dir = "") {
//	vector<string> InputNegFuncs;
//	set<string> Literals;
//	for (auto Func : Funcs) {
//		removeSpace(Func);
//		// cout << "Initial Func: " << Func << endl;
//		ofstream f1;
//		f1.open(dir + "NegFunc.eqn");
//		f1 << "Func=!(" << Func << ");" << endl;
//		f1.close();
//		system((string("sis -c \"read_eqn ") + dir + string("NegFunc.eqn;simplify;write_eqn ") + dir + string("NegFunc_out.eqn;\"")).c_str());
//		string NegFunc = ParseEqn(dir + "NegFunc_out.eqn");
//		// cout << "Neg Func: " << NegFunc << endl;
//		vector<string> Products = (NegFunc.size()) ? split(NegFunc, '+') : vector<string>{};
//		vector<vector<string>> vProducts;
//		// derive the sum of products for onset and offset
//		for (auto s : Products)
//			vProducts.push_back(split(s, '*'));
//		for (int i = 0; i < vProducts.size(); i++) {
//			for (int j = 0; j < vProducts[i].size(); j++) {
//				if (vProducts[i][j][0] == '!')
//					vProducts[i][j].erase(vProducts[i][j].begin());
//				else
//					vProducts[i][j] = "!" + vProducts[i][j];
//			}
//		}
//		// get the number of literals
//		for (auto product : vProducts)
//			for (auto literal : product)
//				Literals.insert(literal);
//
//		// recombine products
//		NegFunc = "";
//		for (int i = 0; i < vProducts.size(); i++) {
//			string product = vProducts[i][0];
//			for (int j = 1; j < vProducts[i].size(); j++) {
//				product += "*";
//				product += vProducts[i][j];
//			}
//			if (i)
//				NegFunc += "+";
//			NegFunc += product;
//		}
//
//		InputNegFuncs.push_back(NegFunc);
//		// cout << "Input neg: " << NegFunc << endl;
//	}
//	return make_pair(InputNegFuncs, Literals.size());
//}
//

pair<vector<string>, int> InputNeg(vector<string> Funcs, string dir = "") {
	vector<string> InputNegFuncs;
	set<string> Literals;
	for (auto Func : Funcs) {
		removeSpace(Func);
		// cout << "Initial Func: " << Func << endl;
		ofstream f1;
		f1.open("NegFunc.eqn");
		f1 << Func;
		f1.close();
		system("python sis.py NegFunc.eqn");
		string NegFunc = ParseEqn("NegFunc_out.eqn");
		// cout << "Neg Func: " << NegFunc << endl;
		vector<string> Products = (NegFunc.size()) ? split(NegFunc, '+') : vector<string>{};
		vector<vector<string>> vProducts;
		// derive the sum of products for onset and offset
		for (auto s : Products)
			vProducts.push_back(split(s, '*'));
		for (int i = 0; i < vProducts.size(); i++) {
			for (int j = 0; j < vProducts[i].size(); j++) {
				if (vProducts[i][j][0] == '!')
					vProducts[i][j].erase(vProducts[i][j].begin());
				else
					vProducts[i][j] = "!" + vProducts[i][j];
			}
		}
		// get the number of literals
		for (auto product : vProducts)
			for (auto literal : product)
				Literals.insert(literal);

		// recombine products
		NegFunc = "";
		for (int i = 0; i < vProducts.size(); i++) {
			string product = vProducts[i][0];
			for (int j = 1; j < vProducts[i].size(); j++) {
				product += "*";
				product += vProducts[i][j];
			}
			if (i)
				NegFunc += "+";
			NegFunc += product;
		}

		InputNegFuncs.push_back(NegFunc);
		// cout << "Input neg: " << NegFunc << endl;
	}
	return make_pair(InputNegFuncs, Literals.size());
}

int main(int argc, char* argv[]) {
	argparse::ArgumentParser program("MiniTNtk", "1.0");

	program.add_argument("--dir")
		.help("path of Booleans.txt (default: ./)")
		.default_value(string("./"));
	program.add_argument("--preset")
		.help("number of pre-defined transistors (default: 0)")
		.default_value(0)
		.scan<'i', int>();
	program.add_argument("--timeout")
		.help("runtime bound of SAT solving in seconds (default: 3600)")
		.default_value(3600)
		.scan<'i', int>();
	program.add_argument("--pdn-only")
		.help("only solve PDN (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--depth-limited")
		.help("limit the number of transistors in series (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--count-inv")
		.help("count transistors of input inverters (default: true)")
		.default_value(true)
		.implicit_value(true);
	program.add_argument("--no-count-inv")
		.help("do not count transistors of input inverters (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--acc1")
		.help("acceleration: representative patterns (default: true)")
		.default_value(true)
		.implicit_value(true);
	program.add_argument("--no-acc1")
		.help("disable acceleration technique 1 (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--acc2")
		.help("acceleration: pre-defined transistors for existing literals (default: true)")
		.default_value(true)
		.implicit_value(true);
	program.add_argument("--no-acc2")
		.help("disable acceleration technique 2 (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--spice-dir")
		.help("path for generated .sp files (default: ./out/)")
		.default_value(string("./out/"));
	program.add_argument("--mustnet")
		.help("use MuSTNet mode (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--placement")
		.help("enable placement constraints in MuSTNet (default: false)")
		.default_value(false)
		.implicit_value(true);
	program.add_argument("--csv")
		.help("path of output result CSV file (default: {dir}/PClassResults.csv)")
		.default_value(string(""));

	try {
		program.parse_args(argc, argv);
	} catch (const std::exception& err) {
		cerr << err.what() << endl;
		cerr << program;
		return 1;
	}

	string dir = program.get<string>("--dir");
	// Ensure dir ends with /
	if (!dir.empty() && dir.back() != '/')
		dir += '/';

	int OnlyPDNFlag = program.get<bool>("--pdn-only") ? 1 : 0;
	int DepthLimited = program.get<bool>("--depth-limited") ? 1 : 0;
	int CountInputINV = program.get<bool>("--no-count-inv") ? 0 : (program.get<bool>("--count-inv") ? 1 : 1);
	string spicepath = program.get<string>("--spice-dir");
	if (!spicepath.empty() && spicepath.back() != '/')
		spicepath += '/';
	int useMustNet = program.get<bool>("--mustnet") ? 1 : 0;
	int placementFlag = program.get<bool>("--placement") ? 1 : 0;
	string csvPath = program.get<string>("--csv");
	if (csvPath.empty())
		csvPath = dir + "PClassResults.csv";
	int AccFlag1 = program.get<bool>("--no-acc1") ? 0 : 1;
	int AccFlag2 = program.get<bool>("--no-acc2") ? 0 : 1;
	int nPreSetTransistors = program.get<int>("--preset");
	int timeBound = program.get<int>("--timeout");
	map<string, pair<string, int>> BoolFuncs;
	ParseBoolFuncTxtFile(dir+string("Booleans.txt"), BoolFuncs);

	ofstream fExcel;
	fExcel.open(csvPath);
	if (DepthLimited)
		fExcel << "Boolean Func,#Transistors,#Transistors_PDN,#Transistors_PUN,PDN-CG,PUN-CG,Runtime(ms),SatResult,DepthLimited" << endl;
	else
		fExcel << "Boolean Func,#Transistors,#Transistors_PDN,#Transistors_PUN,PDN-CG,PUN-CG,Runtime(ms),SatResult" << endl;
	for (auto it = BoolFuncs.begin(); it != BoolFuncs.end(); it++) {
		string FuncName = (*it).first;
		vector<string> Funcs = split((*it).second.first, '|');
		int nTransistors = (*it).second.second;

		// version: 2023/4/4
		int OutInvFlag = (FuncName[0] == '!') ? 1 : 0;
		vector<int> OutInvFlags;
		for (int i = 0; i < Funcs.size(); i++) {
			if (FuncName[i] == '!')
				OutInvFlags.push_back(1);
			else
				OutInvFlags.push_back(0);
		}
		int SAT = 1;
		int SATDepthLimited = 1;
		auto start_time = chrono::high_resolution_clock::now();
		pair<vector<string>,pair<int,int>> LiteralsPDN, LiteralsPUN; // literals, whether satisfying given Boolean functions, whether satisfying the given depth limitation
		// version: 2023/6/5
		vector<transistor> transistors_PDN, transistors_PUN;
		string cgStringPDN, cgStringPUN;
		// pair<vector<int>, pair<int,int>> Tran2InputVarsandnVars = TransistorExactSynthesis(argv[1], FuncName + "PDN", Funcs, nTransistors, atoi(argv[3]), atoi(argv[2]));
		if (useMustNet) {
			LiteralsPDN = MustNetExactSynthesis(dir, FuncName + "PDN", Funcs, nTransistors, transistors_PDN, 0, OutInvFlags[0], cgStringPDN, timeBound, DepthLimited, AccFlag1, AccFlag2, placementFlag);
		} else {
			LiteralsPDN = TransistorExactSynthesis(dir, FuncName + "PDN", Funcs, nTransistors, transistors_PDN, 0, OutInvFlags[0], cgStringPDN, timeBound, nPreSetTransistors, DepthLimited, AccFlag1, AccFlag2);
		}
		// version: 2023/4/29
		SAT *= LiteralsPDN.second.first;
		SATDepthLimited *= LiteralsPDN.second.second;
		/*vector<int> Tran2InputVars = Tran2InputVarsandnVars.first;
		int nVars = Tran2InputVarsandnVars.second.first;
		int nInitTransistors = Tran2InputVarsandnVars.second.second;
		vector<int> vPreSetTransistors = Tran2InputVars;*/
		
		// pair<vector<int>, pair<int, int>> Tran2InputVarsPUNandnVars = TransistorExactSynthesis(argv[1], FuncName + "PUN", InputNeg(Funcs), Tran2InputVars.size(), atoi(argv[3]), Tran2InputVars.size() - nInitTransistors, { vPreSetTransistors });
		if (!OnlyPDNFlag) {
			pair<vector<string>, int> InputNegFuncs = InputNeg(Funcs, dir);
			if (useMustNet) {
				LiteralsPUN = MustNetExactSynthesis(dir, FuncName + "PUN", InputNegFuncs.first, InputNegFuncs.second, transistors_PUN, 1, OutInvFlags[0], cgStringPUN, timeBound, DepthLimited, AccFlag1, AccFlag2, placementFlag);
			} else {
				LiteralsPUN = TransistorExactSynthesis(dir, FuncName + "PUN", InputNegFuncs.first, InputNegFuncs.second, transistors_PUN, 1, OutInvFlags[0], cgStringPUN, timeBound, nPreSetTransistors, DepthLimited, AccFlag1, AccFlag2);
			}
			SAT *= LiteralsPUN.second.first;
			SATDepthLimited *= LiteralsPUN.second.second;
		}
		auto end_time = chrono::high_resolution_clock::now();
		auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

		set<string> LiteralsAll;
		for (auto literal : LiteralsPDN.first)
			LiteralsAll.insert(literal);
		for (auto literal : LiteralsPUN.first)
			LiteralsAll.insert(literal);
		// version:2023/6/5
		GenerateTransistors(LiteralsAll, transistors_PUN, transistors_PDN, OutInvFlags[0]);

		// summarize the path statistics of each transistor
		map<string, int> PathStatistics;
		for (auto literal : LiteralsAll)
			PathStatistics[literal] = 0;
		for (auto transistor : transistors_PDN)
			PathStatistics[transistor.Gate] += transistor.maxPathLength;
		for (auto transistor : transistors_PUN)
			PathStatistics[transistor.Gate] += transistor.maxPathLength;

		string spiceName = FuncName;
		if (DepthLimited)
			spiceName += "_DepthLimited";
		if (useMustNet)
			spiceName += "_MuSTNet";
		for (int c = 0; c < Funcs.size(); c++)
			spiceName.erase(spiceName.begin());
		writeSpice(spicepath + spiceName + ".sp", spiceName, LiteralsAll, transistors_PUN, transistors_PDN, PathStatistics);
		// Save original name for CSV before stripping marker characters
		string csvFuncName = FuncName;
		// version: 2023/4/29
		// remove the first characters '!', ' '
		for (int i = 0; i < Funcs.size(); i++)
			FuncName.erase(FuncName.begin());
		if (CountInputINV) {
			if (DepthLimited)
				fExcel << csvFuncName << "," << NPTransistorsWithINV(LiteralsAll, LiteralsPDN.first.size() + LiteralsPUN.first.size(), OutInvFlags) << "," << LiteralsPDN.first.size() << "," << LiteralsPUN.first.size() << "," << cgStringPDN << "," << cgStringPUN << "," << elapsed_time.count() << "," << string((SAT) ? "SAT" : "UNSAT") << "," << SATDepthLimited << endl;
			else
 				fExcel << csvFuncName << "," << NPTransistorsWithINV(LiteralsAll, LiteralsPDN.first.size() + LiteralsPUN.first.size(), OutInvFlags) << "," << LiteralsPDN.first.size() << "," << LiteralsPUN.first.size() << "," << cgStringPDN << "," << cgStringPUN << "," << elapsed_time.count() << "," << string((SAT) ? "SAT" : "UNSAT") << endl;
			cout << "Total transistors: " << NPTransistorsWithINV(LiteralsAll, LiteralsPDN.first.size() + LiteralsPUN.first.size(), OutInvFlags) << endl;
		}	
		else {
			if (DepthLimited)
				fExcel << csvFuncName << "," << NPTransistorsWithoutINV(LiteralsPDN.first.size() + LiteralsPUN.first.size(), OutInvFlags) << "," << LiteralsPDN.first.size() << "," << LiteralsPUN.first.size() << "," << cgStringPDN << "," << cgStringPUN << "," << elapsed_time.count() << "," << string((SAT) ? "SAT" : "UNSAT") << "," << SATDepthLimited << endl;
			else
				fExcel << csvFuncName << "," << NPTransistorsWithoutINV(LiteralsPDN.first.size() + LiteralsPUN.first.size(), OutInvFlags) << "," << LiteralsPDN.first.size() << "," << LiteralsPUN.first.size() << "," << cgStringPDN << "," << cgStringPUN << "," << elapsed_time.count() << "," << string((SAT) ? "SAT" : "UNSAT") << endl;
			cout << "Total transistors: " << NPTransistorsWithoutINV(LiteralsPDN.first.size() + LiteralsPUN.first.size(), OutInvFlags) << endl;
		}

		// Clean up intermediate files
		std::remove("NegFunc.eqn");
		std::remove("NegFunc_out.eqn");
		// Remove CNF files generated during synthesis
		string cleanCmd = "rm -f " + dir + "*.cnf 2>/dev/null";
		system(cleanCmd.c_str());
		// Remove .dot and .pdf graph files
		cleanCmd = "rm -f Transistors_*.dot Transistors_*.pdf " + dir + "Transistors_*.dot " + dir + "Transistors_*.pdf 2>/dev/null";
		system(cleanCmd.c_str());

		//	// the following can be annotated
		//	int SatFlag = 0;
		//	int OutInvFlag = (FuncName[0] == '!') ? 1 : 0;
		//	// version_tmp: 2023/3/30
		//	vector<int> OutInvFlags;
		//	for (int i = 0; i < Funcs.size(); i++) {
		//		if (FuncName[i] == '!')
		//			OutInvFlags.push_back(1);
		//		else
		//			OutInvFlags.push_back(0);
		//	}
		//	for (int i = 0; i < Funcs.size(); i++)
		//		FuncName.erase(FuncName.begin());
		//	auto start_time = chrono::high_resolution_clock::now();
		//	while (!SatFlag) {
		//		// nTransistors = 7;
		//		cout << endl << FuncName << " with " << nTransistors << " transistors: " << endl;
		//		TransistorNtk TMultiOutNtk = ConstructMultiOutTransistorNtk(nTransistors, Funcs.size(), FuncName);
		//		MultiOutTransistorCNF TMultiCnf(TMultiOutNtk, Funcs.size());
		//		TMultiCnf.InitVecMultiOutsCnfs(Funcs);
		//		/*TMultiCnf.InitGlobalVars();
		//		TMultiCnf.CreateGlobalClauses();*/
		//		vector<int> Tran2InputVars = TMultiCnf.CreatePriorClauses();

		//		int nRemainTransistors = TMultiOutNtk.iTransistors.size() - Tran2InputVars.size();
		//		nRemainTransistors = (nRemainTransistors < atoi(argv[2])) ? nRemainTransistors : atoi(argv[2]);
		//		if (nRemainTransistors) {
		//			int nCases = int(pow(Tran2InputVars.size(), nRemainTransistors));
		//			for (int i = 0; i < nCases; i++) {
		//				MultiOutTransistorCNF TMultiCnfTmp = TMultiCnf;
		//				vector<int> Tran2InputVarsTmp = Tran2InputVars;
		//				// create priorclauses for remaining transistors
		//				int iCase = i;
		//				for (int j = 0; j < nRemainTransistors; j++) {
		//					int iLiteral = iCase % Tran2InputVars.size();
		//					TMultiCnfTmp.CreateTransistorInputClauses(j + Tran2InputVars.size(), Tran2InputVars[iLiteral]);
		//					Tran2InputVarsTmp.push_back(Tran2InputVars[iLiteral]);
		//					iCase /= Tran2InputVars.size();
		//				}

		//				TMultiCnfTmp.MultiOutCreateClauses(Tran2InputVarsTmp);
		//				TMultiCnfTmp.GetAllClauses();
		//				TMultiCnfTmp.WriteCnf(argv[1] + TMultiOutNtk.NtkName + ".cnf");
		//				system(("minisat " + string(argv[1]) + TMultiOutNtk.NtkName + ".cnf " + string(argv[1]) + TMultiOutNtk.NtkName + "_out.cnf").c_str());
		//				// system(("minisat ./" + TMultiOutNtk.NtkName + ".cnf ./" + TMultiOutNtk.NtkName + "_out.cnf").c_str());
		//				TMultiCnfTmp.ParseCnf(argv[1] + TMultiOutNtk.NtkName + "_out.cnf", argv[1]);
		//				// TMultiCnfTmp.ParseCnf("./" + TMultiOutNtk.NtkName + "_out.cnf");
		//				if (TMultiCnfTmp.GetSatResult()) {
		//					SatFlag = 1;
		//					auto end_time = chrono::high_resolution_clock::now();
		//					auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
		//					fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVarsTmp, TMultiCnfTmp.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;

		//					break;
		//				}
		//			}
		//		}
		//		else {
		//			TMultiCnf.MultiOutCreateClauses(Tran2InputVars);
		//			TMultiCnf.GetAllClauses();
		//			TMultiCnf.WriteCnf(argv[1] + TMultiOutNtk.NtkName + ".cnf");
		//			system(("gtimeout 3600 minisat " + string(argv[1]) + TMultiOutNtk.NtkName + ".cnf " + string(argv[1]) + TMultiOutNtk.NtkName + "_out.cnf").c_str());
		//			TMultiCnf.ParseCnf(argv[1] + TMultiOutNtk.NtkName + "_out.cnf", argv[1]);
		//			if (TMultiCnf.GetSatResult()) {
		//				SatFlag = 1;
		//				auto end_time = chrono::high_resolution_clock::now();
		//				auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
		//				fExcel << TMultiOutNtk.NtkName << "," << NPTransistorsWithINV(Tran2InputVars, TMultiCnf.GetnVars(), nTransistors, OutInvFlags) << "," << elapsed_time.count() << "," << "SAT" << endl;
		//				// fExcel << TMultiOutNtk.NtkName << "," << nTransistors << "," << "UNSAT" << endl;
		//			}
		//		}
		//		nTransistors++;
		//	}
		//	
		//}
		//
		//fExcel.close();
	}


	// system("pause");
	return 0;
}