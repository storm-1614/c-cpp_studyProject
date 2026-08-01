.PHONY: run clean test  # 伪目标声明

# 编译变量定义
CFLAGS = -Wall -Werror -std=c11 -O2 # 编译选项
CC = gcc # C 编译器
LD = gcc # 链接器

# 默认目标
yemu: yemu.o idex.o
	$(LD) $(LDFLAGS) -o yemu yemu.o idex.o

yemu.o: yemu.c yemu.h
	$(CC) $(CFLAGS) -c -o yemu.o yemu.c

idex.o: idex.c yemu.h
	$(CC) $(CFLAGS) -c -o idex.o idex.c

run: yemu
	@./yemu

# @ 抑制命令回显，只显示程序输出

clean:
	rm -f test yemu *.o

# 一次完成编译加运行
test: yemu
	$(CC) $(CFLAGS) -o test idex.o test.c && ./test
