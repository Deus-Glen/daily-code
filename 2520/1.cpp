#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;

double a[40][40];
int b[43];
double hai(int x, int y, int z)
{
	double p = (x + y + z) / 2.0;
	return sqrt(p * (p - x) * (p - y) * (p - z));
}
int main() 
{
	int n, sum = 0;
	for (int i = 1;i <= n;i++)
	{
		cin >> b[i];
		sum += b[i];
	}
	for (int k = 1;k <= n;k++)
	{
		for (int i = sum / 2;i > 0;i--)
			for (int j = sum / 2;j > 0;j--)
			{
				s
			}
	}


	return 0;
}

