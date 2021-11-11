#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;

double a[40][40][40];
int b[43];
double hai(int x, int y, int z)
{
	double p = (x + y + z) / 2.0;
	return sqrt(p * (p - x) * (p - y) * (p - z));
}
int main() 
{
	int n;
	for (int i = 1;i <= n;i++)
	{
		cin >> b[i];
	}
	for(int i=1;i<=n;i++)
		for (int j = 1;j <= n;j++)
		{
			
		}


	return 0;
}

