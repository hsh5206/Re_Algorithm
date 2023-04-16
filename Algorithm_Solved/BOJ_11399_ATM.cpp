#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int GetMinSum(vector<int>& arr)
{
    int sum = 0;
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            sum += arr[j];
        }
    }

    return sum;
}

int main()
{
    int N;
    cin >> N;

    vector<int> times;
    for (int i = 0; i < N; i++)
    {
        int temp;
        cin >> temp;

        times.push_back(temp);
    }

    sort(times.begin(), times.end());

    cout << GetMinSum(times);

    return 0;
}