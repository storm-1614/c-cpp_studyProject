/*
 * =====================================================================================
 *
 *       Filename:  3.cpp
 *
 *    Description: 重载运算符“<<”和“>>”，使其能够输入一件商品的信息和输出这件商品的信息。商品信息有编号，商品名和价格。
 *
 *        Version:  1.0
 *        Created:  06/19/2026 10:01:19 AM
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

class Merchandise
{
  public:
    Merchandise() = default;
    ~Merchandise() = default;
    friend std::istream &operator>>(std::istream &in, Merchandise &s);  // 输入一件商品的信息
    friend std::ostream &operator<<(std::ostream &out, Merchandise &s); // 输出一件商品的信息
  private:
    int no;           // 编号
    std::string name; // 商品名
    double price;     // 价格
};

std::istream &operator>>(std::istream &in, Merchandise &s)
{
    std::cout << "ender: no、name、price:";
    in >> s.no >> s.name >> s.price;
    return in;
}
std::ostream &operator<<(std::ostream &out, Merchandise &s)
{
    std::cout << "no: " << s.no << "\nname: " << s.name << "\nprice: " << s.price << "\n";
    return out;
}

int main()
{
    Merchandise mer;
    std::cin >> mer;
    std::cout << mer;
    return 0;
}
