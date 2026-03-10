/*
 * 教师信息管理系统（简陋版）
 * 2026-03-10 13:56
 * storm-1614
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Birthday
{
    int year, month, day;
};

struct teacher_info
{
  public:
    std::string name;
    std::string gender;
    std::string number;
    Birthday birthday;
    std::string level;
    double wage;
};


class Teacher
{
  public:
    teacher_info info;

    Teacher(teacher_info input = {}) : info(input)
    {
    }
    void add()
    {
        std::cout << "请输入姓名：";
        std::cin >> info.name;
        std::cout << "请输入性别：";
        std::cin >> info.gender;
        std::cout << "请输入工号：";
        std::cin >> info.number;
        std::cout << "请输入生日(例：2026 3 9）：";
        std::cin >> info.birthday.year >> info.birthday.month >> info.birthday.day;
        std::cout << "请输入职称：";
        std::cin >> info.level;
        std::cout << "请输入基本工资";
        std::cin >> info.wage;
    }

    bool modify()
    {
        int in;
        std::cout << "请输入要修改的信息数字:" << std::endl;
        std::cout << "1. 姓名、2. 性别、3. 工号、4. 生日、5. 职称、6. 基本工资" << std::endl;
        std::cin >> in;
        switch (in)
        {
        case 1: {
            std::cout << "请输入姓名：";
            std::cin >> info.name;
            break;
        }
        case 2: {
            std::cout << "请输入性别";
            std::cin >> info.gender;
            break;
        }
        case 3: {
            std::cout << "请输入工号";
            std::cin >> info.number;
            break;
        }
        case 4: {
            std::cout << "请输入生日(例：2026 3 9）";
            std::cin >> info.birthday.year >> info.birthday.month >> info.birthday.day;
            break;
        }
        case 5: {
            std::cout << "请输入职称";
            std::cin >> info.level;
            break;
        }
        case 6: {
            std::cout << "请输入基本工资";
            std::cin >> info.wage;
            break;
        }
        default: {
            return false;
        }
        }
        return true;
    }
};

class teacher_info_list
{
  private:
    std::string data_path;
    std::vector<Teacher> list;

  public:
    teacher_info_list(const std::string path) : data_path(path)
    {
        list = load_from_csv(data_path);
    }

    ~teacher_info_list()
    {
        write_to_csv(data_path);
    }
    int find_number(std::string number)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (number == list[i].info.number)
            {
                return i;
            }
        }
        return -1;
    }

    void add_teacher()
    {
        Teacher new_teacher(teacher_info{});
        new_teacher.add();
        list.emplace_back(new_teacher);
    }
    void print(std::string info = "打印信息：")
    {
        std::cout << info << std::endl;
        std::cout << "==========" << std::endl;
        for (int i = 0; i < list.size(); i++)
        {
            std::cout << "索引：" << i << std::endl;
            std::cout << "姓名：" << list[i].info.name << std::endl;
            std::cout << "性别：" << list[i].info.gender << std::endl;
            std::cout << "工号：" << list[i].info.number << std::endl;
            std::cout << "出生日期：" << list[i].info.birthday.year << "年" << list[i].info.birthday.month << "月"
                      << list[i].info.birthday.day << std::endl;
            std::cout << "职称：" << list[i].info.level << std::endl;
            std::cout << "基本工资：" << list[i].info.wage << std::endl;
            std::cout << "==========" << std::endl;
        }
    }

    void sort_present()
    {
        std::sort(list.begin(), list.end(),
                  [](Teacher x, Teacher y) { return std::stoi(x.info.number) > std::stoi(y.info.number); });
        print("排序后：");
    }

    void modify_info()
    {
        print();
        std::string input;
        int index;
        std::cout << "请输入要修改教师的工号：";
        std::cin >> input;
        index = find_number(input);
        if (index != -1)
            list[index].modify();
        else
            std::cout << "没有该教师" << std::endl;
    }

    std::vector<std::string> spilt(const std::string &line)
    {
        std::vector<std::string> column;
        std::string item;
        std::stringstream ss(line);
        while (std::getline(ss, item, ','))
            column.emplace_back(item);
        return column;
    }

    std::vector<Teacher> load_from_csv(std::string path)
    {
        std::ifstream in(path, std::fstream::out | std::ifstream::in);
        if (!in)
            return std::vector<Teacher>{};
        std::vector<Teacher> data;
        std::string line;
        while (std::getline(in, line))
        {
            if (line.empty())
                continue;

            std::vector<std::string> f = spilt(line);

            teacher_info stu;
            stu.name = f[0];
            stu.gender = f[1];
            stu.number = f[2];
            stu.birthday.year = std::stoi(f[3]);
            stu.birthday.month = std::stoi(f[4]);
            stu.birthday.day = std::stoi(f[5]);
            stu.level = f[6];
            stu.wage = std::stod(f[7]);
            Teacher in(stu);

            data.emplace_back(in);
        }

        return data;
    }

    void write_to_csv(std::string path)
    {
        std::ofstream out(path);
        for (auto &s : list)
        {

            out << s.info.name << "," << s.info.gender << "," << s.info.number << "," << s.info.birthday.year << ","
                << s.info.birthday.month << "," << s.info.birthday.day << "," << s.info.level << ","
                << s.info.wage << "\n";
        }
    }
};

int main(int argc, char *argv[])
{
    teacher_info_list info("./data.csv");
    bool running = true;
    int num;
    while (running)
    {
        std::cout << "教师信息管理系统" << std::endl;
        std::cout << "1. 信息录入" << std::endl;
        std::cout << "2. 信息查找" << std::endl;
        std::cout << "3. 信息修改" << std::endl;
        std::cout << "4. 信息打印" << std::endl;
        std::cout << "5. 工号排序" << std::endl;
        std::cout << "6. 退出" << std::endl;
        std::cout << "请输入：";
        std::cin >> num;

        switch (num)
        {
        case 1:
            info.add_teacher();
            break;
        case 2: {
            std::string input;

            std::cout << "输入要查找的工号：";
            std::cin >> input;

            std::cout << info.find_number(input) << std::endl;
            break;
        }

        case 3:
            info.modify_info();
            break;
        case 4:
            info.print();
            break;
        case 5:
            info.sort_present();
            break;
        case 6:
            running = false;
            break;
        }
    }

    return 0;
}
