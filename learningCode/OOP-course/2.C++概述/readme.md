# C++ 在非面向对象方面的补充 

## 头文件
现在的C++标准库头文件不带后缀：  
``` cpp
#include <iostream>
```

## 注释行
以 `//` 开始注释内容只能在本行起作用  
以 `\*..*\` 方式的注释为其之间的所有内容

## C++ 的输入输出
C++ 提供了更安全的和更方便的 I/O 写法。  
`std::cout` `std::cin`  

``` cpp
std::cout << (1 << 2) << std::endl;
```

## 灵活的局部变量声明
C++ 运行在代码块的任何地方声明局部变量  

## 结构、联合和枚举名可以直接作为类型名

定义变量时不必再结构名、联合名或枚举名前冠以 `struct`、`union` 和 `enum`。  
C 语言：
``` c
typedef struct Point
{
    int x, y;
}PT;

Point pt;
```

C++:
``` cpp
struct Point
{
    int x, y;
};

Point pt;
```

啰啰嗦嗦的 struct 的新特性：
``` cpp
{
    /*
        struct Point
        {
            int x, y;
        };

        Point pt = {1, 2};
    */
    struct Point
    {
        int x, y;
        Point(int x, int y) : x(x), y(y)
        {
            std::cout << x << " " << y << std::endl;
        }
    };

    Point pt(1, 2);

    return 0;
}
```

## const 修饰符
不好的码风：  
``` c
for (index = 0; index < 512; ++index)
```
512 可读性不好。  

可以这样：

``` c
int bufSize = 512;
for (index = 0; index < bufSize; ++index)
```

但是用 const 就更好：

``` cpp
const int bufSize = 512;
for (index = 0; index < bufSize; ++index)
```
> 
> ``` c
> #define LIMIT 100
> ```
> 预编译时的符号替换    
> 无类型  
> define 不安全，直接替换。补救：`()`，`do{}while(0)`     


const 即常量修饰符。  

### const 指针
用例：
``` cpp
int value = 10;
int other = 20;
const int *p1 = &value;
//*p1 = 30; //报错
// p1 = &other; // 可以运行
std::cout << "p1=" << *p1 << ";" << "value=" << value << std::endl;
int *const p2 = &other;
// *p2 = 30; // 可以运行
// p2 = &value; // 报错
std::cout << "p2=" << *p2 << ";" << "other=" << other << std::endl;
```

地址不能变，但是值可以变  
``` cpp
int *const p = &value;
```

地址能变，但是值不能变  
``` cpp
const int *p = &value;
```


**勘误**:
``` cpp
    char * const name = "chen";
    name[3] = 'a';  // 段错误
```
编译通过，但是运行时错误（非法访问）  
应该这样写：
``` cpp
char arr[] = "chen";
name[3] = 'a';
```

> 勘误：~~如果 const 定义是一个整形常量，关键字 int 可以省略。~~(现在不能省略)  
- 函数形参可以用 const 说明，用于保证形参在函数内部不被改动。  
