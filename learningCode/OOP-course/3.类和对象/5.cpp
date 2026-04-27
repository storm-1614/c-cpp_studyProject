/*
 * =====================================================================================
 *
 *       Filename:  5.cpp
 *
 *    Description: 学生信息管理系统
 *
 *        Version:  1.0
 *        Created:  04/23/2026 11:30:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <list>
#include <string>

struct Birthday
{
    int year;
    int month;
    int day;
    Birthday(bool input = false)
    {
        if (input == true)
            std::cin >> year >> month >> day;
    }
};

class Student
{
  private:
    std::string name;   // 姓名
    int gender;         // 性别：男生为 1,女生为 0
    std::string number; // 学号
    Birthday birthday;  // 出生日期
    std::string major;  // 专业
    int score;          // 成绩

    static double total_score; // 总分
    static int count;          // 学生人数

  public:
    Student()
    {
        if (set_data())
            count++;
    }
    ~Student()
    {
        total_score -= score;
        count--;
    }
    bool set_data()
    {

        std::string temp_input;
        std::cout << "输入姓名：";
        std::cin >> name;
        while (true)
        {
            std::cout << "输入性别（男/女)";
            std::cin >> temp_input;
            if (temp_input == "男")
            {
                gender = 1;
                break;
            }
            else if (temp_input == "女")
            {
                gender = 0;
                break;
            }
        }

        std::cout << "输入学号：";
        std::cin >> number;
        std::cout << "输入出生日期（年 月 日）";

        Birthday new_birthday(true);
        birthday = new_birthday;

        std::cout << "输入专业：";
        std::cin >> major;
        std::cout << "输入分数";
        std::cin >> score;

        total_score += score;

        return true;
    }

    bool print_data()
    {
        std::cout << "姓名：" << name << std::endl;
        std::cout << "性别：" << (gender == 1 ? "男" : "女") << std::endl;
        std::cout << "学号：" << number << std::endl;
        std::cout << "出生日期：" << birthday.year << "." << birthday.month << "." << birthday.day << std::endl;
        std::cout << "专业：" << major << std::endl;
        std::cout << "成绩：" << score << std::endl;

        return true;
    }

    bool account()
    {
        // TODO: 暂时不需要
        return true;
    }

    static double sum()
    {
        return total_score;
    }

    static double average()
    {
        return total_score / count;
    }

    static bool compareByScoreAsc(const Student &x, const Student &y)
    {
        return x.score < y.score;
    }

    static bool compareByScoreDesc(const Student &x, const Student &y)
    {
        return x.score > y.score;
    }
};

double Student::total_score = 0;
int Student::count = 0;

class StudentManager
{
  private:
    std::list<Student> student_list;

  public:
    StudentManager()
    {
        int num;
        std::cout << "输入要添加到学生数量：";
        std::cin >> num;
        for (int i = 0; i < num; i++)
        {
            student_list.emplace_back(Student());
            std::cout << "================" << std::endl;
        }
    }

    bool add_student()
    {
        Student s;
        student_list.emplace_back(s);

        return true;
    }

    bool print_all_student()
    {
        int index = 1;
        for (auto &student : student_list)
        {
            std::cout << "--- 第 " << index << " 个学生 ---" << std::endl;
            student.print_data();
            std::cout << std::endl;
            index++;
        }
        return true;
    }

    bool sort(bool (*func)(const Student &x, const Student &y))
    {
        student_list.sort([func](const Student &a, const Student &b) { return func(a, b); });
        return true;
    }

    bool delete_student(int index)
    {
        if (index < 1 || index > (int)student_list.size())
        {
            std::cout << "索引超出范围！" << std::endl;
            return false;
        }

        auto it = student_list.begin();
        std::advance(it, index - 1); // 迭代器移动 index - 1 步
        student_list.erase(it);

        return true;
    }
};

int main(int argc, char *argv[])
{
    StudentManager stu_mg;
    int choice;
    while (true)
    {
        std::cout << "\n===== 学生信息管理系统 =====\n";
        std::cout << "1. 添加学生\n";
        std::cout << "2. 显示所有学生\n";
        std::cout << "3. 按成绩升序排序\n";
        std::cout << "4. 按成绩降序排序\n";
        std::cout << "5. 删除学生\n";
        std::cout << "0. 退出\n";
        std::cout << "请选择：";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            stu_mg.add_student();
            break;
        case 2:
            stu_mg.print_all_student();
            break;
        case 3:
            stu_mg.sort(Student::compareByScoreAsc);
            std::cout << "已按成绩升序排序。" << std::endl;
            break;
        case 4:
            stu_mg.sort(Student::compareByScoreDesc);
            std::cout << "已按成绩降序排序。" << std::endl;
            break;
        case 5: {
            int index;
            std::cout << "输入要删除的学生序号：";
            std::cin >> index;
            stu_mg.delete_student(index);
            break;
        }
        case 0:
            std::cout << "感谢使用！" << std::endl;
            return 0;
        default:
            std::cout << "无效选项，请重新选择。" << std::endl;
            break;
        }
    }
    return 0;
}
