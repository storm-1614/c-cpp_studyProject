#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

// 自定义异常类
class PersonException : public runtime_error
{
public:
    explicit PersonException(const string &msg) : runtime_error(msg) {}
};

class InvalidAgeException : public PersonException
{
public:
    explicit InvalidAgeException(int age)
        : PersonException("无效年龄: " + to_string(age) + "，年龄应在15-70之间") {}
};

class InvalidGenderException : public PersonException
{
public:
    explicit InvalidGenderException(char gender)
        : PersonException(string("无效性别: '") + gender + "'，性别必须为 M 或 F") {}
};

class InvalidScoreException : public PersonException
{
public:
    explicit InvalidScoreException(float score)
        : PersonException("无效成绩: " + to_string(score) + "，成绩应在0-100之间") {}
};

class InvalidSalaryException : public PersonException
{
public:
    explicit InvalidSalaryException(float salary)
        : PersonException("无效工资: " + to_string(salary) + "，工资不能为负数") {}
};

class NotFoundException : public PersonException
{
public:
    explicit NotFoundException(const string &key)
        : PersonException("未找到: " + key) {}
};

// 排序用的模板函数 —— 按某个字段对容器排序
template <typename Container, typename Proj>
void sortBy(Container &c, Proj proj, bool asc = true)
{
    if (asc)
        sort(c.begin(), c.end(), [&](const auto &a, const auto &b) { return proj(a) < proj(b); });
    else
        sort(c.begin(), c.end(), [&](const auto &a, const auto &b) { return proj(a) > proj(b); });
}

// 查找模板 —— 返回第一个匹配的迭代器
template <typename Container, typename Pred>
auto findBy(Container &c, Pred pred)
{
    return find_if(c.begin(), c.end(), pred);
}

// 查找所有匹配
template <typename Container, typename Pred>
auto findAllBy(const Container &c, Pred pred) -> vector<typename Container::value_type>
{
    vector<typename Container::value_type> result;
    copy_if(c.begin(), c.end(), back_inserter(result), pred);
    return result;
}

// 多字段比较器 —— 先比主字段，一样再比次字段
template <typename T, typename P1, typename P2>
auto multiCmp(P1 p1, P2 p2, bool a1 = true, bool a2 = true)
{
    return [p1, p2, a1, a2](const T *a, const T *b) -> bool {
        auto v1a = p1(a), v1b = p1(b);
        if (v1a != v1b)
            return a1 ? (v1a < v1b) : (v1a > v1b);
        auto v2a = p2(a), v2b = p2(b);
        return a2 ? (v2a < v2b) : (v2a > v2b);
    };
}

// 人员基类
class Person
{
protected:
    string id;
    string name;
    char gender;
    int age;

public:
    Person() : id(""), name(""), gender('M'), age(18) {}

    Person(const string &i, const string &n, char g, int a) : id(i), name(n)
    {
        setGender(g);
        setAge(a);
    }

    virtual ~Person() {}

    virtual void print() const = 0;
    virtual string getType() const = 0;
    virtual float getKey() const = 0;

    virtual void input()
    {
        cout << "编号: ";
        cin >> id;
        cout << "姓名: ";
        cin >> name;

        while (true) {
            try {
                char g;
                cout << "性别 (M/F): ";
                cin >> g;
                setGender(g);
                break;
            } catch (const InvalidGenderException &e) {
                cerr << "错误: " << e.what() << " 请重新输入。" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        while (true) {
            try {
                int a;
                cout << "年龄 (15-70): ";
                cin >> a;
                setAge(a);
                break;
            } catch (const InvalidAgeException &e) {
                cerr << "错误: " << e.what() << " 请重新输入。" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void setGender(char g)
    {
        g = toupper(g);
        if (g != 'M' && g != 'F')
            throw InvalidGenderException(g);
        gender = g;
    }

    void setAge(int a)
    {
        if (a < 15 || a > 70)
            throw InvalidAgeException(a);
        age = a;
    }

    string getId()   const { return id; }
    string getName() const { return name; }
    char   getGender() const { return gender; }
    int    getAge()    const { return age; }
};

// 学生类
class Student : public Person
{
private:
    string dept;
    float score;

public:
    Student() : Person(), dept(""), score(0) {}

    Student(const string &i, const string &n, char g, int a,
            const string &d, float s) : Person(i, n, g, a), dept(d)
    {
        setScore(s);
    }

    void setScore(float s)
    {
        if (s < 0 || s > 100)
            throw InvalidScoreException(s);
        score = s;
    }

    float  getScore() const { return score; }
    string getDept()  const { return dept; }

    void print() const override
    {
        cout << left
             << setw(12) << id
             << setw(10) << name
             << setw(6)  << gender
             << setw(6)  << age
             << setw(16) << dept
             << setw(8)  << right << fixed << setprecision(1) << score
             << left << endl;
    }

    string getType() const override { return "Student"; }
    float  getKey()  const override { return score; }

    void input() override
    {
        Person::input();
        cout << "系别: ";
        cin >> dept;

        while (true) {
            try {
                float s;
                cout << "成绩 (0-100): ";
                cin >> s;
                setScore(s);
                break;
            } catch (const InvalidScoreException &e) {
                cerr << "错误: " << e.what() << " 请重新输入。" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static void printHeader()
    {
        cout << string(58, '=') << endl;
        cout << left
             << setw(12) << "学号"
             << setw(10) << "姓名"
             << setw(6)  << "性别"
             << setw(6)  << "年龄"
             << setw(16) << "系别"
             << setw(8)  << "成绩" << endl;
        cout << string(58, '-') << endl;
    }
};

// 教师类
class Teacher : public Person
{
private:
    string title;
    float salary;

public:
    Teacher() : Person(), title(""), salary(0) {}

    Teacher(const string &i, const string &n, char g, int a,
            const string &t, float s) : Person(i, n, g, a), title(t)
    {
        setSalary(s);
    }

    void setSalary(float s)
    {
        if (s < 0)
            throw InvalidSalaryException(s);
        salary = s;
    }

    float  getSalary() const { return salary; }
    string getTitle()  const { return title; }

    void print() const override
    {
        cout << left
             << setw(12) << id
             << setw(10) << name
             << setw(6)  << gender
             << setw(6)  << age
             << setw(12) << title
             << setw(10) << right << fixed << setprecision(2) << salary
             << left << endl;
    }

    string getType() const override { return "Teacher"; }
    float  getKey()  const override { return salary; }

    void input() override
    {
        Person::input();
        cout << "职称: ";
        cin >> title;

        while (true) {
            try {
                float s;
                cout << "工资: ";
                cin >> s;
                setSalary(s);
                break;
            } catch (const InvalidSalaryException &e) {
                cerr << "错误: " << e.what() << " 请重新输入。" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static void printHeader()
    {
        cout << string(56, '=') << endl;
        cout << left
             << setw(12) << "工号"
             << setw(10) << "姓名"
             << setw(6)  << "性别"
             << setw(6)  << "年龄"
             << setw(12) << "职称"
             << setw(10) << "工资" << endl;
        cout << string(56, '-') << endl;
    }
};

// 人员管理器 —— 用 vector/map/list 三种容器配合
class PersonManager
{
private:
    vector<Person *> persons;             // 主存储
    map<string, Person *> idMap;          // 编号索引，快速查找
    list<Person *> recent;                // 最近操作记录
    static const size_t MAX_RECENT = 10;

public:
    ~PersonManager() { clear(); }

    void clear()
    {
        for_each(persons.begin(), persons.end(), [](Person *p) { delete p; });
        persons.clear();
        idMap.clear();
        recent.clear();
    }

    void add(Person *p)
    {
        if (!p) return;

        try {
            if (idMap.find(p->getId()) != idMap.end())
                throw PersonException("编号 '" + p->getId() + "' 已存在！");

            persons.push_back(p);
            idMap[p->getId()] = p;

            recent.push_front(p);
            if (recent.size() > MAX_RECENT)
                recent.pop_back();

            cout << "添加成功: " << p->getType() << " - "
                 << p->getName() << " (ID: " << p->getId() << ")" << endl;
        } catch (const PersonException &e) {
            cerr << "添加失败: " << e.what() << endl;
            delete p;
            throw;
        }
    }

    bool remove(const string &id)
    {
        auto it = idMap.find(id);
        if (it == idMap.end()) {
            cerr << "未找到编号 '" << id << "' 的人员。" << endl;
            return false;
        }

        Person *target = it->second;

        auto vit = find_if(persons.begin(), persons.end(),
                           [&](const Person *p) { return p->getId() == id; });
        if (vit != persons.end())
            persons.erase(vit);

        idMap.erase(it);
        recent.remove(target);

        cout << "已删除: " << target->getType() << " - " << target->getName() << endl;
        delete target;
        return true;
    }

    Person *findById(const string &id)
    {
        auto it = idMap.find(id);
        if (it == idMap.end())
            throw NotFoundException("编号: " + id);
        return it->second;
    }

    Person *findByName(const string &name)
    {
        auto it = findBy(persons, [&](const Person *p) { return p->getName() == name; });
        if (it == persons.end())
            throw NotFoundException("姓名: " + name);
        return *it;
    }

    vector<Person *> filterByType(const string &type) const
    {
        return findAllBy(persons, [&](const Person *p) { return p->getType() == type; });
    }

    int countByType(const string &type) const
    {
        return count_if(persons.begin(), persons.end(),
                        [&](const Person *p) { return p->getType() == type; });
    }

    Person *maxKey() const
    {
        if (persons.empty()) return nullptr;
        auto it = max_element(persons.begin(), persons.end(),
                              [](const Person *a, const Person *b) { return a->getKey() < b->getKey(); });
        return *it;
    }

    Person *minKey() const
    {
        if (persons.empty()) return nullptr;
        auto it = min_element(persons.begin(), persons.end(),
                              [](const Person *a, const Person *b) { return a->getKey() < b->getKey(); });
        return *it;
    }

    void sortByKey(bool asc = false)
    {
        sortBy(persons, [](const Person *p) { return p->getKey(); }, asc);
        cout << "已按关键值" << (asc ? "升序" : "降序") << "排列。" << endl;
    }

    void sortByName(bool asc = true)
    {
        sortBy(persons, [](const Person *p) { return p->getName(); }, asc);
        cout << "已按姓名" << (asc ? "升序" : "降序") << "排列。" << endl;
    }

    void sortByAge(bool asc = true)
    {
        sortBy(persons, [](const Person *p) { return p->getAge(); }, asc);
        cout << "已按年龄" << (asc ? "升序" : "降序") << "排列。" << endl;
    }

    void sortByAgeThenName()
    {
        sort(persons.begin(), persons.end(),
             multiCmp<Person>(
                 [](const Person *p) { return p->getAge(); },
                 [](const Person *p) { return p->getName(); }));
        cout << "已按年龄->姓名排序。" << endl;
    }

    void printByType() const
    {
        if (persons.empty()) {
            cout << "（暂无数据）" << endl;
            return;
        }

        auto students = filterByType("Student");
        auto teachers  = filterByType("Teacher");

        if (!students.empty()) {
            cout << endl << "--- 学生信息 (" << students.size() << "人) ---" << endl;
            Student::printHeader();
            for_each(students.begin(), students.end(), [](const Person *p) { p->print(); });
        }

        if (!teachers.empty()) {
            cout << endl << "--- 教师信息 (" << teachers.size() << "人) ---" << endl;
            Teacher::printHeader();
            for_each(teachers.begin(), teachers.end(), [](const Person *p) { p->print(); });
        }
    }

    void printAll() const
    {
        if (persons.empty()) {
            cout << "（暂无数据）" << endl;
            return;
        }

        cout << endl << "--- 全部人员 (" << persons.size() << "人) ---" << endl;
        cout << string(60, '-') << endl;
        cout << left
             << setw(10) << "类型"
             << setw(12) << "编号"
             << setw(10) << "姓名"
             << setw(6)  << "性别"
             << setw(6)  << "年龄"
             << setw(16) << "附加信息" << endl;
        cout << string(60, '-') << endl;

        for_each(persons.begin(), persons.end(), [](const Person *p) {
            cout << left << setw(10) << p->getType();
            p->print();
        });
    }

    void showRecent() const
    {
        if (recent.empty()) {
            cout << "（暂无最近操作记录）" << endl;
            return;
        }

        cout << endl << "--- 最近操作 (list容器, 最多" << MAX_RECENT << "条) ---" << endl;
        int i = 1;
        for_each(recent.begin(), recent.end(), [&](const Person *p) {
            cout << "  " << i++ << ". [" << p->getType() << "] "
                 << p->getName() << " (ID: " << p->getId() << ")" << endl;
        });
    }

    void showIndex() const
    {
        cout << endl << "--- ID索引 (map容器) ---" << endl;
        cout << "索引数: " << idMap.size() << endl;
        for_each(idMap.begin(), idMap.end(), [](const auto &kv) {
            cout << "  " << kv.first << " -> "
                 << kv.second->getType() << " " << kv.second->getName() << endl;
        });
    }

    void stats() const
    {
        if (persons.empty()) {
            cout << "（暂无数据，无法统计）" << endl;
            return;
        }

        int stuCnt = countByType("Student");
        int teaCnt = countByType("Teacher");

        float stuSum = 0, teaSum = 0;
        for_each(persons.begin(), persons.end(), [&](const Person *p) {
            if (p->getType() == "Student")
                stuSum += p->getKey();
            else
                teaSum += p->getKey();
        });

        cout << endl << "--- 统计信息 ---" << endl;
        cout << "总人数: " << persons.size() << endl;
        cout << "学生: " << stuCnt;
        if (stuCnt > 0)
            cout << "，平均成绩: " << fixed << setprecision(1) << stuSum / stuCnt;
        cout << endl;
        cout << "教师: " << teaCnt;
        if (teaCnt > 0)
            cout << "，平均工资: " << fixed << setprecision(2) << teaSum / teaCnt;
        cout << endl;

        auto *mx = maxKey();
        auto *mn = minKey();
        if (mx) cout << "关键值最高: " << mx->getType() << " " << mx->getName()
                     << " (" << mx->getKey() << ")" << endl;
        if (mn) cout << "关键值最低: " << mn->getType() << " " << mn->getName()
                     << " (" << mn->getKey() << ")" << endl;
    }

    size_t size()      const { return persons.size(); }
    size_t indexSize() const { return idMap.size(); }
};

// 清输入缓冲
void clearCin()
{
    if (cin.eof()) return;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause()
{
    if (cin.eof()) return;
    cout << endl << "按回车继续...";
    string dummy;
    getline(cin, dummy);
    if (cin.eof()) cout << endl;
}

void showMenu()
{
    cout << endl;
    cout << "---------------------------------------------" << endl;
    cout << "      人员信息管理系统 (模板 + 异常处理)" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "  1. 添加学生" << endl;
    cout << "  2. 添加教师" << endl;
    cout << "  3. 按编号删除" << endl;
    cout << "  4. 按编号查找 (map)" << endl;
    cout << "  5. 按姓名查找 (find_if)" << endl;
    cout << "  6. 分类打印" << endl;
    cout << "  7. 打印全部" << endl;
    cout << "  8. 按关键值排序" << endl;
    cout << "  9. 按姓名排序" << endl;
    cout << " 10. 按年龄->姓名排序" << endl;
    cout << " 11. 统计信息" << endl;
    cout << " 12. for_each 算法演示" << endl;
    cout << " 13. 最近操作记录 (list)" << endl;
    cout << " 14. ID索引 (map)" << endl;
    cout << " 15. 异常处理演示" << endl;
    cout << "  0. 退出" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "请选择: ";
}

int main()
{
    PersonManager mgr;

    // 预置一些初始数据
    cout << "初始化预置数据..." << endl;
    try {
        mgr.add(new Student("2024001", "张三", 'M', 20, "计算机", 92.5));
        mgr.add(new Teacher("T1001",   "李教授", 'F', 45, "教授",   15000));
        mgr.add(new Student("2024002", "王芳", 'F', 19, "数学",   88.0));
        mgr.add(new Teacher("T1002",   "赵老师", 'M', 35, "副教授", 12000));
        cout << "预置数据加载完成！" << endl;
    } catch (const PersonException &e) {
        cerr << "预置数据异常: " << e.what() << endl;
    } catch (const exception &e) {
        cerr << "未知异常: " << e.what() << endl;
    }

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        cin >> choice;

        if (cin.eof()) {
            cout << endl << "输入结束，退出。" << endl;
            break;
        }
        if (cin.fail()) {
            cerr << "输入无效，请输入数字！" << endl;
            clearCin();
            continue;
        }

        try {
            switch (choice) {
            case 1: {
                cout << endl << "-- 添加学生 --" << endl;
                auto *s = new Student();
                s->input();
                mgr.add(s);
                break;
            }
            case 2: {
                cout << endl << "-- 添加教师 --" << endl;
                auto *t = new Teacher();
                t->input();
                mgr.add(t);
                break;
            }
            case 3: {
                string id;
                cout << "要删除的编号: ";
                cin >> id;
                mgr.remove(id);
                break;
            }
            case 4: {
                string id;
                cout << "要查找的编号: ";
                cin >> id;
                Person *p = mgr.findById(id);
                cout << endl << "找到 (map索引):" << endl;
                if (p->getType() == "Student") {
                    Student::printHeader();
                    p->print();
                } else {
                    Teacher::printHeader();
                    p->print();
                }
                break;
            }
            case 5: {
                string name;
                cout << "要查找的姓名: ";
                cin >> name;
                Person *p = mgr.findByName(name);
                cout << endl << "找到 (find_if):" << endl;
                if (p->getType() == "Student") {
                    Student::printHeader();
                    p->print();
                } else {
                    Teacher::printHeader();
                    p->print();
                }
                break;
            }
            case 6:
                mgr.printByType();
                break;
            case 7:
                mgr.printAll();
                break;
            case 8: {
                int asc;
                cout << "升序(1) / 降序(0): ";
                cin >> asc;
                mgr.sortByKey(asc == 1);
                mgr.printAll();
                break;
            }
            case 9: {
                int asc;
                cout << "升序(1) / 降序(0): ";
                cin >> asc;
                mgr.sortByName(asc == 1);
                mgr.printAll();
                break;
            }
            case 10:
                mgr.sortByAgeThenName();
                mgr.printAll();
                break;
            case 11:
                mgr.stats();
                break;
            case 12: {
                cout << endl << "-- for_each 算法演示 --" << endl;

                auto stus = mgr.filterByType("Student");
                auto teas = mgr.filterByType("Teacher");
                cout << "学生姓名: ";
                for_each(stus.begin(), stus.begin() + min((int)stus.size(), 5),
                         [](const Person *p) { cout << p->getName() << " "; });
                cout << endl;
                cout << "教师姓名: ";
                for_each(teas.begin(), teas.begin() + min((int)teas.size(), 5),
                         [](const Person *p) { cout << p->getName() << " "; });
                cout << endl;

                cout << "count_if 统计: 学生 " << mgr.countByType("Student")
                     << " 人, 教师 " << mgr.countByType("Teacher") << " 人" << endl;

                auto *mx = mgr.maxKey();
                auto *mn = mgr.minKey();
                if (mx) cout << "max_element: " << mx->getName() << " (" << mx->getKey() << ")" << endl;
                if (mn) cout << "min_element: " << mn->getName() << " (" << mn->getKey() << ")" << endl;
                break;
            }
            case 13:
                mgr.showRecent();
                break;
            case 14:
                mgr.showIndex();
                break;
            case 15: {
                cout << endl << "-- 异常处理演示 --" << endl;

                // 非法年龄
                cout << "1) 创建年龄=10的学生..." << endl;
                try {
                    Student s("S9999", "测试", 'M', 10, "计算机", 80);
                } catch (const InvalidAgeException &e) {
                    cerr << "   捕获: " << e.what() << endl;
                } catch (...) {
                    cerr << "   捕获未知异常" << endl;
                }

                // 非法性别
                cout << "2) 创建性别='X'的教师..." << endl;
                try {
                    Teacher t("T9999", "测试", 'X', 30, "讲师", 8000);
                } catch (const InvalidGenderException &e) {
                    cerr << "   捕获: " << e.what() << endl;
                } catch (...) {
                    cerr << "   捕获未知异常" << endl;
                }

                // 非法成绩
                cout << "3) 设置成绩=150..." << endl;
                try {
                    Student s("S8888", "测试2", 'F', 20, "物理", 85);
                    s.setScore(150);
                } catch (const InvalidScoreException &e) {
                    cerr << "   捕获: " << e.what() << endl;
                } catch (...) {
                    cerr << "   捕获未知异常" << endl;
                }

                // 非法工资
                cout << "4) 设置工资=-5000..." << endl;
                try {
                    Teacher t("T8888", "测试3", 'M', 40, "教授", 10000);
                    t.setSalary(-5000);
                } catch (const InvalidSalaryException &e) {
                    cerr << "   捕获: " << e.what() << endl;
                } catch (...) {
                    cerr << "   捕获未知异常" << endl;
                }

                // 重复ID
                cout << "5) 重复添加编号'2024001'..." << endl;
                try {
                    throw PersonException("模拟：编号 '2024001' 已存在！");
                } catch (const PersonException &e) {
                    cerr << "   捕获: " << e.what() << endl;
                }

                // 查找不存在
                cout << "6) 查找不存在的编号'X9999'..." << endl;
                try {
                    mgr.findById("X9999");
                } catch (const NotFoundException &e) {
                    cerr << "   捕获: " << e.what() << endl;
                } catch (...) {
                    cerr << "   捕获未知异常" << endl;
                }

                cout << "-- 异常演示完毕 --" << endl;
                break;
            }
            case 0:
                running = false;
                cout << "再见！" << endl;
                break;
            default:
                cout << "无效选择，请重试。" << endl;
                break;
            }
        } catch (const NotFoundException &e) {
            cerr << "查找失败: " << e.what() << endl;
        } catch (const PersonException &e) {
            cerr << "操作失败: " << e.what() << endl;
            clearCin();
        } catch (const exception &e) {
            cerr << "系统异常: " << e.what() << endl;
            clearCin();
        } catch (...) {
            cerr << "未知异常！" << endl;
            clearCin();
        }

        if (choice != 0) pause();
    }

    cout << endl << "退出，清理资源..." << endl;
    return 0;
}
