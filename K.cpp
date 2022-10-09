#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    size_t n, m;
    vector<vector<char>> vec_2d;
    cin >> n >> m;
    while (n--)
    {
        vector<char> new_vec;
        for (size_t i = 0; i < m; i++)
        {
            char new_char;
            cin >> new_char;
            new_vec.push_back(new_char);
        }
        vec_2d.push_back(new_vec);
    }
    for (auto i = vec_2d.begin(); i != vec_2d.end(); i++)
    {
        for (auto j = i->begin(); j != i->end(); j++)
        {
            if (*j == '#')
            {
                cout << "# ";
                continue;
            }
            uint64_t res{};
            if (j != i->end() - 1 && *(j + 1) == '#')
            {
                res++;
            }
            if (j != i->begin() && *(j - 1) == '#')
            {
                res++;
            }
            if (i != vec_2d.begin() && (i - 1)->at(j - i->begin()) == '#')
            {
                res++;
            }
            if (i != vec_2d.end() - 1 && (i + 1)->at(j - i->begin()) == '#')
            {
                res++;
            }
            if (i != vec_2d.begin() && j != i->begin() && (i - 1)->at(j - i->begin() - 1) == '#')
            {
                res++;
            }
            if (i != vec_2d.end() - 1 && j != i->begin() && (i + 1)->at(j - i->begin() - 1) == '#')
            {
                res++;
            }
            if (i != vec_2d.begin() && j != i->end() - 1 && (i - 1)->at(j - i->begin() + 1) == '#')
            {
                res++;
            }
            if (i != vec_2d.end() - 1 && j != i->end() - 1 && (i + 1)->at(j - i->begin() + 1) == '#')
            {
                res++;
            }
            if (res == 0)
            {
                cout << ". ";
                continue;
            }
            cout << res << ' ';
        }
        cout << '\n';
    }
    return 0; 
}