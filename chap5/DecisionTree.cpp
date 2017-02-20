#pragma once
#include "DecisionTree.h"

DecisionTree::DecisionTree()
{
}


DecisionTree::DecisionTree(vector<vector<int>>_data, vector<int>_kind, vector<string>&_name)
{
	data = _data;
	kind = _kind;
	name = _name;
}


DecisionTree::~DecisionTree()
{
}

DecisionNode* DecisionTree::Creat(vector<vector<int>>&_data, vector<int>&_kind, vector<string>&_name)
{
	DecisionNode *Node = new DecisionNode;
	FeatureSelect myFeature(_data, _kind, _name);
	myFeature.Statistics();
	if (myFeature.only_one_Ck.first)
	{
		Node->kind = myFeature.only_one_Ck.second;
		Node->name = to_string(myFeature.only_one_Ck.second);
		if (root == NULL)
			root = Node;
		return Node;
	}
	if (myFeature.no_feature)
	{
		Node->kind = myFeature.max_kind;
		Node->name = to_string(myFeature.max_kind);
		if (root == NULL)
			root = Node;
		return Node;
	}
	int Ag = myFeature.max_gain_kind;
	double Ag_gain = myFeature.gain[Ag];
	if (Ag_gain < delta)
	{
		Node->kind = myFeature.max_kind;
		Node->name = to_string(myFeature.max_kind);
	}
	else {
		Node->feature = Ag;
		Node->name = _name[Ag];
		map<int, vector<vector<int>>>NewData;
		map<int, vector<int>>NewKind;
		vector<string>NewName;
		NewData.clear();
		NewKind.clear();
		NewName.clear();
		int kind_num = _data.front().size();
		for (int i = 0;i != kind_num;++i)
		{
			if (i != Ag)
				NewName.push_back(_name[i]);
		}

		//将原始数据以Ag对应的每一个可能值ai分类，特征不再包括Ag
		int data_num = _data.size();
		for (int j = 0;j != data_num;++j)
		{
			vector<int>each_data = _data[j];
			int ai = each_data[Ag];
			vector<int>NewRows;
			NewRows.clear();
			int sz = each_data.size();
			for (int i = 0;i != sz;++i)
			{
				if (i != Ag)
				{
					NewRows.push_back(each_data[i]);
				}
			}
			NewKind[ai].push_back(_kind[j]);
			NewData[ai].push_back(NewRows);
		}
		for (auto ai : myFeature.feature_value[Ag])
		{
			Node->child.push_back(make_pair(ai, Creat(NewData[ai], NewKind[ai], NewName)));
		}
	}
	if (root == NULL)
		root = Node;
	return Node;
}

void DecisionTree::PrintTree(DecisionNode* nowNode,int depth)
{
	if (nowNode == NULL)
		return;
	for (int i = 0;i < depth;i++)
		cout << "        ";
	nowNode->PrintNode();
	for (auto child : nowNode->child)
	{
		cout << "-( " << child.first << " )-";
		PrintTree(child.second,depth+1);
	}
}
