long arith(long x)
{
    return x / 8;
}

/*
    leaq	7(%rdi), %rax
	testq	%rdi, %rdi
	cmovns	%rdi, %rax
	sarq	$3, %rax
	ret
*/
