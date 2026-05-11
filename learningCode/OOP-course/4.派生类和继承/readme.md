# 派生类和继承

## 派生类的概念
在c++中，类的相互关系主要可以分为三类：  
![](./src/1.png)

继承代表了 **is a** 关系：  
![](./src/2.png)
已有的类叫基类，新建的类叫派生类。  


### protect 修饰符
和 private 相似。但是在继承中，父类可以访问子类的 protect 成员，但是子类不能访问父类的 protect 成员。  
而 private 仅自己可以访问。  
详细看：[https://www.runoob.com/cplusplus/cpp-class-access-modifiers.html](https://www.runoob.com/cplusplus/cpp-class-access-modifiers.html)  
### 继承格式
``` cpp
// 基类
class Shape 
{
   public:
      void setWidth(int w)
      {
         width = w;
      }
      void setHeight(int h)
      {
         height = h;
      }
   protected:
      int width;
      int height;
};
 
// 派生类
class Rectangle: public Shape
{
   public:
      int getArea()
      { 
         return (width * height); 
      }
};
```

### 派生类的构成
``` cpp
class 派生类名: 继承方式 基类名{
    // 派生类新增的数据成员和成员函数
};
```

``` cpp
class employee: public person{}; // 公有继承
class employee: private person{};// 私有继承
class employee: protect person{};// 保护继承
```

- 如果没有显式定义继承方式，系统默认为 private。  

### 基类成员在派生类中的访问属性
![](./src/5.jpg)  

![](./src/3.png)  

在基类中的访问属性为 private，在派生类中访问属性还是不可访问。所以有 protected 访问属性。  
![](./src/6.jpg)  

内部访问：由派生类中新增成员对基类继承来的成员的访问。  
对象访问：在派生类外部，通过派生类的对象对从基类继承的成员的访问。  
``` c
#include <iostream>

class Base {
protected:
    int y = 20;

public:
    int x = 10;
};

class Derived : public Base {
public:
    void show() {
        std::cout << x << std::endl; // 内部访问：派生类成员函数访问继承成员
        std::cout << y << std::endl; // 内部访问：protected 也可访问
    }
};

int main() {
    Derived d;
    d.show();                      // 调用内部访问
    std::cout << d.x << std::endl; // 外部访问：通过对象访问继承的 public 成员
    // std::cout << d.y << std::endl; // 外部访问失败：protected
}
```

![](./src/7.jpg)
        
#### 公有继承的访问规则

![](./src/4.png)  



## 派生类的构造函数和析构函数

派生类对象的构造与析构顺序：  

构造顺序：先基类，后派生类。若有成员对象，先构造成员对象，再执行派生类构造函数体。  
析构顺序：先派生类，后基类。成员对象析构在派生类析构函数体执行完之后、基类析构之前。  

简短示例：
``` c
#include <iostream>

struct Member {
    Member() { std::cout << "Member()\n"; }
    ~Member() { std::cout << "~Member()\n"; }
};

struct Base {
    Base() { std::cout << "Base()\n"; }
    ~Base() { std::cout << "~Base()\n"; }
};

struct Derived : public Base {
    Member m;
    Derived() { std::cout << "Derived()\n"; }
    ~Derived() { std::cout << "~Derived()\n"; }
};

int main() {
    Derived d;
}
```
输出：
```
Base()
Member()
Derived()
~Derived()
~Member()
~Base()
```

时序图（构造 / 析构）：
```
构造：Base() -> Member() -> Derived()
析构：~Derived() -> ~Member() -> ~Base()
```

派生类构造函数：
``` cpp
派生类名(参数表):基类名(参数表)
{
}
```
派生类的构造函数定义可以定义在类的外部。此时类中不包括基类构造函数名及其参数表。只在类外定义构造函数时才将它列出。    

示例：
``` cpp
#include <iostream>

class Base {
public:
    Base(int v) { std::cout << "Base(" << v << ")\n"; }
};

class Derived : public Base {
public:
    Derived(int v); // 仅声明
};

Derived::Derived(int v) : Base(v) {
    std::cout << "Derived(" << v << ")\n";
}

int main() {
    Derived d(5);
}
```

简化版本（基类默认构造）：
``` cpp
#include <iostream>

class Base {
public:
    Base() { std::cout << "Base()\n"; }
};

class Derived : public Base {
public:
    Derived();
};

Derived::Derived() {
    std::cout << "Derived()\n";
}

int main() {
    Derived d;
}
```

基类的构造函数使用默认构造函数或**不带参数的构造函数**时，在派生类中定义构造函数时可以省略前导（初始化成员表），也可以不定义构造函数。  

当基类没有默认构造函数，它所有的派生类都被必须定义构造函数。  

含有对象成员的派生类的构造函数：  
```
派生类名(参数总表):基类名(参数表1), 对象成员名1(参数表1), ... , 对象成员名n(参数表n)
{
    // 派生类新增成员的初始化语句
}
```
## 调整基类成员在派生类中的访问属性

## 多重继承

## 基类和派生类对象之间的赋值兼容关系

## 参考资料
1. [知乎：轻松理解c++中的继承与派生](https://zhuanlan.zhihu.com/p/603637625)  
