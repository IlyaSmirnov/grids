#include "stdafx.h"

using namespace std;

const double a = 0; //левая граница
const double b = 1; //правая граница
const int n = 100; //сетка по x
const int m = 500; //сетка по t
const double h = (b - a) / n;
const double tau = h * h / 2; //шаг по t

double phi(double t) //граничное условие при x = a
{
	return exp(-0.25 * t);
}

double psi(double t) //граничное условие при x = b
{
	return exp(-0.25 * t) * cos(0.5);
}

double u0(double x) //граничное условие при t = 0
{
	return cos(0.5 * x) + (1 - x) * x;
}

int _tmain(int argc, char*argv[])
{
	double u[n + 1][m];

	//явная схема
	for (int i = 0; i <= n; i++)
		u[i][0] = phi(a + i * h);

	for (int k = 0; k < m - 1; k++)
	{
		u[0][k + 1] = phi((k + 1) * tau);
		u[n][k + 1] = psi((k + 1) * tau);
		for (int i = 1; i < n; i++)
			u[i][k + 1] = (tau / h / h) * u[i + 1][k] + (1 - 2 * tau / h / h) * u[i][k] + (tau / h / h) * u[i - 1][k];
	}

	for (int k = 0; k < m; k += 50)
	{
		for (int i = 0; i <= n; i += 10)
			cout << u[i][k] << ' ';
		cout << endl;
	}

	return 0;
}
