#pragma once
#ifndef DECISIONNODE_H
#define DECISIONNODE_H
#include "my_funtion.h"

class DecisionNode
{
public:
	DecisionNode();
	~DecisionNode();
	void PrintNode();
	int feature;
	int kind;
	string name;
	vector<pair<int, DecisionNode*>>child;
	pair<int, DecisionNode*>parent;
private:

};



#endif