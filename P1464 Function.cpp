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
int rpt[25][25][25];

int w(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
        return 1;
    else if (rpt[a][b][c] != 0)
        return rpt[a][b][c];
    else if (a > 20 || b > 20 || c > 20)
        rpt[a][b][c] = w(20, 20, 20);
    else if (a < b && b < c)
        rpt[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    else
        rpt[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
    return rpt[a][b][c];
}

void solve()
{
    int a, b, c;
    while (cin >> a >> b >> c)
    {
        memset(rpt, 0, sizeof(rpt));
        if (a == -1 && b == -1 && c == -1)
            break;
        cout << "w(" << a << ", " << b << ", " << c << ") = ";
        if (a > 20)
            a = 21;
        if (b > 20)
            b = 21;
        if (c > 20)
            c = 21;
        cout << w(a, b, c) << "\n";
    }
    // wout <<L" "<<endl;
    // cout << R"( )" << endl;
}

signed main()
{
    // setlocale(LC_ALL, "");
    int t = 1;
    //	cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}