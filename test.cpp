#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    for (int i=0; i<t; i++)
    {
        int n;
        cin >> n;
        vector<pair<int, int>> ab(n);
        for (int j=0; j<n; j++) 
        {
            cin >> ab[j].first >> ab[j].second;		
        }	 
        stable_sort(ab.begin(), ab.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });
        for (int j=0; j<n; j++)
        {
            cout << ab[j].first << " " << ab[j].second << endl;
        }
        if (i < t-1) // Add an extra newline between test cases, but not after the last one
        {
            cout << endl;
        }
    }
    return 0;
}