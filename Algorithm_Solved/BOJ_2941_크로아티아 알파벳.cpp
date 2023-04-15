#include <iostream>
using namespace std;
#include <string>

int main()
{
    string arr[8] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };

    string words;
    cin >> words;

    for (string target : arr)
    {
        while (words.find(target) != string::npos)
            words.replace(words.find(target), target.length(), "*");
    }

    cout << words.length();

    return 0;
}