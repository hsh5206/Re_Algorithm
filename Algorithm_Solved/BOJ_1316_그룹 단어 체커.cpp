#include <iostream>
using namespace std;
#include <map>

bool Checker(string& words)
{
    if (words.length() == 1)
        return true;

    map<int, bool> m;

    int i = 0, j = 1;
    for (; j <= words.length(); j++)
    {
        if (words[i] == words[j])
            continue;

        if (m.find(words[i]) != m.end())
            return false;

        m.insert(::make_pair(words[i], true));
        i = j;
    }
    return true;
}

int main()
{
    int N;
    cin >> N;

    int cnt = 0;
    for (int k = 0; k < N; k++)
    {
        string words;
        cin >> words;
        if (Checker(words))
            cnt++;
    }

    cout << cnt;

    return 0;
}