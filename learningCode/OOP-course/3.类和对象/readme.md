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
    A(int, double);
};
```
## 对象组和对象指针

## string 类

## 向函数传递对象
