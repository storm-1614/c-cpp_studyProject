# stdarg.h 笔记

`stdarg.h` 声明了 `va_list` 类型，并定义了 `va_start()`、`va_arg()`、`va_end()` 三个宏。其用于在，访问可变数量的参数，可变参数的函数通常是通过在函数参数列表的末尾用省略号定义。  

`stdarg.h` 由编译器提供，GCC 用各种内建实现来提供，暴露给 `stdarg.h`。也就是说，可变参数是编译层面的事情。编译器为不同的 ABI 实现了特定的可变参数，这里就不深入研究，要涉及到各种 ABI 的函数参数约定挺麻烦的。  

你以为呢，`stdarg.h` 其实就是 define 到内建结构而已：  
``` c
#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif

#define va_start(...) __builtin_c23_va_start(__VA_ARGS__)
#else
#define va_start(v,l)	__builtin_va_start(v,l)
#endif
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v,l)	__builtin_va_arg(v,l)
#if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L \
    || __cplusplus + 0 >= 201103L
#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif
#define __va_copy(d,s)	__builtin_va_copy(d,s)
```

在 `man stdarg` 里这样写的。宏为了描述把宏加上类型，其实它们都是宏：  
``` c
#include <stdarg.h>

void va_start(va_list ap, last);
type va_arg(va_list ap, type);
void va_end(va_list ap);
void va_copy(va_list dest, va_list src);
```

## `va_list`
va_list 存储可变参数信息的类型供后面三个宏使用，在 x86 实现大致如下：  
```c
struct __va_list_tag {
    unsigned int gp_offset;
    unsigned int fp_offset;
    void *overflow_arg_area;
    void *reg_save_area;
}
```
总之，要挖编译器源码，还得翻各 ABI 的实现，我就找博客贴着凑合着看吧。  

用法就是声明声明一个用于后面给宏传参。  

## `va_start`
初始化 `va_list ap` 还需要有一个固定参数放在 last。  

## `va_arg` 
在可变参数中依次获取每个可变参数的值，传入 ap ，然后把类型传入 type ，返回当前可变参数中的下一个参数。  

## `va_end`
用于清理 `va_list` 变量，使其不再指向任何有效的内存位置，在可变参数函数列表中使用，结束可变参数的处理。  

## 示例
最经典的参数求和：  
``` c
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int sum(int count, ...)
{
    int total = 0;
    va_list args;

    va_start(args, count);

    for (int i = 0; i < count; i++)
        total += va_arg(args, int);
    va_end(args);

    return total;
}

int main(int argc, char *argv[])
{
    printf("Sum of 1, 2, 3: %d\n", sum(3, 1, 2, 3));
    printf("Sum of 4, 5, 6, 7: %d\n", sum(4, 4, 5, 6, 7));

    return EXIT_SUCCESS;
}
```

甚至可以实现自己的 printf，我目前就只实现了 %d 和 %s：  
``` c
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void my_putnbr(int val)
{
    unsigned int unum;
    if (val < 0)
    {
        putchar('-');
        /*
         * 直接取反会导致溢出
         */
        unum = (unsigned int)(-(val + 1)) + 1;
    }
    else
        unum = (unsigned int)(val);

    if (unum >= 10)
        my_putnbr(unum / 10);
    putchar('0' + unum % 10);
}

void my_putstr(const char *str)
{
    for (; *str != '\0'; str++)
        putchar(*str);
    putchar('\0');
}

void my_printf(const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);

    for (const char *p = fmt; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        p++;
        if (*p == 'd')
            my_putnbr(va_arg(arg, int));

        else if (*p == 's')
            my_putstr(va_arg(arg, char *));

        else if (*p == '%')
            putchar('%');
    }
    va_end(arg);
}

int main(int argc, char *argv[])
{
    my_printf("int:%d, string: %s %", -2131, "adas");
    return EXIT_SUCCESS;
}
```

## 参考资料
1. [ 从frida到va_list ](https://www.cnblogs.com/lordtianqiyi/p/18603315)
2. [揭秘X86架构C可变参数函数实现原理](https://zhuanlan.zhihu.com/p/94036267)
3. [gcc-mirror/gcc](https://github.com/gcc-mirror/gcc)
4. [C 标准库 - <stdarg.h>](https://www.runoob.com/cprogramming/c-standard-library-stdarg-h.html)
