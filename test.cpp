#include <bits/stdc++.h>
using namespace std;
int arr[1000007];
bool isPrime(int n)
{
    memset(arr, 1, sizeof(arr));
    arr[0] = arr[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (arr[i] == 1)
        {
            for (int j = i + i; j <= n; j += i)
            {
                arr[j] = 0;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n / 2; i++)
    {
        if (isPrime(i) && n % i == 0 && isPrime(n / i))
        {
            cout << i << " " << n / i << endl;
            break;
        }
    }
    return 0;
}