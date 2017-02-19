#pragma once
#ifndef MYFUNTION_H
#define MYFUNTION_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/matx.hpp>

using namespace cv;
using namespace std;
static double eps = 1e-8;

int sgn(double x);
Mat CreatGramMat(Mat X);
double dPow(double x, int n);
double LpDistance(Mat Xi, Mat Xj, int p);
double LpDistance(vector<double> Xi, vector<double> Xj, int p);

#endif