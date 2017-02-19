#include"my_funtion.h"
int sgn(double x)
{
	if (fabs(x) < eps)
		return 0;
	else if (x < 0)
		return -1;
	else
		return 1;
}

Mat CreatGramMat(Mat X)
{
	int N = X.cols;
	Mat Gram = (Mat_<double>(N, N));
	for (int i = 0;i != X.cols;i++)
	{
		for (int j = 0;j != X.cols;j++)
		{
			Gram.at<double>(i, j) = X.col(i).dot(X.col(j));
		}
	}
	return Gram;
}

double dPow(double x, int n)
{
	double ans = 1;
	while (n)
	{
		if (n & 1)
			ans *= x;
		x *= x;
		n >>= 1;
	}
	return ans;
}

double LpDistance(Mat Xi, Mat Xj, int p)
{
	double dis = 0;
	for (int i = 0;i != Xi.rows;++i)
	{
		double d = fabs(Xi.at<double>(i, 0) - Xj.at<double>(i, 0));
		d = dPow(d, p);
		dis += d;
	}
	return pow(dis, 1.0 / p);
}

double LpDistance(vector<double> Xi, vector<double> Xj, int p)
{
	double dis = 0;
	int rows = Xi.size();
	for (int i = 0;i != rows;++i)
	{
		double d = fabs(Xi[i] - Xj[i]);
		d = dPow(d, p);
		dis += d;
	}
	return pow(dis, 1.0 / p);
}