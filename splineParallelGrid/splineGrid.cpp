#include "stdafx.h"

using namespace std;

const double a = 0; //����� �������
const double b = 1; //������ �������
const int n = 100; //����� �� x
const int m = 500; //����� �� t
const double h = (b - a) / n;
const double tau = h * h / 2; //��� �� t

double phi(double t) //��������� ������� ��� x = a
{
	return exp(-0.25 * t);
}

double psi(double t) //��������� ������� ��� x = b
{
	return exp(-0.25 * t) * cos(0.5);
}

double u0(double x) //��������� ������� ��� t = 0
{
	return cos(0.5 * x) + (1 - x) * x;
}

double omega2Derivative(int status) //������������ ������ ����������� ���������; status ������� � ���, � ����� ����� �� ������� ����������: j, j + 1 ��� j - 1
{
	if (status == 0)
		return 2 / (-h * h);
	if (status == -1)
		return 2 / (2 * h * h);
	if (status == 1)
		return 2 / (2 * h * h);
}

int _tmain(int argc, char*argv[])
{
	double u[n + 1][m];

	//����� �����
#pragma omp parallel for
	for (int i = 0; i <= n; i++)
		u[i][0] = phi(a + i * h);

	for (int k = 0; k < m - 1; k++)
	{
		u[0][k + 1] = phi((k + 1) * tau);
		u[n][k + 1] = psi((k + 1) * tau);
#pragma omp parallel for
		for (int i = 1; i < n; i++)
			u[i][k + 1] = (omega2Derivative(1) * u[i + 1][k] + (1 / tau + omega2Derivative(0)) * u[i][k] + omega2Derivative(-1) * u[i - 1][k]) * tau;
	}

	for (int k = 0; k < m; k += 50)
	{
		for (int i = 0; i <= n; i += 10)
			cout << u[i][k] << ' ';
		cout << endl;
	}

    return 0;
}
