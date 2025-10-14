/*
* storm-1614
* 2025-10-12 12:38
* 排列字符
*/


#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::string n;
    int premutationNum = 1;
    std::cin >> n;
    for (int i = 1; i <= n.length();i++)
        premutationNum *= i;

    for (int i = 0; i < premutationNum - 1; i++)
    {
        std::cout << n << std::endl;
        std::next_permutation(n.begin(), n.end());
    }
        std::cout << n << std::endl;
    return 0;
}
