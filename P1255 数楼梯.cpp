#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long ll;

using namespace std;

const ll W = 100000000;

const ll s = 8;

const ll WS[8] = {10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};

struct BigInt
{
    bool flag;
    int size;
    ll values[220];

    BigInt()
    {
        this->clear();
    }

    void clear()
    {
        memset(values, 0, sizeof values);
        this->size = 1;
        this->flag = true;
    }

    void operator=(int x)
    {
        this->clear();
        if (x == 0)
            return;
        ll cnt = 0;
        if (x < 0)
            x = -x, this->flag = false;
        while (x)
        {
            this->values[cnt] = x % W;
            x /= W;
            cnt++;
        }
        this->size = cnt;
    }

    void operator=(char *x)
    {
        this->clear();
        ll start = 0;
        ll len = strlen(x);
        if (len >= 1 && x[0] == '-')
            this->flag = false, start++;
        ll size = (len - start) % s ? (len - start) / s + 1 : (len - start) / s;
        this->size = size;
        ll cnt = 0;
        for (ll i = 0; i < this->size; i++)
        {
            for (ll j = s - 1; j >= 0; j--)
                this->values[cnt] = this->values[cnt] * 10 + (len - i * s - j - 1 >= start && x[len - i * s - j - 1] ? x[len - i * s - j - 1] - '0' : 0);
            cnt++;
        }
    }

    void operator=(BigInt x)
    {
        this->clear();
        this->size = x.size;
        this->flag = x.flag;
        for (int i = 0; i < this->size; i++)
            this->values[i] = x.values[i];
    }

    BigInt operator+(BigInt x) const
    {
        if (this->flag && x.flag)
        {
            BigInt y = *this;
            add(y, x);
            return y;
        }
        else if (this->flag)
        {
            x.flag = true;
            BigInt y = *this;
            subtract(y, x);
            return y;
        }
        else if (x.flag)
        {
            BigInt a = *this;
            a.flag = true;
            subtract(a, x);
            a.flag = false;
            return a;
        }
        else
        {
            BigInt a = *this;
            a.flag = true;
            x.flag = true;
            add(a, x);
            a.flag = false;
            return a;
        }
    }

    BigInt operator*(BigInt x) const
    {
        bool flag = this->flag == x.flag;
        BigInt y;
        y = *this;
        multiply(y, x);
        y.flag = flag;
        return y;
    }

    BigInt operator*(ll x) const
    {
        BigInt i;
        i = x;
        return this->operator*(i);
    }

    BigInt operator/(BigInt x) const
    {
        bool flag = this->flag == x.flag;
        BigInt y;
        y = *this;
        divide(y, x);
        y.flag = flag;
        return y;
    }

    BigInt operator/(ll x) const
    {
        BigInt i;
        i = x;
        return this->operator/(i);
    }

    void operator/=(BigInt x)
    {
        bool flag = this->flag == x.flag;
        divide(*this, x);
        this->flag = flag;
    }

    void operator/=(ll x)
    {
        BigInt i;
        i = x;
        this->operator/=(i);
    }

    BigInt operator%(BigInt x)
    {
        bool flag = this->flag == x.flag;
        BigInt y = *this;
        mod(y, x);
        y.flag = flag;
        return y;
    }

    BigInt operator%(ll x)
    {
        BigInt i;
        i = x;
        this->operator%(i);
    }

    void operator*=(BigInt x)
    {
        bool flag = this->flag == x.flag;
        multiply(*this, x);
        this->flag = flag;
    }

    void operator*=(ll x)
    {
        BigInt i;
        i = x;
        this->operator*=(i);
    }

    BigInt operator-(BigInt x) const
    {
        x.flag ^= 1;
        return this->operator+(x);
    }

    BigInt operator-() const
    {
        BigInt x = *this;
        x.flag ^= 1;
        return x;
    }

    BigInt operator+(ll x) const
    {
        BigInt i;
        i = x;
        return *this + i;
    }

    BigInt operator-(ll x) const
    {
        BigInt i;
        i = x;
        return *this - i;
    }

    void operator+=(BigInt x)
    {
        if (this->flag && x.flag)
            add(*this, x);
        else if (this->flag)
        {
            x.flag = true;
            subtract(*this, x);
        }
        else if (x.flag)
        {
            this->flag = true;
            subtract(*this, x);
            this->flag = false;
        }
        else
        {
            this->flag = true;
            x.flag = true;
            add(*this, x);
            this->flag = false;
        }
    }

    void operator+=(ll x)
    {
        BigInt i;
        i = x;
        return this->operator+=(i);
    }

    void operator-=(ll x)
    {
        BigInt i;
        i = x;
        return this->operator-=(i);
    }

    void operator-=(BigInt x)
    {
        x.flag ^= 1;
        this->operator+=(x);
    }

    BigInt operator++()
    {
        this->operator+=(1);
        return *this;
    }

    BigInt operator--()
    {
        this->operator+=(-1);
        return *this;
    }

    char *charValue() const
    {
        ll maxcnt = 0;
        ll start = 0;
        if (!this->flag)
            start++;
        char *t = new char[this->size * s + 1 + start];
        if (!this->flag)
            t[0] = '-';
        for (ll i = 0; i < this->size; i++)
        {
            for (ll j = s - 1; j >= 0; j--)
            {
                t[i * s + s - 1 - j + start] = (this->values[i] / WS[j]) % 10 + '0';
                if (t[i * s + s - 1 - j + start] != '0')
                    maxcnt = i * s + s - 1 - j + start;
            }
        }
        t[maxcnt + 1] = 0;
        reverse(t + start, t + maxcnt + 1);
        return t;
    }

    operator char *() const
    {
        return charValue();
    }

    bool operator==(BigInt x) const
    {
        if (this->size != x.size)
            return false;
        if (this->size == 1 && this->values[0] == x.values[0] && this->values[0] == 0)
            return true;
        if (this->flag != x.flag)
            return false;
        for (ll i = 0; i < this->size; i++)
            if (this->values[i] != x.values[i])
                return false;
        return true;
    }

    bool operator==(int x) const
    {
        BigInt y;
        y = x;
        return *this == y;
    }

    bool operator!=(BigInt x) const
    {
        if (*this == x)
            return false;
        return true;
    }

    bool operator<(BigInt x) const
    {
        if (this->size > x.size)
            return false;
        else if (this->size < x.size)
            return true;
        if ((ll)this->flag > (ll)x.flag)
            return false;
        for (ll i = this->size - 1; i >= 0; i--)
        {
            if (this->values[i] < x.values[i])
            {
                if (this->flag)
                    return true;
                else
                    return false;
            }
            else if (this->values[i] > x.values[i])
            {
                if (this->flag)
                    return false;
                else
                    return true;
            }
        }
        return false;
    }

    bool operator>(BigInt x) const
    {
        if (*this < x)
            return false;
        if (*this == x)
            return false;
        return true;
    }

    bool operator<=(BigInt x) const
    {
        if (*this > x)
            return false;
        return true;
    }

    bool operator>=(BigInt x) const
    {
        if (*this < x)
            return false;
        return true;
    }

    bool operator!() const
    {
        if (this->size != 1)
            return true;
        if (this->values[0] != 0)
            return true;
        return false;
    }

    void println()
    {
        print(*this);
        print("\n");
    }

    static void add(BigInt &a, BigInt b)
    {
        ll cnt = max(a.size, b.size) + 1;
        for (ll i = 0; i < cnt; i++)
        {
            ll t = a.values[i] + b.values[i];
            if (t >= W)
                a.values[i] = t - W, a.values[i + 1]++;
            else
                a.values[i] = t;
        }
        if (a.values[cnt - 1])
            a.size = cnt;
        else
            a.size = cnt - 1;
    }

    static void subtract(BigInt &a, BigInt b)
    {
        if (a == b)
        {
            a = 0;
            return;
        }
        if (a < b)
            swap(a, b), a.flag = false;
        ll maxcnt = 0;
        ll cnt = max(a.size, b.size);
        bool flag = false;
        for (ll i = 0; i < cnt; i++)
        {
            ll t = a.values[i] - b.values[i];
            if (flag)
                t--, flag = false;
            if (t < 0)
                flag = true, a.values[i] = t + W;
            else
                a.values[i] = t;
            if (a.values[i])
                maxcnt = i;
        }
        a.size = maxcnt + 1;
    }

    static void multiply(BigInt &a, BigInt b)
    {
        if (a == 1)
        {
            a = b;
            return;
        }
        if (a == 0 || b == 0)
        {
            a = 0;
            return;
        }
        if (b == 1)
        {
            return;
        }
        ll size = a.size + b.size;
        ll *ts = new ll[size];
        for (ll i = 0; i < size; i++)
            ts[i] = 0;
        for (ll i = 0; i < a.size; i++)
            for (ll j = 0; j < b.size; j++)
            {
                ll t = a.values[i] * b.values[j];
                if (t >= W)
                    ts[i + j] += t % W, ts[i + j + 1] += t / W;
                else
                    ts[i + j] += t;
            }
        for (ll i = 0; i < size; i++)
        {
            if (ts[i] >= W)
                ts[i + 1] += ts[i] / W, ts[i] %= W;
            a.values[i] = ts[i];
        }
        if (ts[size - 1])
            a.size = size;
        else
            a.size = size - 1;
    }

    static void divide(BigInt &a, BigInt b)
    {
        if (a < b)
        {
            a = 0;
            return;
        }
        if (a == b)
        {
            a = 1;
            return;
        }
        if (b == 0)
        {
            a = 0;
            return;
        }
        if (b == 1)
            return;
        if (b == 2)
        {
            divide2(a);
            return;
        }
        BigInt left, right;
        left = pow10_(max(0, a.size - b.size - 1)), right = pow10_(a.size - b.size + 1);
        while (left <= right)
        {
            BigInt mid;
            mid = left + right;
            divide2(mid);
            BigInt o = mid * b;
            BigInt o2 = o + b;
            if (o <= a && o2 > a)
            {
                a = mid;
                return;
            }
            else if (o2 <= a)
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    static void divide2(BigInt &a)
    {
        for (ll i = 0; i < a.size; i++)
        {
            ll t = a.values[i];
            if (t % 2 == 0 || i == 0)
                a.values[i] /= 2;
            else
                a.values[i] /= 2, a.values[i - 1] += W / 2;
        }
        if (!a.values[a.size - 1])
            a.size--;
    }

    static BigInt pow10_(int x)
    {
        BigInt y;
        if (x == 0)
        {
            y = 1;
            return y;
        }
        y.size = x;
        y.values[x - 1] = WS[0];
        return y;
    }

    static BigInt pow10(ll x)
    {
        ll size = (x + 1) % s == 0 ? (x + 1) / s : (x + 1) / s + 1;
        BigInt y;
        y.size = size;
        if ((x + 1) % s)
        {
            y.values[(x + 1) / s] = WS[s - (x + 1) % s];
        }
        else
            y.values[(x + 1) / s - 1] = WS[0];
        return y;
    }

    static void mod(BigInt &a, BigInt b)
    {
        BigInt x = a;
        divide(x, b);
        a -= b * x;
    }

    static void print(BigInt x)
    {
        if (!x.flag)
            cout << "-";
        cout << x.values[x.size - 1];
        for (ll i = x.size - 2; i >= 0; i--)
            print(x.values[i], s);
    }

    static void print(char *x)
    {
        cout << x;
    }

    static void print(ll x, ll d)
    {
        for (ll i = 0; i < d; i++)
            cout << (x / WS[i]) % 10;
    }

    static void swap(BigInt &a, BigInt &b)
    {
        BigInt x = a;
        a = b;
        b = x;
    }
};

struct Matrix
{
    BigInt values[2][2];

    ll size;
    Matrix(ll size)
    {
        this->size = size;
    }

    Matrix operator*(Matrix other)
    {
        Matrix ans(this->size);
        for (ll i = 0; i < this->size; i++)
            for (ll j = 0; j < this->size; j++)
                for (ll k = 0; k < this->size; k++)
                    ans.values[i][k] += this->values[i][j] * other.values[j][k];
        return ans;
    }

    Matrix operator^(ll b)
    {
        Matrix ans(this->size);
        Matrix base = *this;
        for (ll i = 0; i < this->size; i++)
            ans.values[i][i] = 1;
        while (b)
        {
            if (1 & b)
                ans = ans * base;
            base = base * base;
            b >>= 1;
        }
        return ans;
    }

    void init(ll values[2][2])
    {
        for (ll i = 0; i < this->size; i++)
            for (ll j = 0; j < this->size; j++)
                this->values[i][j] = values[i][j];
    }
};

int main()
{
    ll n;
    cin >> n;
    if (n == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    Matrix base(2);
    ll t[2][2] = {0, 1, 1, 1};
    ll t2[2][2] = {1, 2, 0, 0};
    base.init(t);
    Matrix ans(2);
    ans.init(t2);
    Matrix other = ans * (base ^ (n - 1));
    cout << other.values[0][0] << endl;
}