#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

class Person
{
  protected:
    std::string id;
    std::string name;
    char gender;
    int age;

  public:
    Person() : id(""), name(""), gender('M'), age(18) {}
    Person(const std::string &i, const std::string &n, char g, int a)
        : id(i), name(n)
    {
        setGender(g);
        setAge(a);
    }

    virtual ~Person() {}

    virtual void PrintInfo() const = 0;
    virtual std::string getType() const = 0;
    virtual float getKey() const = 0;

    virtual void Input()
    {
        std::cout << "请输入编号: ";
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

    bool setGender(char g)
    {
        g = toupper(g);
        if (g == 'M' || g == 'F') { gender = g; return true; }
        gender = 'M';
        return false;
    }

    bool setAge(int a)
    {
        if (a >= 15 && a <= 70) { age = a; return true; }
        age = 18;
        return false;
    }

    std::string getId()   const { return id; }
    std::string getName() const { return name; }
    char   getGender()    const { return gender; }
    int    getAge()       const { return age; }
};

class Student : public Person
{
  private:
    std::string department;
    float scores;

  public:
    Student() : Person(), department(""), scores(0.0) {}
    Student(const std::string &i, const std::string &n, char g, int a,
            const std::string &dept, float s)
        : Person(i, n, g, a), department(dept)
    {
        setScores(s);
    }

    bool setScores(float s)
    {
        if (s >= 0.0f && s <= 100.0f) { scores = s; return true; }
        scores = 0.0f;
        return false;
    }

    float getScores() const { return scores; }

    void PrintInfo() const override
    {
        std::cout << std::left
                  << std::setw(12) << id
                  << std::setw(10) << name
                  << std::setw(6)  << gender
                  << std::setw(6)  << age
                  << std::setw(16) << department
                  << std::setw(8)  << std::right
                  << std::fixed << std::setprecision(1) << scores
                  << std::left << std::endl;
    }

    std::string getType() const override { return "Student"; }
    float getKey() const override { return scores; }

    void Input() override
    {
        Person::Input();
        std::cout << "请输入系别: ";
        std::cin >> department;
        float s;
        std::cout << "请输入成绩 (0-100): ";
        std::cin >> s;
        setScores(s);
    }

    static void printHeader()
    {
        std::cout << std::string(58, '=') << std::endl;
        std::cout << std::left
                  << std::setw(12) << "学号"
                  << std::setw(10) << "姓名"
                  << std::setw(6)  << "性别"
                  << std::setw(6)  << "年龄"
                  << std::setw(16) << "系别"
                  << std::setw(8)  << "成绩" << std::endl;
        std::cout << std::string(58, '-') << std::endl;
    }
};

class Teacher : public Person
{
  private:
    std::string title;
    float salary;

  public:
    Teacher() : Person(), title(""), salary(0.0) {}
    Teacher(const std::string &i, const std::string &n, char g, int a,
            const std::string &t, float s)
        : Person(i, n, g, a), title(t)
    {
        setSalary(s);
    }

    bool setSalary(float s)
    {
        if (s >= 0.0f) { salary = s; return true; }
        salary = 0.0f;
        return false;
    }

    float getSalary() const { return salary; }

    void PrintInfo() const override
    {
        std::cout << std::left
                  << std::setw(12) << id
                  << std::setw(10) << name
                  << std::setw(6)  << gender
                  << std::setw(6)  << age
                  << std::setw(12) << title
                  << std::setw(10) << std::right
                  << std::fixed << std::setprecision(2) << salary
                  << std::left << std::endl;
    }

    std::string getType() const override { return "Teacher"; }
    float getKey() const override { return salary; }

    void Input() override
    {
        Person::Input();
        std::cout << "请输入职称: ";
        std::cin >> title;
        float s;
        std::cout << "请输入工资: ";
        std::cin >> s;
        setSalary(s);
    }

    static void printHeader()
    {
        std::cout << std::string(56, '=') << std::endl;
        std::cout << std::left
                  << std::setw(12) << "工号"
                  << std::setw(10) << "姓名"
                  << std::setw(6)  << "性别"
                  << std::setw(6)  << "年龄"
                  << std::setw(12) << "职称"
                  << std::setw(10) << "工资" << std::endl;
        std::cout << std::string(56, '-') << std::endl;
    }
};

class PersonManager
{
  private:
    std::vector<Person *> persons;

  public:
    ~PersonManager()
    {
        for (auto p : persons)
            delete p;
    }

    void addPerson(Person *p)
    {
        persons.push_back(p);
    }

    void printByType() const
    {
        if (persons.empty())
        {
            std::cout << "\n（暂无人员数据）\n";
            return;
        }

        bool hasStudent = false, hasTeacher = false;
        for (const auto &p : persons)
        {
            if (p->getType() == "Student") hasStudent = true;
            else hasTeacher = true;
        }

        if (hasStudent)
        {
            std::cout << "\n========== 学生信息 ==========";
            Student::printHeader();
            for (const auto &p : persons)
                if (p->getType() == "Student")
                    p->PrintInfo();
        }

        if (hasTeacher)
        {
            std::cout << "\n========== 教师信息 ==========";
            Teacher::printHeader();
            for (const auto &p : persons)
                if (p->getType() == "Teacher")
                    p->PrintInfo();
        }
    }

    void printAll() const
    {
        if (persons.empty())
        {
            std::cout << "\n（暂无人员数据）\n";
            return;
        }

        std::cout << "\n========== 全部人员信息 ==========\n";
        std::cout << std::string(60, '-') << std::endl;
        std::cout << std::left
                  << std::setw(10) << "类型"
                  << std::setw(12) << "编号"
                  << std::setw(10) << "姓名"
                  << std::setw(6)  << "性别"
                  << std::setw(6)  << "年龄"
                  << std::setw(16) << "附加信息" << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        for (const auto &p : persons)
        {
            std::cout << std::left << std::setw(10) << p->getType();
            p->PrintInfo();
        }
    }

    void sortAll()
    {
        std::sort(persons.begin(), persons.end(),
                  [](const Person *a, const Person *b)
                  {
                      return a->getKey() > b->getKey();
                  });
        std::cout << "\n已按关键值降序排列（学生成绩 / 教师工资）。\n";
    }

    void statistics() const
    {
        int stuCnt = 0, teaCnt = 0;
        float stuSum = 0.0, teaSum = 0.0;

        for (const auto &p : persons)
        {
            if (p->getType() == "Student")
            {
                stuCnt++;
                stuSum += p->getKey();
            }
            else
            {
                teaCnt++;
                teaSum += p->getKey();
            }
        }

        std::cout << "\n===== 统计信息 =====\n";
        std::cout << "学生人数: " << stuCnt;
        if (stuCnt > 0)
            std::cout << "，平均成绩: " << std::fixed << std::setprecision(1)
                      << stuSum / stuCnt;
        std::cout << std::endl;

        std::cout << "教师人数: " << teaCnt;
        if (teaCnt > 0)
            std::cout << "，平均工资: " << std::fixed << std::setprecision(2)
                      << teaSum / teaCnt;
        std::cout << std::endl;
    }

    size_t size() const { return persons.size(); }
};

int main()
{
    Person *persons[4];
    persons[0] = new Student("2024001", "张三", 'M', 20, "计算机", 92.5);
    persons[1] = new Teacher("T1001",   "李教授", 'F', 45, "教授", 15000);
    persons[2] = new Student("2024002", "王芳", 'F', 19, "数学", 88.0);
    persons[3] = new Teacher("T1002",   "赵老师", 'M', 35, "副教授", 12000);

    std::cout << "\n--- 全部人员 ---\n";
    for (int i = 0; i < 4; i++)
        persons[i]->PrintInfo();

    std::cout << "\n--- 学生 ---\n";
    Student::printHeader();
    for (int i = 0; i < 4; i++)
        if (persons[i]->getType() == "Student")
            persons[i]->PrintInfo();

    std::cout << "\n--- 教师 ---\n";
    Teacher::printHeader();
    for (int i = 0; i < 4; i++)
        if (persons[i]->getType() == "Teacher")
            persons[i]->PrintInfo();

    std::sort(persons, persons + 4,
              [](const Person *a, const Person *b)
              { return a->getKey() > b->getKey(); });

    std::cout << "\n--- 排序后（降序）---\n";
    for (int i = 0; i < 4; i++)
        persons[i]->PrintInfo();

    for (int i = 0; i < 4; i++)
        delete persons[i];

    return 0;
}
