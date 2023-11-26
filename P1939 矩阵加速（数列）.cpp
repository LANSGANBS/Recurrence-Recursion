#include <bits/stdc++.h>
#define endl '\n'
#define buff ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
/*
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize(3)
*/
using namespace std;
#define ll long long
#define int ll
const int mod = 1e9 + 7;

struct Genshin_Impact
{
    int a[4][4];
} ss;

int k, t;

Genshin_Impact X(Genshin_Impact s, Genshin_Impact kk)
{
    Genshin_Impact cx;
    memset(cx.a, 0, sizeof(cx.a));
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
            {
                cx.a[i][j] += (s.a[i][k] * kk.a[k][j]) % mod;
                cx.a[i][j] %= mod;
            }
    return cx;
}

Genshin_Impact quick_pow(Genshin_Impact kk, int n)
{
    if (n <= 1)
        return kk;
    Genshin_Impact cx = kk;
    n--;
    while (n > 0)
    {
        if (n % 2 == 1)
            cx = X(cx, kk);
        n /= 2;
        kk = X(kk, kk);
    }
    return cx;
}

signed main()
{
    buff;
    memset(ss.a, 0, sizeof(ss.a));
    ss.a[1][1] = 1;
    ss.a[3][1] = 1;
    ss.a[1][2] = 1;
    ss.a[2][3] = 1;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cin >> k;
        Genshin_Impact kks;
        memset(kks.a, 0, sizeof(kks.a));
        kks = quick_pow(ss, k - 1);
        cout << kks.a[1][1] << endl;
    }
}