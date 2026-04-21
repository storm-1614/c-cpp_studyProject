# 3. 类和对象

## 类和对象的基本概念
### 结构体和类
C++ 提供了一种比结构体更安全有效的数据类型——类。类与结构体十分相似。  

C++ 中的 struct 和 class 基本是通用的，唯有几个细节不同：  
- **成员默认访问权限不一样**：class 中类中的成员默认都是 private 属性的。而在 struct 中结构体中的成员默认都是 public 属性的。  

- class 继承默认是 private 继承，而 struct 继承默认是 public 继承。    

- class 可以用于定义模板参数，struct 不能用于定义模板参数。    

为了保护类的数据安全，C++ 将类的成员分为：私有(private) 、公有(public) 和保护(protected)成员。  


#### private

private（私有）成员只能在类的内部访问，外部无法直接访问。通常用于保护类的数据安全，防止被随意修改。

#### public

public（公有）成员可以在类的内部和外部访问。一般用于提供类对外的接口，如成员函数等。

#### protect

protected（保护）成员可以在类的内部以及其子类中访问，但外部无法直接访问。常用于继承时让子类访问父类的成员。

#### 成员函数的定义
**内联函数**：定义在类内的成员函数。即该函数的函数体放在类体内。  
**外联函数**：在类声明体外部实现的成员函数。它们在类内只声明函数原型，具体实现写在类外，并通过作用域运算符::与类名关联。  
``` cpp
class Complex
{
  public:
    void func()  // 内联函数
    {
        return;
    }
    int func1();
};

int Complex::func1()  // 外联函数，在“类外”定义成员函数  
{
    return 1;
}
```

**在类定义中只给出成员函数的原型，而将函数的定义在类的外部，是C++程序设计的好习惯。**  
例:  
damo.h
``` cpp
class Complex
{
    public:
    int func1();
    int func2();
};
```

damo.c
``` cpp
#include "damo.h"

int Complex::func1()
{
    return 0;
}

int Complex::func2()
{
    return 9;
}
```

分离声明和实现。  
函数定义在类外，但在类内原型声明或类外定义前面冠以 `inline` 关键字。也可以成为内联函数。  
**这样定义和声明要放在同一个文件内**  
``` cpp
class A
{
    int X, Y;

  public:
    int a()
    {
        return X;
    }
    int b()
    {
        return Y;
    }
    int c(); // 在类外定义为内联函数
    inline int d();
};

inline int A::c()
{
    return a()+b();
}

int d()
{
    return 10;
}
```
C++ 把类的变量称为类的对象，对象也被称为该类的实例。  
一个类也就是用户声明的一个数据类型，而类的对象则是该类类型的一个实例。  
### 对象的定义和使用
#### 定义
在定义类的同时，直接定义对象。  
``` cpp
class Point{
    ...
} op1, op2;
```
定义类之后在使用时再定义对象，格式与一般变量的定义格式相同。  
```cpp
Point op1, op2;
```

#### 访问
通过对象名和对象选择符访问对象中的成员：  
```cpp
对象名.数据成员名;
对象名.成员函数名(实参参数表);
```

不能直接访问对象的私有成员：  
``` cpp
class B
{
  private:
    int x, y;

  public:
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }
};

int main(int argc, char *argv[])
{
    B b;
    std::cout << b.getx();
    std::cout << b.x(); //ERROR: 不能直接访问私有成员  
}
```

通过指向对象的指针访问对象中的成员
```cpp
class Date
{
  public:
    int year; // 年份成员变量
};

Date d, *ptr; // 定义Date类的对象d和指向Date对象的指针ptr
ptr = &d;     // 让ptr指向对象d
cout << ptr->year; // 通过指针ptr访问对象d的成员year并输出
```

通过对象引用访问对象中的成员：  
``` cpp
Date d1;
Date &d2 = d1;
cout << d1.year;
cout << d2.year;
```

### 类的作用域和类成员的访问属性
定义：在类的一对花括号所形成的作用域。  
作用域内：成员函数可以不受限制地访问该类的其他成员。  
作用域外：访问类的数据成员和成员函数时要受到一定的限制，有时生长所不允许的。  


## 构造函数和析构函数
### 对象的初始化和构造函数
对象的初始化：
1. 使用初始化列表  

```  cpp
class Complex
{
  public:
    int x, y;
};
Complex c1 = {1, 2};
```
缺点：只能给共有数据进行赋值。  

2. 使用自定义的成员函数

``` cpp
class Complex
{
  private:
    int x, y;
  public:
    void init(int a, int b)
    {
        x = a;
        y = b;
    }
};
```

3. 构造函数

构造函数的名字必须与类名相同，且不能有返回值和返回值类型。  
定义对象时，编译系统会自动调用构造函数。  

```cpp
class Complex
{
  private:
    double real;
    double imag;

  public:
    Complex(double r, double i)
    {
        real = r;
        imag = i;
    }
};

int main()
{
    Complex A(1.1, 2.2); // 直接赋值
}
```

建立对象的两种方式：  
1. `类名 对象名(实参表);`
2. `类名 *指针变量名 = 类名(实参表);`

没有给类定义构造函数，则编译系统自动生成一个默认的构造函数（不带任何东西）。  

### 用成员初始化列表对数据成员初始化
对数据成员的初始化工作一般在够展示中赋值语句进行。  
也可以采用初始化列表对数据成员进行初始化:  
``` cpp
class Complex
{
  private:
    double real;
    double imag;

  public:
    Complex(double r, double i) : real(r), imag(i)
    {
    }
};
```
用成员初始化列表对**引用类型的数据成员**和 **const 修饰的数据成员**初始化。  
数据成员是按照它们在类中声明的顺序进行初始化的，与它们在成员初始化类别中列出的顺序无关。  

### 构造函数重载
C++ 允许重载构造函数，以适应不同的场合。  
``` cpp
class A{
  public:
    A();
    A(int);
    A(int, char);
    A(float, char);
};

int main()
{
    A x;
    A y(2);
    A z(10, 'z');
    A w(4.4, 'w');
}
```
无参构造函数创建对象时用 `Data a;` 不能用 `Data a();`(其与函数声明类似)  
可以定义带默认参数的构造函数。  

## 析构函数
特殊成员函数，与构造函数相反，执行清理的任务。  
和类名相同的函数前面加上 `~`  
``` cpp
class Complex
{
    Complex()
    {
    }
    ~Complex()
    {
    }
};
```
析构函数没有参数，一个类只能有一个析构函数。  
若没有显式定义，编译系统会自动生成一个默认的空白析构函数。它能够释放对象所占用的内存空间。   

- 用运算符 new 在构造函数中分配的内存空间，需用 delete 在析构函数中释放，不然会内存泄漏。  

如果一个对象的生命周期结束时，该对象将释放，析构函数就会被自动调用。  
用 new 创建的对象，在用 delete 运算符释放时，delete 会自动调用析构函数。  
如果没有用 delete ，程序运行结束都不会调用析构函数。  

## 对象数组和对象指针
### 对象数组
C++ 对象数组是由同一类的多个对象组成的数组。就像 int、double 等基本类型可以组成数组一样，类类型也可以组成对象数组。对象数组的每个元素都是该类的一个对象，数组会自动调用类的构造函数为每个对象初始化。

#### 示例

假设有一个简单的类 `Student`：

```cpp
class Student {
private:
    int id;
    std::string name;
public:
    Student(int i, std::string n) : id(i), name(n) {}
    void show() {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }
};
```

定义对象数组并初始化：

```cpp
Student students[3] = {
    Student(1, "Tom"),
    Student(2, "Jerry"),
    Student(3, "Alice")
};

for(int i = 0; i < 3; ++i) {
    students[i].show();
}
```

**说明：**
- 数组 `students` 包含 3 个 `Student` 对象。
- 创建数组时，会分别调用构造函数初始化每个对象。
- 可以像普通数组一样通过下标访问每个对象，并调用其成员函数。

如果类有默认构造函数，也可以这样定义：  

```cpp
Student students[5]; // 5个Student对象，调用默认构造函数
```

**注意事项：**
- 如果类没有默认构造函数，必须用上面第一种方式初始化对象数组。  
- 对象数组常用于需要管理多个同类对象的场景，比如班级学生、商品列表等。  

### 对象指针
C++ 对象指针是指向类对象的指针变量。通过对象指针可以访问对象的成员（用 -> 运算符），也可以动态创建对象数组。

#### 示例

假设有如下类：

```cpp
class Student {
public:
    int id;
    std::string name;
    void show() {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }
};
```

- 1. 对象指针的基本用法

```cpp
Student s(1, "Tom");
Student* p = &s; // p是指向对象s的指针
p->show();       // 通过指针访问成员
```

- 2. 动态创建对象

```cpp
Student* p = new Student{2, "Jerry"};
p->show();
delete p; // 用完后释放内存
```

- 3. 动态创建对象数组

```cpp
Student* arr = new Student[3]; // 创建3个Student对象
arr[0].id = 1; arr[0].name = "Tom";
arr[1].id = 2; arr[1].name = "Jerry";
arr[2].id = 3; arr[2].name = "Alice";

for(int i = 0; i < 3; ++i) {
    arr[i].show();
}
delete[] arr; // 释放数组
```

注意：  
``` cpp
Complex *p = new Complex[2]{{1.1, 2.2}, {3.3, 4.4}};
p[1].show();// 不能用 p[1]->show();
```

**总结：**
- 对象指针可以指向单个对象或对象数组。
- 通过对象指针可以访问对象成员。
- 用 new 创建的对象（数组）需要手动 delete（delete[]）释放内存。

### this 指针
> 对象只包含数据成员，不包含成员函数(用 sizeof 证明)  

在 C++ 中，this 指针是类的每个成员函数内部都隐含的一个指针，指向调用该成员函数的对象本身。

#### 作用
- 访问当前对象的成员变量和成员函数。
- 区分成员变量和同名的参数或局部变量。
- 支持链式调用（返回 *this）。

#### 示例

```cpp
class Student {
private:
    int id;
public:
    void setId(int id) {
        this->id = id; // this->id 表示成员变量，id 表示参数
    }
    Student& setAndReturn(int id) {
        this->id = id;
        return *this; // 返回当前对象的引用
    }
};
```

#### 说明
- 在成员函数内部，this 是一个指向当前对象的指针，类型为 `Student*`。
- 通过 `this->成员名` 明确表示访问成员变量。
- 可以用 `return *this;` 实现链式调用。

**注意：**  
静态成员函数没有 this 指针，因为它们不属于任何对象。

## string 类
c 语言 string.h 的栈溢出风险：  
``` cpp
#include <string.h>
#include <iostream>

struct test{
    int x;
    char a[4];
    int y;
    char b[4];
    int z;
};

int main(int argc, char *argv[])
{
    test t1{1, "abc", 1, "xyz", 1};
    std::cout << t1.x << " " << t1.y << " " << t1.z << std::endl;
    strcat(t1.a, t1.b);
    std::cout << t1.a << std::endl;
    std::cout << t1.x << " " << t1.y << " " << t1.z << std::endl;

    return 0;
}
```

string 的类运算符
| 运算符         | 作用描述                         | 示例                          |
|:--------------|:--------------------------------|:-----------------------------|
| =             | 赋值运算符                       | s1 = s2;                     |
| +             | 字符串连接                       | s3 = s1 + s2;                |
| +=            | 追加字符串                       | s1 += "abc";                 |
| ==            | 判断字符串是否相等               | if(s1 == s2)                 |
| !=            | 判断字符串是否不相等             | if(s1 != s2)                 |
| <, >, <=, >=  | 字典序比较                       | if(s1 < s2)                  |
| []            | 访问指定位置字符                 | `char c = s1[0];`              |
| <<, >>        | 输入输出流运算符                 | `std::cin >> s1; std::cout << s1;` |

## 向函数传递对象
### 使用对象作为函数参数
其实和普通变量一样……   

## 对象的赋值和复制
### 对象赋值语句
A 和 B 是同一类的两个对象，那么有下述对象赋值语句:
``` cpp
B = A;
```
把对象 A 的数据成员的值逐位复制给对象 B。  

等号 C++ 已经重载过了，做了非常多的工作。  

运算符重载的例子：  
``` cpp
#include <iostream>

class MyClass
{
  public:
    MyClass(int a, int b) : x(a), y(b)
    {
    }
    MyClass() : x(0), y(0)
    {
    }
    // MyClass &operator=(MyClass &&) = default;
    // MyClass &operator=(const MyClass &) = default;
    MyClass &operator=(const MyClass &p)
    {
        std::cout << "= operator overload" << std::endl;
        this->x = p.x;
        this->y = p.y;
        return *this;
    }

    MyClass operator+(const MyClass &p)
    {
        std::cout << "+ operator overload" << std::endl;
        MyClass res;
        res.x = this->x += p.x;
        res.y = this->y += p.y;
        return res;
    }
    void print()
    {
        std::cout << "x = " << x << std::endl;
        std::cout << "y = " << y << std::endl;
    }

  private:
    int x, y;
};

int main(int argc, char *argv[])
{
    MyClass a(1, 2), b(2, 3);
    std::cout << "a: " << std::endl;
    a.print();
    std::cout << "b: " << std::endl;
    b.print();
    // b.operator=(a);
    b = a;
    std::cout << "b: " << std::endl;
    b.print();
    // a.operator+(b);
    a = a + b;
    std::cout << "a: " << std::endl;
    a.print();
    return 0;
}
```
### 对象的复制：拷贝构造函数
在定义对象时用另一个对象初始化。   
有两种方式，带入或赋值。两者等价。  
``` cpp
Point p2(p1); // 代入法
Point p2 = p1; // 赋值法
```

缺省拷贝构造函数，C++ 会自动将一个已存在的对象赋值给新对象，逐一赋值变量的成员。  

拷贝构造函数（特殊的构造函数，用于依据已存在的对象建立一个新对象）：  
``` cpp
类名 (const 类名 & 对象名)
{
    // 拷贝构造函数的函数体
}
```

例：
``` cpp
class MyClass
{
  public:
    MyClass(int a, int b) : x(a), y(b)
    {
    }
    MyClass() : x(0), y(0)
    {
    }
    MyClass(const MyClass &p)
    {
        x = 2 * p.x;
        y = 2 * p.y;
    }
};
int main()
{
    MyClass a(1, 2), b(a);
    std::cout << "a: " << std::endl;
    a.print();
    std::cout << "b: " << std::endl;
    b.print();
}
```

输出：
```
a: 
x = 1
y = 2
b: 
x = 2
y = 4
```

注意：
``` cpp
MyClass p1 = p2; //赋值
p1 = p2;         // 复制
```

1. 当类的一个对象去初始化该类的另一个对象时，拷贝构造函数将会被调用。  
2. 当函数的形参是类的对象，在调用函数进行形参和实参结合时，拷贝函数将会被调用。  
3. 当函数的返回值是类的对象时，函数调用完毕将返回值（对象）带回函数调用处时。  

```cpp
Point fun2()
{
    Point p1(10, 20);
    return p1;
}

int main()
{
    Point p2;
    p2 = fun2(); // 赋值 又拷贝
}
```


## 静态成员
在类定义中，它的成员可用关键字 static 定义，无论创建多少个类的对象，静态成员都只有一个副本。  

``` cpp
#include <iostream>

class MyClass
{
  public:
    MyClass()
    {
        count++;
    }
    ~MyClass()
    {
        count--;
    }
    static int count;
};

int MyClass::count = 0;

int main(int argc, char *argv[])
{
    MyClass *a = new MyClass[100];
    MyClass b;

    std::cout << a->count << std::endl;
    delete[] a;
    std::cout << a->count << std::endl;
}
```

输出：
```
101
1
```

静态成员甚至可以用类名直接调用：
``` cpp
MyClass::count = 10;
```
## 友元
### 友元函数
友元函数不是当前类的成员函数，而是独立于当前类的外部函数，但它可以访问该类的所有对象的成员，包括私有成员。  
```cpp
friend void disp(Girl &g);
```
## 类的组合

## 常类型
