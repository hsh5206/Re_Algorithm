#include <iostream>
using namespace std;

bool hansoo(int num)
{
    if (num < 100)
        return true;
    else
    {
        int a, b, c;
        a = num / 100;
        b = num % 100 / 10;
        c = num % 10;

        if (a - b == b - c)
            return true;
    }

    return false;
}

int main()
{
    int N, cnt = 0;
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        if (hansoo(i))
            cnt++;
    }

    cout << cnt;

    return 0;
}