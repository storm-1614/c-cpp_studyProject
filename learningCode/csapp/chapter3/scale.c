long scale(long x, long y, long z)
{
    long t = x + 4 * y + 12 * z;
    return t;
}

/*
	leaq	(%rdi,%rsi,4), %rax
	leaq	(%rdx,%rdx,2), %rdx
	leaq	(%rax,%rdx,4), %rax
*/
