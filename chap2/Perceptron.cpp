#pragma once
#include "my_funtion.h"
void OriginPerceptron()
{
	Mat X = (Mat_<double>(2, 3) << 3, 4, 1,
		3, 3, 1);
	cout << X << endl;
	Vec<double, 3> Y(1, 1, -1);
	cout << Y << endl;

	int n = 3;
	Vec<double, 2>w0;
	double b0 = 0, yita = 1;
	bool flag = 0;
	while (!flag)
	{
		flag = 1;
		for (int i = 0;i != 3;i++)
		{
			double check = Y(i) * (w0.dot(X.col(i)) + b0);
			if (sgn(check) <= 0)
			{
				Vec<double, 2>Xi = X.col(i);
				w0 = Xi*Y(i)*yita + w0;
				b0 = b0 + yita * Y(i);
				cout << "w = " << w0 << endl;
				cout << "b = " << b0 << endl;
				flag = 0;
			}
		}
	}
	cout << "w = " << endl;
	cout << w0 << endl;
	cout << "b = " << endl;
	cout << b0 << endl;
}

void DualPerceptron()
{
	const int N = 3;
	Mat X = (Mat_<double>(2, N) << 3, 4, 1,
		3, 3, 1);
	cout << X << endl;
	Vec<double, N> Y(1, 1, -1);
	cout << Y << endl;

	Vec<double, N>alpha;
	double b0 = 0, yita = 1;
	bool flag = 0;
	Mat Gram = CreatGramMat(X);
	cout << "Gram = " << endl;
	cout << Gram << endl;
	while (!flag)
	{
		flag = 1;
		for (int i = 0;i != 3;i++)
		{
			double check = b0;
			for (int j = 0;j != N;j++)
			{
				check += Y(j)*Gram.at <double>(j, i)*alpha(j);
			}
			check *= Y(i);
			if (sgn(check) <= 0)
			{
				alpha(i) += yita;
				b0 = b0 + yita * Y(i);
				cout << "---X" << i << "---" << endl;
				cout << "alpha = " << alpha << endl;
				cout << "b = " << b0 << endl;
				flag = 0;
			}
		}
	}
	cout << "alpha = " << endl;
	cout << alpha << endl;
	cout << "b = " << endl;
	cout << b0 << endl;
	cout << "w = " << endl;
	Vec<double, 2>w;
	for (int i = 0;i != N;++i)
	{
		Vec<double, 2> Xj = X.col(i);
		w += alpha(i) * Y(i)*Xj;
	}
	cout << w << endl;

}