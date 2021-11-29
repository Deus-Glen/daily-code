#include<iostream>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>

using namespace std;
typedef long long ll;

struct node{
    int x, y;
}a[10005],b[150],cost[10005];

int m, n, w;
int flag[10005];
int dp[10005][5005];

node all(int f)
{
    node sum;
    sum.x = 0;
    sum.y = 0;
    for (int i = 1;i <= m;i++)
    {
        if (b[i].x == f)
        {
            if (flag[b[i].x] != 1)
            {
                sum.x += a[b[i].y].x;
                sum.y += a[b[i].y].y;
                flag[b[i].x] = 1;
                sum.x += all(a[i].y).x;
                sum.y += all(a[i].y).y;
            }
        }
    }
    return sum;
}

int main()
{
    memset(flag, 0, sizeof(flag));
    memset(dp, 0, sizeof(0));
    cin >> n >> m >> w;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i].x >> a[i].y;
    }
    for (int i = 1;i <= m;i++)
    {
        cin >> b[i].x >> b[i].y;
    }
    for (int i = 1;i <= n;i++)
    {
        cost[i] = a[i];
    }
    for (int i = 1;i <= m;i++)
    {
        memset(flag, 0, sizeof(flag));
        cost[b[i].x] = all(b[i].x);
    }
    for (int i = 1;i <= n;i++)
    {
        for (int j = 0;j <= w;j++)
        {
            if (j < cost[i].x)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost[i].x] + cost[i].y);
            }
        }
    }
    int maxx = 0;
    for (int j = 0;j <= w;j++)
    {
        if (dp[n][j] > maxx)
            maxx = dp[n][j];
    }
    cout << maxx;
}