#include "Bayes.h"

NaiveBayes::NaiveBayes(vector<vector<int>>_X, vector<int>_Y)
{
	X = _X;
	Y = _Y;
}

NaiveBayes::NaiveBayes()
{
}

NaiveBayes::~NaiveBayes()
{
}

void NaiveBayes::Statistics()
{
	try
	{
		int rows = X.size();
		int cols = X.front().size();
		for (int i = 0;i != cols;i++)
		{
			count_xy.push_back(map<pair<int, int>, double>());
			conditional_probability.push_back(map<pair<int, int>, double>());
		}
		for (int i = 0;i != rows;++i)
		{
			count_y[Y[i]]++;
			for (int j = 0;j != cols;++j)
			{
				count_xy[j][make_pair(X[i][j], Y[i])]++;
			}
		}



		double N = rows;
		for (auto y : count_y)
		{
			priori_probability[y.first] = y.second / N;
		}
		int eigen_sz = count_xy.size();
		for (int i = 0;i != eigen_sz;++i)
		{
			for (auto xy : count_xy[i])
			{
				conditional_probability[i][xy.first] = xy.second / count_y[xy.first.second];
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "No empty";
	}
}





int NaiveBayes::Class(vector<int> sample)
{
	map<int, double>arg_y;
	arg_y.clear();
	int eigen_sz = count_xy.size();
	for (auto ck : count_y)
		arg_y[ck.first] = 1;
	for (int i = 0;i != eigen_sz;++i)
	{
		int xj = sample[i];
		for (auto ck : count_y)
		{
			arg_y[ck.first] *= conditional_probability[i][make_pair(xj, ck.first)];
		}
	}
	int ans_y = 0;//未定义
	double pro = 0;
	for (auto y : priori_probability)
	{
		arg_y[y.first] *= y.second;
		double this_pro = arg_y[y.first];
		cout << "Y = " << y.first << " = " << this_pro << endl;
		if (this_pro > pro)
		{
			pro = this_pro;
			ans_y = y.first;
		}
	}
	return ans_y;
}


BayesEstimates::BayesEstimates(vector<vector<int>>_X, vector<int>_Y, double _lambda)
{
	X = _X;
	Y = _Y;
	lambda = _lambda;
}

BayesEstimates::BayesEstimates()
{
}

BayesEstimates::~BayesEstimates()
{
}

void BayesEstimates::Statistics()
{
	try
	{
		int rows = X.size();
		int cols = X.front().size();
		for (int i = 0;i != cols;i++)
		{
			count_xy.push_back(map<pair<int, int>, double>());
			conditional_probability.push_back(map<pair<int, int>, double>());
		}
		for (int i = 0;i != rows;++i)
		{
			count_y[Y[i]]++;
			for (int j = 0;j != cols;++j)
			{
				count_xy[j][make_pair(X[i][j], Y[i])]++;
			}
		}
		for (int j = 0;j != cols;++j)
		{
			map<int, bool>kind_x;
			kind_x.clear();
			for (int i = 0;i != rows;++i)
			{
				kind_x[X[i][j]] = 1;
			}
			S.push_back(kind_x.size());
		}
		K = count_y.size();



		double N = rows;
		for (auto y : count_y)
		{
			priori_probability[y.first] = (y.second + lambda) / (N + K*lambda);
		}
		int eigen_sz = count_xy.size();
		for (int i = 0;i != eigen_sz;++i)
		{
			for (auto xy : count_xy[i])
			{
				conditional_probability[i][xy.first] = (xy.second + lambda) / (count_y[xy.first.second] + S[i] * lambda);
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "No empty";
	}
}





int BayesEstimates::Class(vector<int> sample)
{
	map<int, double>arg_y;
	arg_y.clear();
	int eigen_sz = count_xy.size();
	for (auto ck : count_y)
		arg_y[ck.first] = 1;
	for (int i = 0;i != eigen_sz;++i)
	{
		int xj = sample[i];
		for (auto ck : count_y)
		{
			arg_y[ck.first] *= conditional_probability[i][make_pair(xj, ck.first)];
		}
	}
	int ans_y = 0;//未定义
	double pro = 0;
	for (auto y : priori_probability)
	{
		arg_y[y.first] *= y.second;
		double this_pro = arg_y[y.first];
		cout << "Y = " << y.first << " = " << this_pro << endl;
		if (this_pro > pro)
		{
			pro = this_pro;
			ans_y = y.first;
		}
	}
	return ans_y;
}

void NaiveBayesExample()
{
	vector<vector<int>>X{ { 1,1 },{ 1,2 },{ 1,2 },{ 1,1 },{ 1,1 },{ 2,1 },{ 2,2 },{ 2,2 },{ 2,3 },{ 2,3 },{ 3,3 },
	{ 3,2 },{ 3,2 },{ 3,3 },{ 3,3 } };
	vector<int>Y{ -1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,1,-1 };
	NaiveBayes myBayes(X, Y);
	myBayes.Statistics();
	cout << "P(y) = " << endl;
	for (auto y : myBayes.priori_probability)
	{
		cout << "P(Y=" << y.first << ")=" << y.second << endl;
	}
	cout << "conditional_probability = " << endl;
	for (int i = 0;i != 2;i++)
	{
		cout << "eigen " << i << endl;
		for (auto prob : myBayes.conditional_probability[i])
		{
			cout << "X = " << prob.first.first << "Y = " << prob.first.second << "prob = " << prob.second << endl;
		}
	}
	vector<int>testX{ 2,1 };
	int ans_y = myBayes.Class(testX);
	cout << "class result y = " << ans_y << endl;
}

void BayesEstimates()
{
	vector<vector<int>>X{ { 1,1 },{ 1,2 },{ 1,2 },{ 1,1 },{ 1,1 },{ 2,1 },{ 2,2 },{ 2,2 },{ 2,3 },{ 2,3 },{ 3,3 },
	{ 3,2 },{ 3,2 },{ 3,3 },{ 3,3 } };
	vector<int>Y{ -1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,1,-1 };
	BayesEstimates myBayes(X, Y, 1);
	myBayes.Statistics();
	cout << "P(y) = " << endl;
	for (auto y : myBayes.priori_probability)
	{
		cout << "P(Y=" << y.first << ")=" << y.second << endl;
	}
	cout << "conditional_probability = " << endl;
	for (int i = 0;i != 2;i++)
	{
		cout << "eigen " << i << endl;
		for (auto prob : myBayes.conditional_probability[i])
		{
			cout << "X = " << prob.first.first << "Y = " << prob.first.second << "prob = " << prob.second << endl;
		}
	}
	vector<int>testX{ 2,1 };
	int ans_y = myBayes.Class(testX);
	cout << "class result y = " << ans_y << endl;
}