#include <algorithm>

string substractSmallerFromLarger(string &a, string &b)
{
    int substractSize = b.size();
    int x = a.size() - 1;
    int y = substractSize - 1;
    int borrow = 0;
    string result;
    while (x >= 0 || y >= 0)
    {
        int digit = x >= 0 ? a[x] - '0' : 0;
        digit -= borrow;
        int digitA = y >= 0 ? b[y] - '0' : 0;
        if (digitA > digit)
        {
            digit += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        int temp = digit - digitA;
        result += temp + '0';
        x--;
        y--;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

string addPositiveNumbers(string &a, string &b)
{
    string result;
    int addSize = a.size();
    int x = b.size() - 1;
    int y = addSize - 1;
    int mod = 0;
    while (x >= 0 || y >= 0)
    {
        int digitA = y >= 0 ? a[y] - '0' : 0;
        int digit = x >= 0 ? b[x] - '0' : 0;
        int temp = digitA + digit;
        temp += mod;
        mod = temp / 10;
        temp %= 10;
        result += temp + '0';
        x--;
        y--;
    }
    result += mod + '0';
    std::reverse(result.begin(), result.end());
    return result;
}

class number
{
  private:
    string digits;
    int digitCount;
    int sign;

  public:
    number(string digits = "0")
    {
        preprocessNumber(digits, true);
    }

    void preprocessNumber(string digits, bool checkMinus = false)
    {
        if (checkMinus)
        {
            if (digits[0] == '-')
            {
                sign = -1;
                digits.erase(0, 1);
            }
            else
                sign = 1;
        }

        bool erased = false;
        for (int x = 0; x < digits.size(); x++)
        {
            if (digits[x] != '0')
            {
                digits.erase(0, x);
                erased = true;
                break;
            }
        }
        if (!erased)
        {
            digits = "";
        }

        digitCount = digits.size();
        this->digits = digits;
    }

    number operator-=(number &a)
    {
        if (a < *this == 0)
        {
            string result = "0";
            preprocessNumber(result);
            return *this;
        }
        if (sign == 1 && a.sign == -1)
        {
            a.sign = 1;
            *this += a;
            a.sign = -1;
            return *this;
        }
        if (sign == 1 && a.sign == 1)
        {
            string temp;
            if (*this < a == 1)
            {
                temp = substractSmallerFromLarger(digits, a.digits);
            }
            else
            {
                temp = substractSmallerFromLarger(a.digits, digits);
                sign = -1;
            }
            preprocessNumber(temp);
            return *this;
        }
        if (sign == -1 && a.sign == 1)
        {
            a.sign = 1;
            sign = 1;
            *this += a;
            sign = -1;
            preprocessNumber(digits);
            return *this;
        }
        if (sign == -1 && a.sign == -1)
        {
            sign = 1;
            a.sign = 1;
            string temp;

            if (*this < a == -1)
            {
                temp = substractSmallerFromLarger(a.digits, digits);
            }
            else
            {
                temp = substractSmallerFromLarger(digits, a.digits);
                sign = -1;
            }
            preprocessNumber(temp);
            a.sign = -1;
            return *this;
        }

        return *this;
    }

    number operator+=(number &a)
    {
        if (sign == -1 && a.sign == 1)
        {
            sign = 1;
            a -= *this;
            *this = a;
            return *this;
        }
        if (sign == 1 && a.sign == -1)
        {
            a.sign = 1;
            *this -= a;
            return *this;
        }
        string result;
        string temp = addPositiveNumbers(a.digits, digits);
        preprocessNumber(temp);
        return *this;
    }

    number operator*=(number &a)
    {
        if (a.digits == "0" || digits == "0")
        {
            sign = 1;
            preprocessNumber("0");
            return *this;
        }
        string results[105];
        for (int y = a.digitCount - 1; y >= 0; y--)
        {
            int x = digitCount - 1;
            int order = a.digitCount - y - 1;
            int mod = 0;
            for (int x = digitCount - 1; x >= 0; x--)
            {
                int temp = (a.digits[y] - '0') * (digits[x] - '0');
                temp += mod;
                mod = temp / 10;
                temp %= 10;
                results[order] += temp + '0';
            }
            results[order] += mod + '0';
            std::reverse(results[order].begin(), results[order].end());
            for (int x = 0; x < order; x++)
            {
                results[order] += '0';
            }
        }

        string result = "0";
        for (int x = 0; x < a.digitCount; x++)
        {
            result = addPositiveNumbers(result, results[x]);
        }
        preprocessNumber(result);
        if ((a.sign == -1 && sign == -1) || (a.sign == 1 && sign == 1))
            sign = 1;
        else
            sign = -1;
        return *this;
    }

    friend ostream &operator<<(ostream &stream, number &a);
    friend istream &operator>>(istream &stream, number &a);
    friend int operator<(number &a, number &b);
    friend string substractSmallerFromLarger(string &a, string &b);
    friend string addPositiveNumbers(string &a, string &b);
};

int operator<(number &a, number &b)
{
    if (a.sign == 1 && b.sign == -1)
    {
        return 1;
    }
    if (a.sign == -1 && b.sign == 1)
    {
        return -1;
    }

    int sign = a.sign;
    if (a.digitCount > b.digitCount)
    {
        return sign;
    }
    else if (a.digitCount < b.digitCount)
    {
        return sign * -1;
    }
    else
    {
        for (int x = 0; x < a.digitCount; x++)
        {
            if (a.digits[x] > b.digits[x])
            {
                return sign;
            }
            else if (a.digits[x] < b.digits[x])
            {
                return sign * -1;
            }
        }
        return 0;
    }
}

ostream &operator<<(ostream &stream, number &a)
{
    if (a.sign == -1)
        stream << '-';
    if (a.digitCount == 0)
    {
        stream << "0";
        return stream;
    }
    else
        stream << a.digits;

    return stream;
}

istream &operator>>(istream &stream, number &a)
{
    string digits;
    stream >> digits;
    a.preprocessNumber(digits, true);
    return stream;
}
