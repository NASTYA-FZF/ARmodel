#include "pch.h"
#include "Analys.h"

signal::signal(double F1, double F2, double F3, double Fd, int n, int n1, int n2, int l, double e)
{
	f1 = F1;
	f2 = F2;
	f3 = F3;
	fd = Fd;
	N = n;
	N1 = n1;
	N2 = n2;
	L = l;
	E0 = e;
}

void signal::CreateFunc(vector<double>& function)
{
	double CurPhase = 0;
	for (int i = 0; i < N; i++)
	{
		function.push_back(sin(CurPhase));
		if (i <= N1) CurPhase += 2 * M_PI * f1 / fd;
		else if (i <= N2) CurPhase += 2 * M_PI * f2 / fd;
		else CurPhase += 2 * M_PI * f3 / fd;
	}
}

void signal::ErrorFuture(vector<double> func, vector<double>& errorf)
{
	double a1 = -2.0 * cos(2.0 * M_PI * f2 / fd);
	vector<double> future;
	future.push_back(func[0]);
	future.push_back(func[1]);
	for (int i = 2; i < N; i++)
	{
		future.push_back(-a1 * func[i - 1] - func[i - 2]);
		errorf.push_back((future[i] - func[i]) * (future[i] - func[i]));
	}
}

void signal::Sglagiv(int L, vector<double> errorf, vector<double>& sred)
{
	double work;
	for (int t = 0; t < errorf.size() - L; t++)
	{
		work = 0;
		for (int i = t; i < L + t; i++)
		{
			work += errorf[i] / L;
		}

		sred.push_back(work);
	}
}

double signal::GetL()
{
	return L;
}

void signal::FindPorog(double E0, vector<double> sr, vector<int>& finding)
{
	bool fl1 = true, fl2 = true;
	int num = sr.size() - 1, n1, n2;
	for (int i = 0; i < sr.size(); i++)
	{
		if (fl1 && sr[i] <= E0)
		{
			n1 = i + L / 2;
			fl1 = false;
		}

		if (fl2 && sr[num - i] <= E0)
		{
			n2 = num - i + L / 2;
			fl2 = false;
		}
	}
	finding.push_back(n1);
	finding.push_back(n2);
}

double signal::GetE0()
{
	return E0;
}
