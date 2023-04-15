#include <iostream>
using namespace std;
#include <vector>
#include <cmath>

#define MAX pow(10,9)

int main()
{
    int N;
    cin >> N;

    vector<int> dp(N + 1, MAX);
    dp[N] = 0;
    for (int i = N; i >= 1; i--)
    {
        dp[i - 1] = min(dp[i - 1], dp[i] + 1);

        if (i % 3 == 0)
            dp[static_cast<int>(i / 3)] = min(dp[static_cast<int>(i / 3)], dp[i] + 1);
        if (i % 2 == 0)
            dp[static_cast<int>(i / 2)] = min(dp[static_cast<int>(i / 2)], dp[i] + 1);
    }

    cout << dp[1];

    return 0;
}