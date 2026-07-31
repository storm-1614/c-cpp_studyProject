long arith(long x, long y, long z)
{
    long t1 = x ^ y;
    long t2 = z * 48;
    long t3 = t1 & 0x0f0f0f0f;
    long t4 = t2 - t3;
    return t4;
}

/*
	xorq	%rsi, %rdi          ; t1 = x ^ y
	leaq	(%rdx,%rdx,2), %rax ; 3 * z
	salq	$4, %rax            ; t2 = 16 * (3 * z) = 48 * z
	andl	$252645135, %edi    ; t3 = t1 & 0x0f0f0f0f
	subq	%rdi, %rax          ; return t2 - t3
	ret
*/

long arith2(long x, long y, long z)
{
    long t1 = x | y;
    long t2 = t1 >> 3;
    long t3 = ~t2;
    long t4 = z - t3;
    return t4;
}

/*
	orq	%rsi, %rdi
	sarq	$3, %rdi
	notq	%rdi
	movq	%rdx, %rax
	subq	%rdi, %rax
	ret
*/
