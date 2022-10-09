#include <bits/stdc++.h>

using namespace std;

class BigNum
{
protected:
    int64_t sign;
    vector<int64_t> a;
    const static int64_t base_digits = 9, base = 1000000000;
    void trim()
    {
        while (!a.empty() && !a.back())
        {
            a.pop_back();
        }
        if (a.empty())
        {
            sign = 1;
        }
    }
    void read(const string &s)
    {
        sign = 1;
        a.clear();
        int64_t pos = 0;
        while (pos < static_cast<int64_t>(s.size()) && (s[static_cast<string::size_type>(pos)] == '-' || s[static_cast<string::size_type>(pos)] == '+'))
        {
            if (s[static_cast<string::size_type>(pos)] == '-')
            {
                sign = -sign;
            }
            ++pos;
        }
        for (int64_t i = static_cast<int64_t>(s.size() - 1); i >= pos; i -= base_digits)
        {
            int64_t x = 0;
            for (int64_t j = max(pos, i - base_digits + 1); j <= i; j++)
            {
                x = x * 10 + s[static_cast<string::size_type>(j)] - '0';
            }
            a.push_back(x);
        }
        trim();
    }
    static vector<int64_t> convert_base(const vector<int64_t> &a, int64_t old_digits, int64_t new_digits)
    {
        vector<int64_t> p(static_cast<uint64_t>(max(old_digits, new_digits) + 1));
        p[0] = 1;
        for (uint64_t i = 1; i < p.size(); i++)
        {
            p[i] = p[i - 1] * 10;
        }
        vector<int64_t> res;
        int64_t cur = 0, cur_digits = 0;
        for (uint64_t i = 0; i < a.size(); i++)
        {
            cur += a[i] * p[static_cast<size_t>(cur_digits)];
            cur_digits += old_digits;
            while (cur_digits >= new_digits)
            {
                uint64_t new_digits_unsigned = static_cast<uint64_t>(new_digits);
                res.push_back(cur % p[new_digits_unsigned]);
                cur /= p[new_digits_unsigned];
                cur_digits -= new_digits;
            }
        }
        res.push_back(cur);
        while (!res.empty() && !res.back())
        {
            res.pop_back();
        }
        return res;
    }
    static vector<int64_t> karatsuba_multiply(const vector<int64_t> &a, const vector<int64_t> &b)
    {
        uint64_t n = a.size();
        vector<int64_t> res(n + n);
        if (n <= 32)
        {
            for (uint64_t i = 0; i < n; i++)
            {
                for (uint64_t j = 0; j < n; j++)
                {
                    res[i + j] += a[i] * b[j];
                }
            }
            return res;
        }
        uint64_t k = n >> 1;
        vector<int64_t> a1(a.begin(), a.begin() + k), a2(a.begin() + k, a.end()), b1(b.begin(), b.begin() + k), b2(b.begin() + k, b.end()), a1b1 = karatsuba_multiply(a1, b1), a2b2 = karatsuba_multiply(a2, b2);
        for (uint64_t i = 0; i < k; i++)
        {
            a2[i] += a1[i];
        }
        for (uint64_t i = 0; i < k; i++)
        {
            b2[i] += b1[i];
        }
        vector<int64_t> r = karatsuba_multiply(a2, b2);
        for (uint64_t i = 0; i < a1b1.size(); i++)
        {
            r[i] -= a1b1[i];
        }
        for (uint64_t i = 0; i < a2b2.size(); i++)
        {
            r[i] -= a2b2[i];
        }
        for (uint64_t i = 0; i < r.size(); i++)
        {
            res[i + k] += r[i];
        }
        for (uint64_t i = 0; i < a1b1.size(); i++)
        {
            res[i] += a1b1[i];
        }
        for (uint64_t i = 0; i < a2b2.size(); i++)
        {
            res[i + n] += a2b2[i];
        }
        return res;
    }
    bool isZero() const
    {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

public:
    BigNum abs() const
    {
        BigNum res = *this;
        res.sign *= res.sign;
        return res;
    }
    BigNum pow(const BigNum &v)
    {
        if (v == 0)
        {
            return 1;
        }
        BigNum res = *this;
        for (BigNum i = 2; i <= v; i++)
        {
            res *= *this;
        }
        return res;
    }
    // constructors
    BigNum() : sign(1)
    {
    }
    BigNum(int64_t v)
    {
        *this = v;
    }
    BigNum(const string &s)
    {
        read(s);
    }
    BigNum(const BigNum &v)
    {
        *this = v;
    }
    // operators, streams
    friend istream &operator>>(istream &stream, BigNum &v)
    {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
    friend ostream &operator<<(ostream &stream, const BigNum &v)
    {
        if (v.sign == -1)
        {
            stream << '-';
        }
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int64_t i = static_cast<int64_t>(v.a.size() - 1); i > 0; i--)
        {
            stream << setw(base_digits) << setfill('0') << v.a[static_cast<uint64_t>(i - 1)];
        }
        return stream;
    }
    void operator=(const BigNum &v)
    {
        sign = v.sign;
        a = v.a;
    }
    void operator=(int64_t v)
    {
        sign = 1;
        a.clear();
        if (v < 0)
        {
            sign = -1, v = -v;
        }
        for (; v > 0; v = v / base)
        {
            a.push_back(v % base);
        }
    }
    BigNum operator-() const
    {
        BigNum result = *this;
        result.sign = -sign;
        return result;
    }
    BigNum operator-(const BigNum &v) const
    {
        if (sign == v.sign)
        {
            if (abs() >= v.abs())
            {
                BigNum res = *this;
                for (uint64_t i = 0, carry = 0; i < v.a.size() || carry; ++i)
                {
                    res.a[i] -= carry + (i < v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                    {
                        res.a[i] += base;
                    }
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
    BigNum operator+(const BigNum &v) const
    {
        if (sign == v.sign)
        {
            BigNum result = v;
            for (uint64_t i = 0, carry = 0; i < max(a.size(), v.a.size()) || carry; i++)
            {
                if (i == result.a.size())
                {
                    result.a.push_back(0);
                }
                result.a[i] += carry + (i < a.size() ? a[i] : 0);
                carry = result.a[i] >= base;
                if (carry)
                {
                    result.a[i] -= base;
                }
            }
            return result;
        }
        return *this - (-v);
    }
    BigNum operator*(const BigNum &v) const
    {
        vector<int64_t> a6 = convert_base(this->a, base_digits, 6), b6 = convert_base(v.a, base_digits, 6), a1(a6.begin(), a6.end()), b(b6.begin(), b6.end());
        while (a1.size() < b.size())
        {
            a1.push_back(0);
        }
        while (b.size() < a1.size())
        {
            b.push_back(0);
        }
        while (a1.size() & (a1.size() - 1))
        {
            a1.push_back(0);
            b.push_back(0);
        }
        vector<int64_t> c = karatsuba_multiply(a1, b);
        BigNum res;
        res.sign = sign * v.sign;
        int64_t *carry = new int64_t(0);
        for (uint64_t i = 0; i < c.size(); i++)
        {
            int64_t cur = c[i] + *carry;
            res.a.push_back(cur % 1000000);
            *carry = cur / 1000000;
        }
        delete carry;
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
    void operator+=(const BigNum &v)
    {
        *this = *this + v;
    }
    void operator-=(const BigNum &v)
    {
        *this = *this - v;
    }
    void operator*=(const BigNum &v)
    {
        *this = *this * v;
    }
    void operator/=(int64_t v)
    {
        if (v < 0)
        {
            sign = -sign;
            v = -v;
        }
        int64_t rem = 0;
        for (uint64_t i = a.size(); i > 0; i--)
        {
            int64_t cur = a[i - 1] + rem * base;
            a[i - 1] = cur / v;
            rem = cur % v;
        }
        trim();
    }
    BigNum operator++()
    {
        *this = *this + 1;
        return *this;
    }
    BigNum operator--()
    {
        *this = *this - 1;
        return *this;
    }
    BigNum operator++(int n)
    {
        if (n != 0)
        {
            *this = *this + n;
        }
        else
        {
            *this = *this + 1;
        }
        return *this;
    }
    BigNum operator--(int n)
    {
        if (n != 0)
        {
            *this = *this - n;
        }
        else
        {
            *this = *this - 1;
        }
        return *this;
    }
    bool operator<(const BigNum &v) const
    {
        if (sign != v.sign)
        {
            return sign < v.sign;
        }
        if (a.size() != v.a.size())
        {
            return static_cast<int64_t>(a.size()) * sign < static_cast<int64_t>(v.a.size()) * v.sign;
        }
        for (uint64_t i = a.size(); i > 0; i--)
        {
            if (a[i - 1] != v.a[i - 1])
            {
                return a[i - 1] * sign < v.a[i - 1] * sign;
            }
        }
        return false;
    }
    bool operator>(const BigNum &v) const
    {
        return v < *this;
    }
    bool operator<=(const BigNum &v) const
    {
        return !(v < *this);
    }
    bool operator>=(const BigNum &v) const
    {
        return !(*this < v);
    }
    bool operator==(const BigNum &v) const
    {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const BigNum &v) const
    {
        return *this < v || v < *this;
    }
};

int main(void)
{
    BigNum a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << (a.pow(b) < c.pow(d) ? "<\n" : ">\n");
    return 0;
}