#pragma once
#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionNode.h"
#include "FeatureSelect.h"
class DecisionTree
{
public:
	DecisionTree();
	DecisionTree(vector<vector<int>> _data, vector<int> _kind, vector<string>&_name);
	~DecisionTree();
	DecisionNode * Creat(vector<vector<int>>& _data, vector<int>& _kind,vector<string>&_name);
	void PrintTree(DecisionNode * nowNode,int depth);
	DecisionNode *root;
	vector<vector<int>>data;
	vector<int>kind;
	vector<string>name;
	double delta;
private:

};



#endif