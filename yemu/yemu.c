#include "yemu.h"
#include <stdio.h>

int main()
{
    while (1)
    {
        if (M[pc] == 0) // TRAP 停机时
        {
            printf("Hit GOOD trap @ pc = %d.\n", pc);
            for (int i = 0; i < NMEM; i++)
            {
                printf("M[%02d] = 0x%02x (%d)\n", i, M[i], M[i]);  // 打印内存状态
            }
            break;
        }
        idex(); // 执行一条命令
    }
    return 0;
}

/*
 * CPU 状态定义 + 内存初始化
 * R：6 个寄存器，都为 0
 * M：内存
 */
u8 R[NREG], M[NMEM] = {
                0b11100111, // lod [7]
                0b00000100, // mov R1 RA
                0b11100110, // LOD [6]
                0b00010001, // ADD RA R1
                0b11111000, // STO [8]
                0b00000000, // TRAP
                0b00010000, // [6]
                0b00100001, // [7]
                0b00000000, // [8]
};
