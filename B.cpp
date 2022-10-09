#include <bits/stdc++.h>

using namespace std;

ptrdiff_t find_el(const deque<int64_t> &deq, const int64_t &el)
{
    return distance(deq.begin(), find(deq.begin(), deq.end(), el));
}

bool is_a_to_b_poss(deque<int64_t> &A, deque<int64_t> &B)
{
    deque<int64_t> B_al;
    ptrdiff_t a0_in_b = find_el(B, A[0]);
    B_al.push_back(A[0]);
    for (size_t i = 1; i < A.size(); i++)
    {
        if (A[i] == A[0])
        {
            
        }
        ptrdiff_t i_in_b = find_el(B, A[i]);
        if (i_in_b < a0_in_b)
        {
            bool valid = true;
            for (size_t j = 1; j < A.size(); j++)
            {
                if (j != i && i_in_b > find_el(B, A[j]))
                {
                    valid = false;
                    break;
                }
            }
            if (!valid)
            {
                for (auto &s : B_al)
                {
                    cout << s << ' ';
                }
                cout << '\n';
                return false;
            }
            B[i_in_b] = numeric_limits<int64_t>::max();
            B_al.push_front(A[i]);
        }
        else
        {
            bool valid = true;
            for (size_t j = 1; j < A.size(); j++)
            {
                if (j != i && i_in_b < find_el(B, A[j]))
                {
                    valid = false;
                    break;
                }
            }
            if (!valid)
            {
                for (auto &s : B_al)
                {
                    cout << s << ' ';
                }
                cout << '\n';
                return false;
            }
            B_al.push_back(A[i]);
        }
    }
    return B_al == B;
}

int main(void)
{
    int64_t N;
    cin >> N;
    deque<int64_t> A, B;
    for (int64_t i = 0; i < N; i++)
    {
        int64_t ai;
        cin >> ai;
        A.push_back(ai);
    }
    for (int64_t i = 0; i < N; i++)
    {
        int64_t bi;
        cin >> bi;
        B.push_back(bi);
    }
    cout << (is_a_to_b_poss(A, B) ? "YES\n" : "NO\n");
    return 0;
}