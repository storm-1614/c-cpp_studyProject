/*
 * 学生信息管理系统
 * 2026-03-16 21:30
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

struct Student_info
{
  public:
    std::string name;
    std::string gender;
    std::string number;
    Birthday birthday;
    std::string major;
    int admission_score;
};

class Student
{
  public:
    Student_info info;

    Student(Student_info input = {}) : info(input)
    {
    }
    void add()
    {
        std::cout << "请输入姓名：";
        std::cin >> info.name;
        std::cout << "请输入性别：";
        std::cin >> info.gender;
        std::cout << "请输入学号：";
        std::cin >> info.number;
        std::cout << "请输入生日(例：2026 3 9）：";
        std::cin >> info.birthday.year >> info.birthday.month >> info.birthday.day;
        std::cout << "请输入专业：";
        std::cin >> info.major;
        std::cout << "请输入入学总成绩";
        std::cin >> info.admission_score;
    }

    bool modify()
    {
        int in;
        std::cout << "请输入要修改的信息数字:" << std::endl;
        std::cout << "1. 姓名、2. 性别、3. 学号、4. 生日、5. 专业、6. 入学总成绩" << std::endl;
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
            std::cout << "请输入学号";
            std::cin >> info.number;
            break;
        }
        case 4: {
            std::cout << "请输入生日(例：2026 3 9）";
            std::cin >> info.birthday.year >> info.birthday.month >> info.birthday.day;
            break;
        }
        case 5: {
            std::cout << "请输入专业";
            std::cin >> info.major;
            break;
        }
        case 6: {
            std::cout << "请输入入学总成绩";
            std::cin >> info.admission_score;
            break;
        }
        default: {
            return false;
        }
        }
        return true;
    }
};

class student_info_list
{
  private:
    std::string data_path;
    std::vector<Student> list;

  public:
    student_info_list(int capacity, const std::string path) : data_path(path)
    {
        list = load_from_csv(capacity, data_path);
    }

    ~student_info_list()
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

    int find_number(double score)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (score == list[i].info.admission_score)
            {
                return i;
            }
        }
        return -1;
    }

    void addStudent()
    {
        Student new_student(Student_info{});
        new_student.add();
        list.emplace_back(new_student);
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
            std::cout << "学号：" << list[i].info.number << std::endl;
            std::cout << "出生日期：" << list[i].info.birthday.year << "年" << list[i].info.birthday.month << "月"
                      << list[i].info.birthday.day << std::endl;
            std::cout << "专业：" << list[i].info.major << std::endl;
            std::cout << "入学总成绩：" << list[i].info.admission_score << std::endl;
            std::cout << "==========" << std::endl;
        }
    }

    void sort_present()
    {
        std::sort(list.begin(), list.end(),
                  [](Student x, Student y) { return x.info.admission_score > y.info.admission_score; });
        print("排序后：");
    }

    void modify_info()
    {
        print();
        std::string input;
        int index;
        std::cout << "请输入要修改学生的学号：";
        std::cin >> input;
        index = find_number(input);
        if (index != -1)
            list[index].modify();
        else
            std::cout << "没有该学生" << std::endl;
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

    std::vector<Student> load_from_csv(int c, std::string path)
    {
        std::ifstream in(path, std::fstream::out | std::ifstream::in);
        if (!in)
            return std::vector<Student>{};
        std::vector<Student> data(c);
        std::string line;
        while (std::getline(in, line))
        {
            if (line.empty())
                continue;

            std::vector<std::string> f = spilt(line);

            Student_info stu;
            stu.name = f[0];
            stu.gender = f[1];
            stu.number = f[2];
            stu.birthday.year = std::stoi(f[3]);
            stu.birthday.month = std::stoi(f[4]);
            stu.birthday.day = std::stoi(f[5]);
            stu.major = f[6];
            stu.admission_score = std::stoi(f[7]);
            Student in(stu);

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
                << s.info.birthday.month << "," << s.info.birthday.day << "," << s.info.major << ","
                << s.info.admission_score << "\n";
        }
    }
};

int main(int argc, char *argv[])
{
    int capacity;
    std::cout << "输入学生数量：";
    std::cin >> capacity;
    student_info_list info(capacity, "./data.csv");
    std::cout << "录入学生：";
    for (int i = 0; i < capacity; i++)
    {
        info.addStudent();
    }
    bool running = true;
    int num;

    while (running)
    {
        std::cout << "学生信息管理系统" << std::endl;
        std::cout << "1. 信息录入" << std::endl;
        std::cout << "2. 信息查找" << std::endl;
        std::cout << "3. 信息修改" << std::endl;
        std::cout << "4. 信息打印" << std::endl;
        std::cout << "5. 成绩排序" << std::endl;
        std::cout << "6. 退出" << std::endl;
        std::cout << "请输入：";
        std::cin >> num;

        switch (num)
        {
        case 1:
            info.addStudent();
            break;
        case 2: {

            int type;
            std::cout << "请输入数据类型（1.学号， 2. 成绩）:";
            std::cin >> type;
            std::string input;

            switch (type)
            {
            case 1: {
                std::cout << "输入要查找的学号：";
                std::cin >> input;

                std::cout << info.find_number(input) << std::endl;
            }
            case 2: {
                std::cout << "输入要查找的成绩：";
                std::cin >> input;

                std::cout << info.find_number(stod(input)) << std::endl;
            }
            }
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
