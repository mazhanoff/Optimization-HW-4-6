// Conj.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#include <iostream>
#include <cmath>
#include <conio.h>
using namespace std;

/*A = [
[1+1/3+1/4,    -1/4,         0],
[-1/4,          1/4+1/2+1/3, 0],
[0,            -1/3,         1/3+1/2],
]
b = [5,-3,3]*/


double f(double  x1, double x2) {
	return 4 * (x1 - 15)*(x1 - 5) + (x2 - 6)*(x2 - 9);
}
//return 2*x1*x1+x1*x2+x2*x2;}
//return pow(2*(pow(x1,2))*(x2+3),1.0/3); }
int main() {
	double E = 0.1, min, var[200], t;
	int i, j, n = 2, k = 0;
	int s = 0, I[100];

	double d[3][3] = { { 0,1 },{ 1,0 },{ 0,1 } };    /*cout <<d[0][0]<<" "<<d[0][1]<<" "<<
													 d[1][0]<<" "<<d[1][1]<<" "<<
													 d[2][0]<<" "<<d[2][1]<<endl;*/
	double X[100][100], Y[100][200], Xz[1][2];

	I[s] = 0;
	cout << "Elements:" << endl;           //нач. точку Хо
	for (int i = 0; i<1; i++)
		for (int j = 0; j<2; j++)
			cin >> X[i][j];           cout << "X(" << X[0][0] << ";" << X[0][1] << ")\n";

	for (i = 0; i<1; i++)             //Y0 = Xo
		for (j = 0; j<2; j++)
			Y[i][j] = X[i][j];         cout << "Y(" << Y[0][0] << ";" << Y[0][1] << ")\n";
	//.2.........................
TWO:  cout << " __2__" << endl;
	min = f(Y[I[s]][0], Y[I[s]][1]);

	i = 0;
	for (double t = -50; t<50; t++, i++)    //вывод различных значений ф-ции
	{
		var[i] = f(Y[I[s]][0] + t * d[I[s]][0], Y[I[s]][1] + t * d[I[s]][1]);
		cout << "step = " << i << ";  var [" << i << "] = " << var[i] << ";   grad[" << i << "] = " << var[i] / 1292 << endl;
	}
	for (int i = 0; i<100; i++)      //вывод наименьшего значения ф-ции
		if (var[i] < min)
			min = var[i];
	cout << "min var[] = " << min << endl;
	for (int index = 0; index<100; index++)  //вывод t
	{
		if (min == var[index])
			t = index - 50;
	}

	cout << "T = " << t << endl;

	Y[I[s] + 1][0] = Y[I[s]][0] + t * d[I[s]][0];
	Y[I[s] + 1][1] = Y[I[s]][1] + t * d[I[s]][1];
	cout << "Y[" << I[s] + 1 << "] = (" << Y[I[s] + 1][0] << ";";
	cout << Y[I[s] + 1][1] << ")" << endl;
	//.3............................
THREE:  cout << " __3__" << endl;
	if (I[s] < n - 1)
	{
		cout << "I[s] < n-1" << endl;
		I[s] = I[s] + 1;
		cout << "I[s] = " << I[s] << endl;
		goto TWO;
	}   //*/
	if (I[s] == n - 1)
	{
		cout << "I[s] == n-1" << endl;
		if ((Y[n][0] == Y[0][0]) && (Y[n][1] == Y[0][1])) {
			Xz[0][0] = Y[n][0];        cout << "Xz(" << Xz[0][0] << ";";
			Xz[0][1] = Y[n][1];        cout << Xz[0][1] << ")" << endl;
		}
		else {
			cout << "Yn != Y0 " << endl;
			I[s] = I[s] + 1;
			cout << "I[s] = " << I[s] << endl;
			goto TWO;
		}
	}
	if (I[s] == n)
	{
		cout << "I[s]  == n" << endl;
		if ((Y[n + 1][0] == Y[1][0]) && (Y[n + 1][1] == Y[1][1])) {
			Xz[0][0] = Y[n + 1][0];        cout << "Xz(" << Xz[0][0] << ";";
			Xz[0][1] = Y[n + 1][1];        cout << Xz[0][1] << ")" << endl;
		}
		if ((Y[n + 1][0] != Y[1][0]) || (Y[n + 1][1] != Y[1][1])) {
			goto Fourth;
		}
	}
	//.4.........................
Fourth:  cout << " __4__" << endl;
	X[k + 1][0] = Y[n + 1][0];    cout << "X[" << (k + 1) << "] = (" << X[k + 1][0];
	X[k + 1][1] = Y[n + 1][1];    cout << ";" << X[k + 1][1] << ")" << endl;
	//...........a...............
	if (pow((pow((X[k + 1][0] - X[k][0]), 2) + pow((X[k + 1][1] - X[k][1]), 2)), 1 / 2.0)<E) {
		cout << "X(k+1) - X(k) = " << pow((pow((X[k + 1][0] - X[k + 1][0]), 2) +
			pow((X[k + 1][1] - X[k + 1][1]), 2)), 1 / 2.0);

		Xz[0][0] = X[k + 1][0];
		Xz[0][1] = X[k + 1][1];
	}
	//..................b.....................
	if (pow((pow((X[k + 1][0] - X[k][0]), 2) + pow((X[k + 1][1] - X[k][1]), 2)), 1 / 2.0)>E) {

		d[0][0] = d[n][0] = Y[n + 1][0] - Y[1][0];    cout << "d0 = (" << d[0][0];
		d[0][1] = d[n][1] = Y[n + 1][1] - Y[1][1];    cout << ";" << d[0][1] << ")" << endl;

		d[I[s]][0] = d[I[s] + 1][0];
		d[I[s]][1] = d[I[s] + 1][1];
		if ((d[1][0] * d[2][1] - d[1][1] * d[2][0]) != 0) {
			cout << "rang(D1,...,Dn) = n" << endl;
			Y[0][0] = X[k + 1][0];  cout << "Y0 = (" << Y[0][0] << ";";
			Y[0][1] = X[k + 1][1];  cout << Y[0][1] << ")\n";
			k = k + 1;
			I[s] = 0;
			goto TWO;
		}
		if ((d[1][0] * d[2][1] - d[1][1] * d[2][0]) == n) {
			cout << "rang(D1,...,Dn) < n" << endl;
			Y[0][0] = X[k + 1][0];
			Y[0][1] = X[k + 1][1];
			k = k + 1;
			I[s] = 0;
			goto TWO;
		}
	}
	cout << "\nMin in Xz(" << Xz[0][0] << ";" << Xz[0][1] << ";0)" << endl;
	_getch();
}


