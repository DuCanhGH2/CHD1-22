#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int64_t n;
    cin >> n;
    vector<int64_t> A, B, C;
    int64_t sum_a{};
    for (int64_t i = 0; i < n; i++)
    {
        int64_t ai;
        cin >> ai;
        A.push_back(ai);
        sum_a += ai;
    }
    for (int64_t i = 0; i < n; i++)
    {
        int64_t bi;
        cin >> bi;
        B.push_back(bi);
        C.push_back(B[i] - A[i]);
    }
    sort(C.rbegin(), C.rend());
    int64_t sum_c{sum_a};
    for (size_t k = 0; k <= n; k++)
    {
        if (k == 0)
        {
            cout << sum_a << ' ';
            continue;
        }
        sum_c += C[k - 1];
        cout << sum_c << ' ';
    }
    cout << '\n';
    return 0;
}