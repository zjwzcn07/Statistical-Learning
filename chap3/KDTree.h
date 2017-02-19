#ifndef KDTREE_H
#define KDTREE_H

#include "KnnNode.h"

class KDTree
{
public:
	KDTree();
	KDTree(int _N);
	~KDTree();
	void PrintSegment(vector<vector<double>>& segment);
	void PrintNode(KnnNode * nowNode);
	KnnNode *Create(vector<vector<double>> &segment, int depth);
	void NearestSearch(int depth, KnnNode * now_node, vector<KnnNode*>& path, const vector<double>& target, KnnNode& now_goal, double &now_distance, bool back, int lp);
	KnnNode *root;
	int N;
private:

};

#endif