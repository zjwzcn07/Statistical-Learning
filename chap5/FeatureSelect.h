#pragma once
#ifndef FEATURESELECT_H
#define FEATURESELECT_H

#include "my_funtion.h"

class FeatureSelect
{
public:
	FeatureSelect();
	FeatureSelect(vector<vector<int>>& _data, vector<int>&_kind,vector<string>&_name);
	~FeatureSelect();
	void Statistics();
	vector<map<int, double>>feature_count;
	vector<vector<int>>feature;
	vector<vector<int>>data;
	vector<int>kind;
	vector<double>conditional_entropy;
	vector<double>gain;
	vector<double>gain_ratio;
	pair<bool, int> only_one_Ck;//所有实例属于同一类，则将类Ck返回
	map<int, set<int>>feature_value;//每种特征的可能取值
	vector<string>name;
	double empirical_entropy;
	int max_gain_kind;
	bool no_feature;//没有特征值，则将实例数最大的类Ck返回
	int max_kind;
private:

};




#endif