/*
* storm-1614
* 2025-10-02 10:06
* 拼写检查
*/


#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, char *argv[])
{
    vector<string> sentence;
    int n = 1;
    string input;

    cin >> n;

    getline(cin, input);
    for (int i = 0; i < n; i++)
    {
        getline(cin, input);
        input[0] = toupper(input[0]);
        for (int i = 1; i < input.size(); i++)
            input[i] = tolower(input[i]);

        sentence.emplace_back(input);
    }

    for (auto it : sentence)
        cout << it << endl;

    return 0;
}
