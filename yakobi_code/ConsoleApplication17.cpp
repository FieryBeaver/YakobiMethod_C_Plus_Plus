// ConsoleApplication17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;
double vectNorm(vector<double> & N)
{
	double max = fabs(N[0]);
	for (int i = 1; i < N.size(); i++)
	{
		max = max < fabs(N[i]) ? fabs(N[i]) : max;
	}
	
	return max;
}
bool getToEAccuracy(vector<double> &x, vector<double> &prevx,double E)
{
	
	
	if (fabs(vectNorm(x) - vectNorm(prevx)) < E)return true;
	return false;
}
void show(vector <vector <double>> A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "\t" << A[i][j] << "\t";
		}
		cout << endl;
	}
}
void show(vector <double> A) 
{
	for (int i = 0; i < A.size(); i++)
	{
		cout << "\t" << A[i] << "\t";
	}
}

bool Check(vector <double> &B, vector<vector<double>> &Matrix)
{

	int n = Matrix.size();
	if (B.size() != n)
	{
		cout << "No match in Vector and Matrix Len ";
		return false;
	}


	//==================Check if matrix have diagonal overweight==========================
	for (int i = 0;i < n;i++)
	{
		int sum = 0;

		for (int j = 0; j < n; j++)	//
		{							//finding sum of element in row
			sum += fabs(Matrix[i][j]);	//
		}							//
		
		if (fabs(2 * Matrix[i][i]) < sum)
		{
			cout << " matrix haven't diagonal overweight, and I'm too lazy to convert it pls enter other Matrix";
			return false;// get out from function
		}
		
	}
	return true;
	
}
void YakobiSlar(vector <double> &B, vector<vector<double>> &Matrix)
{
	if (!Check(B, Matrix))return;
	int n=Matrix.size();
	//======find max el
	double max = B[0];
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			max = max < Matrix[i][j] ? Matrix[i][j] : max;
		}
		max = max < B[i] ? B[i] : max;
	}

	//====norm matrix
	for (int i = 0; i < n; i++)
	{
		B[i] /= max;
		for (int j = 0; j < n; j++)
		{
			Matrix[i][j] /= max;
		}
	}


	//======= Yakobi

	cout << "enter E pls\n";
	double E; cin >> E;
	vector <double> x,pr_x;
	for (int i = 0;i < n;i++)x.push_back(Matrix[i][i]/B[i]);
	
	int iter = 0;
	
	do
	{
		//cout << " test";
		pr_x = x;
		for (int i = 0; i < n; i++)
		{
			x[i] = B[i] / Matrix[i][i];
			for (int j = 0;j < n;j++)
			{	
				if(j!=i)
				x[i] += (Matrix[i][j] * pr_x[j])/Matrix[i][i];
			}
		}
		iter++;
		//cout << iter<<endl;
	} while (!getToEAccuracy(x, pr_x, E));

	show(x);
	cout << " \n\n\n\t===";
	cout << iter;
}
int main()
{
	const int n = 3;
	vector <vector <double>> A(n);
	vector <double> R;
	double inpt;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> inpt;
			A[i].push_back(inpt);
		}
		cin >> inpt;
		R.push_back(inpt);
	}
	show(A,n);
	YakobiSlar(R, A);
	
}

