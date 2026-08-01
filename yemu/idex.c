/*
 * CPU 核心 取指->译码->执行
 */

#include "yemu.h"
#include <assert.h>
#include <stdio.h>

/* 指令编码
 * 高 4 位是 opcode 低 4 位要么是 2bit 寄存器编号，要么是 4bit 内存地址
 * 一条指令正好占 1 字节
 * 寄存器只有 2 位宽
 */
typedef union inst {
    struct
    {
        u8 rs : 2, rt : 2, op : 4;
    } rtype; // 寄存器指令
    struct
    {
        u8 addr : 4, op : 4;
    } mtype; // 内存指令
} inst_t;

/*
 * 操作数提取宏：从指令中提取操作数
 * 在 case 分支直接展开为局部变量， trick!
 */
#define RTYPE(i) u8 rt = (i)->rtype.rt, rs = (i)->rtype.rs;
#define MTYPE(i) u8 addr = (i)->mtype.addr;

/*
 * 取值、译码、执行
 * pc 是 R[4] 的宏别名，即下一条指令在内存中的地址
 */
void idex()
{
    /* 取值 + 类型重解释
     * &M[pc] 拿到 M[pc] 的地址 转换为 unst_t，用 inst_t 位域布局的看这个字节。
     * rs 是源寄存器，rt 是目标寄存器
     * 0x00xx 寄存器-寄存器操作
     * 0x11xx 内存操作
     */
    inst_t *cur = (inst_t *)&M[pc];
    switch (cur->rtype.op) // 译码
    {
    case 0b0000: { // MOV
        RTYPE(cur);
        R[rt] = R[rs];
        pc++;
        break;
    }
    case 0b0001: { // ADD
        /* 两个 8 位数相加，结果自动截断到 8 位
         */
        RTYPE(cur);
        R[rt] += R[rs];
        pc++;
        break;
    }
    case 0b1110: { // LOD
        /* 从内存加载
         */
        MTYPE(cur);
        R[RA] = M[addr];
        pc++;
        break;
    }
    case 0b1111: { // STO
        /* 存储到内存
         */
        MTYPE(cur);
        M[addr] = R[RA];
        pc++;
        break;
    }
    default:
        assert(0); // 非法指令
    }
}
