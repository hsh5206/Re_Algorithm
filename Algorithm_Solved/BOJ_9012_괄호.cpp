#include <iostream>
using namespace std;
#include <stack>

bool IsVPS(string& words)
{
    stack<char> s;
    for (int i = 0; i < words.length(); i++)
    {
        if (words[i] == '(')
            s.push(words[i]);
        else
        {
            if (!s.empty())
                s.pop();
            else
                return false;
        }
    }
    if (!s.empty())
        return false;
    return true;
}

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        string words;
        cin >> words;
        if (IsVPS(words))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}