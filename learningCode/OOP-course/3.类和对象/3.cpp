/*
 * =====================================================================================
 *
 *       Filename:  3.cpp
 *
 *    Description: 使用C++的string类，将5个字符串按逆转后的顺序显示出来。
例如，逆转前5个字符的字符串是： Germany  Japan  America  Britain  France
按逆转后的顺序输出字符串是：France  Britain  America  Japan Germany
 *
 *        Version:  1.0
 *        Created:  04/23/2026 11:10:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
    std::vector<std::string> str_list;

    for (int i = 0; i < 5; i++)
    {
        std::string input;
        std::cin >> input;
        str_list.emplace_back(input);
    }

    std::reverse(str_list.begin(), str_list.end());

    for (auto iter:str_list)
         std::cout << iter << " ";
    

    return 0;
}
