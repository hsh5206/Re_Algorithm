#include <iostream>
using namespace std;
#include <vector>

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> prices;
    for (int i = 0; i < N; i++)
    {
        int price;
        cin >> price;
        prices.push_back(price);
    }

    int result = 0;
    for (int i = prices.size() - 1; i >= 0; i--)
    {
        int cnt = static_cast<int>(K / prices[i]);
        result += cnt;
        K = K % prices[i];
    }

    cout << result;

    return 0;
}