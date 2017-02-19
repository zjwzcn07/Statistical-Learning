#pragma once
#ifndef BAYES_H
#define BAYES_H
#include "my_funtion.h"

class NaiveBayes
{
public:
	NaiveBayes(vector<vector<int>>_X, vector<int>_Y);
	NaiveBayes();
	~NaiveBayes();
	void Statistics();
	int Class(vector<int> sample);
	vector<vector<int>>X;
	vector<int>Y;
	map<int, double>count_y;
	map<int, double>priori_probability;
	vector<map<pair<int, int>, double>>count_xy;
	vector<map<pair<int, int>, double>>conditional_probability;
private:

};

class BayesEstimates
{
public:
	BayesEstimates();
	~BayesEstimates();
	BayesEstimates(vector<vector<int>>_X, vector<int>_Y,double _lambda);
	void Statistics();
	int Class(vector<int> sample);
	vector<vector<int>>X;
	vector<int>Y;
	map<int, double>count_y;
	map<int, double>priori_probability;
	vector<map<pair<int, int>, double>>count_xy;
	vector<map<pair<int, int>, double>>conditional_probability;
	vector<int>S;
	double lambda;
	int K;
private:

};


#endif
