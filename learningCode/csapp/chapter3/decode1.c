void decode1(long *xp, long *yp, long *zp)
{
    /* 局部变量会用额外的寄存器存放 */
    long x = *xp;
    long y = *yp;
    long z = *zp;
    *yp = x;
    *zp = y;
    *xp = z;
}
