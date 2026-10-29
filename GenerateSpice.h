#ifndef __GENERATE_SPICE__
#define __GENERATE_SPICE__
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "PathLimitation.h"
using namespace std;
typedef struct transistor_ {
	string Gate;
	string Source;
	string Drain;
	string Substrate;
	string Mos;
	float W = 0;
	float L = 0.05; // 45 NM
	// float L = 16; // 7 NM
	int lambda = 2;
	float basicW = 0.25; // 45 NM
	// float basicW = 23; // 7 NM
	int nFin;

	int maxPathLength = 0; // the maximum path length of the transistor
}transistor;

// How writeSpice renders the netlist, as opposed to what is in it.
typedef struct SpiceOptions_ {
	// Width and length for every transistor, in microns.  Negative keeps the
	// per-transistor value the synthesis chose (1.5u/0.75u pMOS/nMOS, 0.5u/
	// 0.25u for the inverters), which is what this tool always emitted.  Set
	// them to size the whole cell uniformly instead -- needed to compare a
	// netlist against one from another tool, where a width difference would
	// otherwise be indistinguishable from a topology difference.
	double W = -1;
	double L = -1;
	// Emit the two .model cards.  A SPICE simulator needs them; Astran's
	// netlist reader stops at them, in or out of the .subckt, and then reports
	// only "Could not find cell netlist", so they are off by default and the
	// netlist is laid out as-is.
	bool models = false;
}SpiceOptions;

vector<transistor> DeriveSourceDrains(vector<pair<pair<int, int>, string>> transistors_pairs);
vector<transistor> transformTransistors(int nClusters, int InputClusterID, int OutClusterID, vector<pair<pair<int, int>, string>> transistors_pairs, int mos);
void writeSpice(string file, string CircktName, set<string> AllLiterals, vector<transistor> transistorsPUN, vector<transistor> transistorsPDN, map<string, int> path_statistics, SpiceOptions opt = SpiceOptions());
void GenerateTransistors(set<string> AllLiterals, vector<transistor>& transistorsPUN, vector<transistor>& transistorsPDN);
void GenerateTransistors(set<string> AllLiterals, vector<transistor>& transistorsPUN, vector<transistor>& transistorsPDN, int OutINV);
vector<transistor> transformTransistors(int nClusters, int InputClusterID, int OutClusterID, vector<pair<pair<int, int>, string>> transistors_pairs, map<pair<int, int>, int> transistors_Counts, int mos, int OutINV);
#endif // !__GENERATE_SPICE__
