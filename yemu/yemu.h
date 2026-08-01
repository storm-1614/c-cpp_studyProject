#include <stdint.h>

typedef uint8_t u8;
#define NMEM 16 // 内存大小：16

enum
{
    RA,
    R1,
    R2,
    R3,
    PC,
    NREG
}; // 寄存器：5 个
extern u8 M[NMEM], R[NREG];
#define pc (R[PC])  // 定义 PC 是 R[4]

void idex();
