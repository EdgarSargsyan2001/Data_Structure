#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class bigInt
{
public:
    friend bigInt operator*(bigInt &x, long long y)
    {
        bigInt k = y;
        return x * k;
    }
    friend bool operator==(const bigInt &x, long long y)
    {
        bigInt k = y;
        return x == k;
    }
    friend bigInt operator+(bigInt x, const int y)
    {
        bigInt k = y;
        return x + k;
    }
    friend bigInt operator+(const int y, bigInt x)
    {
        bigInt k = y;
        return x + k;
    }
    friend bigInt operator-(bigInt &x, const int y)
    {
        bigInt k = y;
        return x - k;
    }
    friend bigInt operator-(const int y, bigInt &x)
    {
        bigInt k = y;
        return k - x;
    }
    friend bool operator<=(const bigInt &x, const long long y)
    {
        bigInt k = y;
        return x <= k;
    }
    friend bool operator>(const bigInt &x, const long long y)
    {
        bigInt k = y;
        return x > k;
    }
    friend bool operator<(const bigInt &x, const long long y)
    {
        bigInt k = y;
        return x < k;
    }
    friend bool operator<(const long long y, const bigInt &x)
    {
        bigInt k = y;
        return x > k;
    }
    friend bool operator>=(const bigInt &x, const long long y)
    {
        bigInt k = y;
        return x >= k;
    }

public:
    bigInt() {}
    bigInt(long long _num)
    {
        std::string k = std::to_string(_num);
        push_all_elems(k);
    }
    bigInt(std::string _strNum)
    {
        push_all_elems(_strNum);
    }

    // operator conditional
    bool operator==(bigInt &x) const
    {
        return (str == x.str && sign == x.sign);
    }
    bool operator>(bigInt &x) const
    {
        if (sign != x.sign)
            return sign < x.sign;

        if (sign == 0)
            return str.size() == x.str.size() ? (str > x.str) : (str.size() > x.str.size());

        return str.size() == x.str.size() ? (str < x.str) : (str.size() < x.str.size());
    }
    bool operator<(bigInt &x) const
    {
        return (!(*this == x) && !(*this > x));
    }
    bool operator>=(bigInt &x) const
    {
        return ((*this == x) || (*this > x));
    }
    bool operator<=(bigInt &x) const
    {
        return ((*this == x) || (*this < x));
    }

    // operator arithmetic operation
    bigInt operator+(bigInt &x)
    {
        bigInt tmp;
        if (*this < 0 && x >= 0)
        {
            tmp = *this;
            tmp.sign = 0;
            return (x - tmp);
        }
        if (x < 0 && *this >= 0)
        {
            tmp = x;
            tmp.sign = 0;
            return (*this - tmp);
        }

        if (sign == x.sign)
            tmp.sign = sign;

        short carry = 0;
        for (short i = 0, j = 0; i < str.size() || j < x.str.size();)
        {
            short op1 = i < str.size() ? (str[i++]) : 0;
            short op2 = j < x.str.size() ? (x.str[j++]) : 0;
            short num = (op1 + op2) + carry;
            carry = (num / 100);
            tmp.str.push_back((num % 100));
        }
        if (carry)
            tmp.str.push_back(carry);

        return tmp;
    }

    bigInt operator-(bigInt &x)
    {
        bigInt tmp;
        if (*this <= 0 && x <= 0)
        {
            tmp = x;
            tmp.sign = 0;
            return tmp + *this;
        }
        if (*this <= 0 && x >= 0)
        {
            tmp = *this;
            tmp.sign = 0;
            tmp = tmp + x;
            tmp.sign = 1;
            return tmp;
        }
        if (*this >= 0 && x <= 0)
        {
            tmp = x;
            tmp.sign = 0;
            return tmp + *this;
        }
        std::string s1 = str, s2 = x.str;
        if (*this < x)
            s1.swap(s2), tmp.sign = 1;

        short borrow = 0;
        for (short i = 0, j = 0; i < s1.size() || j < s2.size();)
        {
            short op1 = i < s1.size() ? (s1[i++] - borrow) : (0 - borrow);
            short op2 = j < s2.size() ? (s2[j++]) : 0;
            borrow = (op1 < op2) ? 1 : 0;
            short num = op1 - op2 + 100 * borrow;
            tmp.str.push_back((num % 100));
        }

        while (*(tmp.str.end() - 1) == '\0' && !tmp.str.empty())
            tmp.str.pop_back();

        if (tmp.str.empty())
            tmp = 0;

        return tmp;
    }

    bigInt operator*(bigInt &x)
    {
        bigInt tmp = 0;
        // x = tmp;
        if (*this == 0 || x == 0)
            return tmp;

        bigInt k = 0;
        bigInt op1 = x <= *this ? *this : x;
        std::string st = x < *this ? x.str : str;
        for (int i = 0; i < st.length(); i++)
        {
            for (int j = 0; j < st[i]; j++)
                k = k + op1;
            k << i;
            // k.print();
            tmp = tmp + k;
            k = 0;
        }
        if (*this < 0 || x < 0)
            tmp.sign = 1;
        if (*this < 0 && x < 0)
            tmp.sign = 0;

        return tmp;
    }

    void operator<<(int y)
    {
        if (y == 0)
            return;

        std::reverse(str.begin(), str.end());
        for (int i = 0; i < y; i++)
        {
            str.push_back(0);
        }
        std::reverse(str.begin(), str.end());
    }

    void print()
    {
        std::cout << "size: " << str.size() << "  :  ";
        if (sign)
            std::cout << '-';

        for (int i = str.size() - 1; i >= 0; i--)
        {
            if (str[i] < 10 && i != (str.size() - 1))
                std::cout << '0';

            std::cout << (short)str[i];
        }
        std::cout << std::endl;
    }

private:
    bool is_num(char k)
    {
        return (k >= '0' && k <= '9');
    }

    void push_all_elems(std::string &strNum)
    {
        int start = 0;
        if (strNum[0] == '-' || strNum[0] == '+')
            sign = strNum[0] == '-' ? 1 : 0, start++;

        if ((strNum.length() - start) % 2 == 1)
            strNum.insert(start, "0");

        for (int i = strNum.length() - 1; i >= start; i -= 2)
        {
            if (!is_num(strNum[i]))
            {
                std::cout << "Error: isn't desimal";
                throw("ERROR");
            }
            str.push_back((strNum[i] - '0') + 10 * (strNum[i - 1] - '0'));
        }
    }

private:
    std::string str;
    bool sign = 0;
};
