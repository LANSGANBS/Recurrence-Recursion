#include <bits/stdc++.h>
using namespace std;

template <typename T>
void sortAndPrint(vector<T> &v)
{
    sort(v.begin(), v.end());
    for (const T &val : v)
    {
        cout << val << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<int> intVec(n);
    for (int &val : intVec)
    {
        cin >> val;
    }
    sortAndPrint(intVec);

    vector<double> doubleVec(n);
    for (double &val : doubleVec)
    {
        cin >> val;
    }
    sortAndPrint(doubleVec);

    return 0;
}