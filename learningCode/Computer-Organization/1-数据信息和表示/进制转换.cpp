/* 进制转换
 *
 * Author: storm1614.top
 * Date: 2026-10-06
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

/* 十进制转 R 进制 核心函数
 * 实际上是做除数取模
 * 输入数字、进制
 * 输出可变数组
 */
std::vector<short> decimal_to_R(long n, short R)
{
    std::vector<short> result;
    if (n == 0)
    {
        return std::vector<short>{0};
    }
    while (n != 0)
    {
        result.emplace_back(n % R);
        n /= R;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

/*
 * 十进制转十六进制
 * 输出字符串
 */
std::string decimal_to_hex(long n)
{
    std::vector<short> hex_vect = decimal_to_R(n, 16);
    std::string result = "0x";

    for (auto iter : hex_vect)
    {
        if (iter < 10)
        {
            result += iter + '0';
        }
        else if (iter >= 10 && iter < 16)
        {
            result += iter - 10 + 'A';
        }
    }
    return result;
}

/*
 * 十进制转二进制
 * 输出字符串
 */
std::string decimal_to_binary(long n)
{
    std::vector<short> binary_vect = decimal_to_R(n, 2);

    std::string result = "0b";

    for (auto iter : binary_vect)
    {
        result += iter + '0';
    }
    return result;
}

/*
 * 十进制转八进制
 * 输出字符串
 */
std::string decimal_to_octal(long n)
{
    std::vector<short> octal_vect = decimal_to_R(n, 8);

    std::string result = "0o";

    for (auto iter : octal_vect)
    {
        result += iter + '0';
    }
    return result;
}

/*=====================*/

int char_to_val(unsigned char c)
{
    c = toupper(c);
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    return -1;
}

long R_to_decimal(const std::string &n_str, short R)
{
    if (R != 2 && R != 8 && R != 16)
    {
        return -1;
    }

    if (n_str.empty())
    {
        return -2;
    }
    long result = 0;
    int digit;
    for (auto iter : n_str)
    {
        digit = char_to_val(iter);
        if (digit < 0 || digit >= R)
        {
            return -1;
        }
        result = result * R + digit;
    }
    return result;
}

bool recover_input()
{
    if (std::cin.eof())
    {
        return false;
    }
    std::cout << "输入格式错误，已返回菜单" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

int main()
{
    short choice;

    while (true)
    {
        std::cout << "进制转换" << std::endl;
        std::cout << "1. 十进制 -> 二/八/十六进制" << std::endl;
        std::cout << "2. 二/八/十六进制 -> 十进制" << std::endl;
        std::cout << "0. 退出程序" << std::endl;
        std::cout << "请选择功能：";
        if (!(std::cin >> choice))
        {
            if (!recover_input())
            {
                return 0;
            }
            continue;
        }

        switch (choice)
        {
        case 1: {
            long n;
            std::string token;
            std::cout << "请输入非负十进制整数：";
            if (!(std::cin >> token))
            {
                if (!recover_input())
                {
                    return 0;
                }
                continue;
            }
            std::istringstream parser(token);
            if (!(parser >> n) || parser.peek() != std::char_traits<char>::eof())
            {
                std::cout << "输入格式错误" << std::endl;
                break;
            }

            if (n < 0)
            {
                std::cout << "输入错误，请输入非负整数" << std::endl;
                break;
            }

            std::cout << "二进制：" << decimal_to_binary(n) << std::endl;
            std::cout << "八进制：" << decimal_to_octal(n) << std::endl;
            std::cout << "十六进制：" << decimal_to_hex(n) << std::endl;
            break;
        }
        case 2: {
            std::string n_str;
            short base;
            std::cout << "请输入二/八/十六进制数：";
            if (!(std::cin >> n_str))
            {
                if (!recover_input())
                {
                    return 0;
                }
                continue;
            }
            std::cout << "请输入原进制（2/8/16）：";
            if (!(std::cin >> base))
            {
                if (!recover_input())
                {
                    return 0;
                }
                continue;
            }
            if (base != 2 && base != 8 && base != 16)
            {
                std::cout << "进制错误，请输入 2、8 或 16" << std::endl;
                break;
            }
            long result = R_to_decimal(n_str, base);
            if (result < 0)
            {
                std::cout << "数字与所选进制不匹配" << std::endl;
            }
            else
            {
                std::cout << "十进制：" << result << std::endl;
            }
            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "选项错误，请输入 0、1 或 2" << std::endl;
            break;
        }
        std::cout << "============" << std::endl;
    }
}
