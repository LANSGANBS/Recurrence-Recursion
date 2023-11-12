#include <bits/stdc++.h>
using namespace std;
stack<char> q;
string s;
char s1[20005], ss[20005];
int k, k1, k2;

int main()
{
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ']')
        {
            k1 = 0;
            while (q.top() != '[')
            {
                k1++;
                s1[k1] = q.top();
                q.pop();
            }
            q.pop();
            k2 = k1;
            k = 0;
            while (s1[k2] >= '0' && s1[k2] <= '9')
            {
                k = k * 10 + s1[k2] - '0';
                k2--;
            }
            for (int j = 1; j <= k; j++)
                for (int l = k2; l > 0; l--)
                    q.push(s1[l]);
        }
        else
            q.push(s[i]);
    }
    k = 0;
    while (!q.empty())
    {
        ss[k] = q.top();
        q.pop();
        k++;
    }
    for (int i = k - 1; i >= 0; i--)
        cout << ss[i];
    return 0;
}