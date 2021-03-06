// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
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
	y = x1 * x1 + 2 * x1*x2 + 3 * x2*x2 - 2 * x1 - 3 * x2;
	return y;
}

double dfx1(double x1, double x2)
{
	double y;
	y = 2 * x1 + 2 * x2 - 2;
	return y;
}


double dfx2(double x1, double x2)
{
	double y;
	y = 2 * x1 + 6 * x2 - 3;
	return y;
}

double dfx1x1(double x1, double x2)
{
	return 2;
}

double dfx2x2(double x1, double x2)
{
	return 6;
}

double dfx1x2(double x1, double x2)
{
	return 2;
}

void newton_rafs_optim(int bx, int by, double epsilon, int& k)
{
	const int L = 1500;
	znach_x x[L];
	znach_x x_;
	double eps, y_, f1_1, f1_2, d, d1, d2, p1, p2, dlina, F, y1, y2, A, B;
	double a1, a2, amin, da=0.0001, d0, a, f1, f3;
	double f2[2][2];
	int i, N1, N2, N, N0;
	
	x[0].x1 = bx;
	x[0].x2 = by;
	eps = epsilon;

	f1_1 = dfx1(x[0].x1, x[0].x2);
	f1_2 = dfx2(x[0].x1, x[0].x2);

	k = 0; N1 = 0; N2 = 0; N0 = 0;
m2:
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
	//opredel A,B
	y1 = f(x[k].x1, x[k].x2);
	i = 0;
m5:
	y2 = f(x[k].x1 - ((i + 1)*da)*p1, x[k].x2 - ((i + 1)*da)*p2);

	N0++;
	if (y2<y1) { i++; y1 = y2; goto m5; }
	else {
		B = (1 + i)*da;
		if (i>0) A = (i - 1)*da;
		else A = 0;
	}
	//cout<<"A="<<A<<" B="<<B<<endl;

	d0 = eps / 100;
	do
	{
		a = (A + B) / 2.0;
		a1 = a - d0;
		a2 = a + d0;
		f1 = f(x[k].x1 - a1 * p1, x[k].x2 - a1 * p2);
		f3 = f(x[k].x1 - a2 * p1, x[k].x2 - a2 * p2);
		N0 = N0 + 2;
		if (f1<f3) B = a2;
		else A = a1;
	} while (B - A>2 * eps);

	amin = (A + B) / 2.0;

	x[k + 1].x1 = x[k].x1 - amin * p1;
	x[k + 1].x2 = x[k].x2 - amin * p2;

	//cout << (k + 1) << ") " << x[k + 1].x1 << " " << x[k + 1].x2 << endl;

	f1_1 = dfx1(x[k + 1].x1, x[k + 1].x2);
	f1_2 = dfx2(x[k + 1].x1, x[k + 1].x2);

	N1 = N1 + 2;
	F = f1_1 * f1_1 + f1_2 * f1_2;

	dlina = sqrt(F);

	k++;
	if (dlina>eps)	  goto m2;

	x_ = x[k];
	y_ = f(x_.x1, x_.x2);
	N = N1 + N2 + N0;
	
	std::cout << "Значение: " << y_ << "\n";
	std::cout << "Точки: " << x_.x1 << ", " << x_.x2 << std::endl;
}

//Метод Ньютона — Рафсона является улучшением метода Ньютона нахождения экстремума, описанного выше. 
//Основное отличие заключается в том, что на очередной итерации каким-либо из методов одномерной оптимизации выбирается оптимальный шаг
//https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%9D%D1%8C%D1%8E%D1%82%D0%BE%D0%BD%D0%B0#%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D0%BD%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE_%D0%BA_%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B0%D0%BC_%D0%BE%D0%BF%D1%82%D0%B8%D0%BC%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8

void main()
{
	setlocale(LC_ALL, "Russian");
	double x = 10, y = 10, epsilon = 0.00001;
	int k = 0;
	cout << "Решение задачи поиска минимума функции методом Ньютона-Рафсона с оптимальным шагом\n";
	cout << "Функция x^2 + 2xy + 3y^2 - 2x - 3y\n";
	cout << "Точность 1e-5, ограничение по итерациям отсутствует\n";
	cout << "В качестве метода одномерной оптимизации использовался метод золотого сечения\n";
	cout << "Начальные точки: 10, 10\n";
	cout << "*****************************\n";
	float fTimeStart = clock() / (float)CLOCKS_PER_SEC;
	try {
		newton_rafs_optim(x, y, epsilon, k);
	}
	catch (...) {

	}
	float fTimeStop = clock() / (float)CLOCKS_PER_SEC;
	cout << endl << "Количество итераций: " << k << endl;
	cout << "Длительность процесса " << fTimeStop - fTimeStart << " секунд\n";
	std::cin >> x;
}
