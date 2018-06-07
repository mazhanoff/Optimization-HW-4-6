// Newton.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>

using namespace std;

struct znach_x
{
	double x1, x2;
};

double f(double x1, double x2)
{
	double y;
	y = x1 * x1 - 2 * x1*x2 + x2*x2;
	return y;
}

double dfx1(double x1, double x2)
{
	double y;
	y = 2 * x1 - 2;
	return y;
}


double dfx2(double x1, double x2)
{
	double y;
	y = 2 * x2 - 2;
	return y;
}

double dfx1x1(double x1, double x2)
{	
	return 2;
}

double dfx2x2(double x1, double x2)
{
	return 2;
}

double dfx1x2(double x1, double x2)
{
	return 0;
}

void newton(int bx, int by, double epsilon, int& k)
{
	const int L = 1500;
	znach_x x[L];
	znach_x x_;
	double eps, y_, f1_1, f1_2, d, d1, d2, p1, p2, dlina, F;
	double f2[2][2];
	int N1, N2, N;

	x[0].x1 = bx;
	x[0].x2 = by;
	eps = epsilon;

	f1_1 = dfx1(x[0].x1, x[0].x2);
	f1_2 = dfx2(x[0].x1, x[0].x2);

	k = 0; N1 = 0; N2 = 0;
m1:
	f2[1][1] = dfx1x1(x[k].x1, x[k].x2);
	f2[1][2] = dfx1x2(x[k].x1, x[k].x2);
	f2[2][1] = f2[1][2];
	f2[2][2] = dfx2x2(x[k].x1, x[k].x2);

	N2 = N2 + 3;

	d = f2[1][1] * f2[2][2] - pow(f2[1][2], 2);
	d1 = f1_1 * f2[2][2] - f1_2 * f2[1][2];
	d2 = f2[1][1] * f1_2 - f2[2][1] * f1_1;

	p1 = d1 / d;
	p2 = d2 / d;

	x[k + 1].x1 = x[k].x1 - p1;
	x[k + 1].x2 = x[k].x2 - p2;
	
	//cout << (k + 1) << ") " << x[k + 1].x1 << "  " << x[k + 1].x2 << endl;

	f1_1 = dfx1(x[k + 1].x1, x[k + 1].x2);
	f1_2 = dfx2(x[k + 1].x1, x[k + 1].x2);

	N1 = N1 + 2;
	F = f1_1 * f1_1 + f1_2 * f1_2;
	dlina = sqrt(F);

	k++;

	if (dlina>eps)  goto m1;

	x_ = x[k];
	y_ = f(x_.x1, x_.x2);
	N = N1 + N2;	
	
	std::cout << "Значение: " << y_ << "\n";
	std::cout << "Точки: " << x_.x1 << ", " << x_.x2 << std::endl;

}

// Метод Ньютона основан на использовании квадратичной аппроксимации функции f в окрестности текущей точки xk 
// Таким образом, один шаг в методе Ньютона выглядит как xk+1 = xk − (Hk)^-1 * gk

void main()
{
	int choice;
	double d;
	setlocale(LC_ALL, "Russian");
	double x = 1.063, y = 1, epsilon = 0.000001;
	int k = 0;
	cout << "Решение задачи поиска минимума функции методом Ньютона\n";
	cout << "Ввести параметры схемы или взять их из готовой конфигурации?\n";
	cout << "1) Ввести параметры схемы\n";
	cout << "2) R1=2, R2=4, R3=5, R4=6, R5=8, R6=5, R7=3, E=5\n";
	cin >> choice;
	cout << "Введите свои значения потенциалов : \n";
	cout << "U1: "; cin >> d;
	cout << "U2: "; cin >> d;
	cout << "U3: "; cin >> d;
	cout << "Полученная целевая функция: U1^2 - 2*U1*U1z + U1z^2\n";
	cout << "Точность 1e-5, ограничение по итерациям отсутствует\n";
	cout << "Начальные точки: 10, 10\n";
	cout << "*****************************\n";
	float fTimeStart = clock() / (float)CLOCKS_PER_SEC;
	try {
		newton(x, y, epsilon, k);
	}
	catch(...){

	}
	float fTimeStop = clock() / (float)CLOCKS_PER_SEC;
	cout << endl << "Количество итераций: " << k << endl;
	cout << "Длительность процесса " << fTimeStop - fTimeStart << " секунд\n";
	std::cin >> x;
}

