#include "MustNetNtk.h"

MustNetNtk ConstructMustNetNtk(int nTransistors, string Name) {
	MustNetNtk ntk;
	ntk.T = nTransistors;
	ntk.NtkName = Name;

	// Create T MOS nodes
	for (int i = 0; i < nTransistors; i++) {
		MosNode m;
		m.id = i;
		ntk.mosNodes.push_back(m);
	}

	// Create T+1 net nodes
	int nNets = nTransistors + 1;
	for (int i = 0; i < nNets; i++) {
		NetNode n;
		n.id = i;
		if (i == 0) {
			n.type = 1; // source
			n.name = "Source";
		} else if (i == nNets - 1) {
			n.type = 2; // output
			n.name = "Output";
		} else {
			n.type = 0; // internal
			n.name = "n" + to_string(i);
		}
		ntk.netNodes.push_back(n);
	}

	// Build all net pairs (i,j) with i < j
	int idx = 0;
	for (int i = 0; i < nNets; i++) {
		for (int j = i + 1; j < nNets; j++) {
			ntk.allPairs.push_back({i, j});
			ntk.pairToIdx[{i, j}] = idx;
			idx++;
		}
	}

	return ntk;
}
