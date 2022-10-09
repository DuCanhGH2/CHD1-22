#include <bits/stdc++.h>

using namespace std;

inline vector<string> stvow(const string &_STRING)
{
    istringstream is_as_sstream(_STRING);
    vector<string> words(istream_iterator<string>(is_as_sstream), {});
    return words;
}

int month_to_int(string &month)
{
    int month_int;
    if (month == "January")
    {
        month_int = 1;
    }
    else if (month == "February")
    {
        month_int = 2;
    }
    else if (month == "March")
    {
        month_int = 3;
    }
    else if (month == "April")
    {
        month_int = 4;
    }
    else if (month == "May")
    {
        month_int = 5;
    }
    else if (month == "June")
    {
        month_int = 6;
    }
    else if (month == "July")
    {
        month_int = 7;
    }
    else if (month == "August")
    {
        month_int = 8;
    }
    else if (month == "September")
    {
        month_int = 9;
    }
    else if (month == "October")
    {
        month_int = 10;
    }
    else if (month == "November")
    {
        month_int = 11;
    }
    else if (month == "December")
    {
        month_int = 12;
    }
    return month_int;
}

inline bool is_leap_year(const uint64_t &_YEAR)
{
    return (_YEAR % 4 == 0 && _YEAR % 100 != 0) || _YEAR % 400 == 0;
}

int main(void)
{
    string input;
    getline(cin, input);
    vector<string> vec = stvow(input);
    string day = vec[3], month = vec[5];
    day.erase(day.end() - 2, day.end());
    int day_int = stoi(day), month_int = month_to_int(month);
    int birthday = 344;
    int days_to_cur = 0;
    for (int i = 1; i < month_int; i++)
    {
        if (i == 2 && is_leap_year(i))
        {
            days_to_cur += 29;
            continue;
        }
        if (i == 2)
        {
            days_to_cur += 28;
            continue;
        }
        if (i % 2 != 0 && i <= 7)
        {
            days_to_cur += 31;
            continue;
        }
        if (i % 2 == 0 && i >= 8)
        {
            days_to_cur += 31;
            continue;
        }
        days_to_cur += 30;
    }
    days_to_cur += day_int;
    int result = birthday - days_to_cur;
    if (result < 0)
    {
        result += 365;
    }
    cout << result << '\n';
    return 0;
}