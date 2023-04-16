#include <iostream>
using namespace std;
#include <vector>

int main()
{
    int N;
    cin >> N;

    for (int k = 0; k < N; k++)
    {
        int num;
        cin >> num;
        vector<int> dp(num + 1, 0);

        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        for (int i = 4; i < dp.size(); i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }

        cout << dp[num] << endl;
    }

    return 0;
}