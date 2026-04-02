#pragma once
#ifndef __MUSTNET_NTK_H__
#define __MUSTNET_NTK_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

struct MosNode {
	int id;
};

struct NetNode {
	int id;
	int type; // 0: internal, 1: source (VDD/GND), 2: output
	string name;
};

struct MustNetNtk {
	int T; // number of MOS transistors
	vector<MosNode> mosNodes;   // T MOS nodes
	vector<NetNode> netNodes;   // T+1 net nodes
	string NtkName;

	// Net pair indexing helpers
	vector<pair<int,int>> allPairs;       // all (i,j) with i<j
	map<pair<int,int>, int> pairToIdx;

	int nPairs() const { return (int)allPairs.size(); }

	int pairIndex(int i, int j) const {
		if (i > j) { int tmp = i; i = j; j = tmp; }
		auto it = pairToIdx.find({i, j});
		return it->second;
	}
};

MustNetNtk ConstructMustNetNtk(int nTransistors, string Name);

#endif
