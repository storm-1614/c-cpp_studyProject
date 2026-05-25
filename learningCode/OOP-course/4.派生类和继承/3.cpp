#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm>

class Person
{
  protected:
    std::string id;
    std::string name;
    char gender;
    int age;

  public:
    Person();
    Person(const std::string &i, const std::string &n, char g, int a);

    bool setGender(char g);
    bool setAge(int a);

    void SetData();
    void PrintData() const;

    std::string getId() const;
    std::string getName() const;
    char getGender() const;
    int getAge() const;
};

class Student : public Person
{
  private:
    std::string department;
    float scores;

  public:
    Student();
    Student(const std::string &i, const std::string &n, char g, int a,
            const std::string &dept, float s);

    bool setScores(float s);

    void SetData();
    void PrintData() const;

    float getScores() const;

    static bool compareByScoreDesc(const Student &a, const Student &b);
};

class Teacher : public Person
{
  private:
    std::string title;
    float salary;

  public:
    Teacher();
    Teacher(const std::string &i, const std::string &n, char g, int a,
            const std::string &t, float s);

    bool setSalary(float s);

    void SetData();
    void PrintData() const;

    float getSalary() const;

    static bool compareBySalaryDesc(const Teacher &a, const Teacher &b);
};

void printStudentHeader();
void printTeacherHeader();

// ========== Person ==========

Person::Person() : id(""), name(""), gender('M'), age(18) {}

Person::Person(const std::string &i, const std::string &n, char g, int a)
    : id(i), name(n), gender('M'), age(18)
{
    setGender(g);
    setAge(a);
}

bool Person::setGender(char g)
{
    g = toupper(g);
    if (g == 'M' || g == 'F')
    {
        gender = g;
        return true;
    }
    std::cout << "性别无效，已设为默认值 'M'\n";
    gender = 'M';
    return false;
}

bool Person::setAge(int a)
{
    if (a >= 15 && a <= 70)
    {
        age = a;
        return true;
    }
    std::cout << "年龄无效（需15-70），已设为默认值 18\n";
    age = 18;
    return false;
}

void Person::SetData()
{
    std::cout << "请输入工号/学号: ";
    std::cin >> id;
    std::cout << "请输入姓名: ";
    std::cin >> name;
    char g;
    std::cout << "请输入性别 (M/F): ";
    std::cin >> g;
    setGender(g);
    int a;
    std::cout << "请输入年龄 (15-70): ";
    std::cin >> a;
    setAge(a);
}

void Person::PrintData() const
{
    std::cout << std::left << std::setw(12) << id
              << std::setw(10) << name
              << std::setw(6) << gender
              << std::setw(6) << age;
}

std::string Person::getId() const { return id; }
std::string Person::getName() const { return name; }
char Person::getGender() const { return gender; }
int Person::getAge() const { return age; }

// ========== Student ==========

Student::Student() : Person(), department(""), scores(0.0) {}

Student::Student(const std::string &i, const std::string &n, char g, int a,
                 const std::string &dept, float s)
    : Person(i, n, g, a), department(dept)
{
    setScores(s);
}

bool Student::setScores(float s)
{
    if (s >= 0.0 && s <= 100.0)
    {
        scores = s;
        return true;
    }
    std::cout << "成绩无效（需0-100），已设为0\n";
    scores = 0.0;
    return false;
}

void Student::SetData()
{
    Person::SetData();
    std::cout << "请输入系别: ";
    std::cin >> department;
    float s;
    std::cout << "请输入成绩 (0-100): ";
    std::cin >> s;
    setScores(s);
    std::cin.ignore();
}

void Student::PrintData() const
{
    Person::PrintData();
    std::cout << std::setw(16) << department
              << std::setw(8) << std::right
              << std::fixed << std::setprecision(1) << scores
              << std::left << std::endl;
}

float Student::getScores() const { return scores; }

bool Student::compareByScoreDesc(const Student &a, const Student &b)
{
    return a.scores > b.scores;
}

// ========== Teacher ==========

Teacher::Teacher() : Person(), title(""), salary(0.0) {}

Teacher::Teacher(const std::string &i, const std::string &n, char g, int a,
                 const std::string &t, float s)
    : Person(i, n, g, a), title(t)
{
    setSalary(s);
}

bool Teacher::setSalary(float s)
{
    if (s >= 0.0)
    {
        salary = s;
        return true;
    }
    std::cout << "工资无效，已设为0\n";
    salary = 0.0;
    return false;
}

void Teacher::SetData()
{
    Person::SetData();
    std::cout << "请输入职称: ";
    std::cin >> title;
    float s;
    std::cout << "请输入工资: ";
    std::cin >> s;
    setSalary(s);
    std::cin.ignore();
}

void Teacher::PrintData() const
{
    Person::PrintData();
    std::cout << std::setw(12) << title
              << std::setw(10) << std::right
              << std::fixed << std::setprecision(2) << salary
              << std::left << std::endl;
}

float Teacher::getSalary() const { return salary; }

bool Teacher::compareBySalaryDesc(const Teacher &a, const Teacher &b)
{
    return a.salary > b.salary;
}

// ========== 辅助函数 ==========

void printStudentHeader()
{
    std::cout << "\n" << std::string(58, '=') << std::endl;
    std::cout << std::left << std::setw(12) << "学号"
              << std::setw(10) << "姓名"
              << std::setw(6) << "性别"
              << std::setw(6) << "年龄"
              << std::setw(16) << "系别"
              << std::setw(8) << "成绩" << std::endl;
    std::cout << std::string(58, '-') << std::endl;
}

void printTeacherHeader()
{
    std::cout << "\n" << std::string(56, '=') << std::endl;
    std::cout << std::left << std::setw(12) << "工号"
              << std::setw(10) << "姓名"
              << std::setw(6) << "性别"
              << std::setw(6) << "年龄"
              << std::setw(12) << "职称"
              << std::setw(10) << "工资" << std::endl;
    std::cout << std::string(56, '-') << std::endl;
}

// ========== main ==========

int main()
{
    Teacher teacher_obj;
    Student student_obj;

    std::cout << "\n--- 输入教师信息 ---\n";
    teacher_obj.SetData();
    std::cout << "\n--- 教师信息 ---\n";
    printTeacherHeader();
    teacher_obj.PrintData();

    std::cout << "\n--- 输入学生信息 ---\n";
    student_obj.SetData();
    std::cout << "\n--- 学生信息 ---\n";
    printStudentHeader();
    student_obj.PrintData();

    std::cout << "\n\n========== 动态信息录入 ==========\n";

    int maxStudents = 0, maxTeachers = 0;
    std::cout << "请输入学生数组容量: ";
    std::cin >> maxStudents;
    std::cout << "请输入教师数组容量: ";
    std::cin >> maxTeachers;

    Student *students = new Student[maxStudents];
    Teacher *teachers = new Teacher[maxTeachers];

    int studentCount = 0, teacherCount = 0;
    char choice;

    std::cout << "\n开始录入信息（输入 S 添加学生，T 添加教师，其他字符结束）:\n";
    while (true)
    {
        std::cout << "> 请选择 (S/T/其他结束): ";
        std::cin >> choice;
        choice = toupper(choice);

        if (choice == 'S')
        {
            if (studentCount >= maxStudents)
            {
                std::cout << "学生数组已满！\n";
                continue;
            }
            std::cout << "--- 录入第 " << studentCount + 1 << " 个学生 ---\n";
            students[studentCount].SetData();
            studentCount++;
        }
        else if (choice == 'T')
        {
            if (teacherCount >= maxTeachers)
            {
                std::cout << "教师数组已满！\n";
                continue;
            }
            std::cout << "--- 录入第 " << teacherCount + 1 << " 个教师 ---\n";
            teachers[teacherCount].SetData();
            teacherCount++;
        }
        else
        {
            std::cout << "录入结束。\n";
            break;
        }
    }

    if (studentCount > 0)
        std::sort(students, students + studentCount, Student::compareByScoreDesc);
    if (teacherCount > 0)
        std::sort(teachers, teachers + teacherCount, Teacher::compareBySalaryDesc);

    std::cout << "\n\n========== 排序后的学生信息（按成绩降序） ==========";
    printStudentHeader();
    if (studentCount == 0)
        std::cout << "(无学生数据)\n";
    else
        for (int i = 0; i < studentCount; i++)
            students[i].PrintData();

    std::cout << "\n========== 排序后的教师信息（按工资降序） ==========";
    printTeacherHeader();
    if (teacherCount == 0)
        std::cout << "(无教师数据)\n";
    else
        for (int i = 0; i < teacherCount; i++)
            teachers[i].PrintData();

    delete[] students;
    delete[] teachers;

    return 0;
}
