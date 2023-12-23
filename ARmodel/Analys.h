#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
using namespace std;

class signal
{
	double f1, f2, f3, fd, E0;
	int N, N1, N2, L;

public:
	signal(double, double, double, double, int, int, int, int, double);
	void CreateFunc(vector<double>&);
	void ErrorFuture(vector<double> func, vector<double>& errorf);
	void Sglagiv(int, vector<double>, vector<double>&);
	double GetL();
	void FindPorog(double E0, vector<double> sr, vector<int>& finding);
	double GetE0();
};