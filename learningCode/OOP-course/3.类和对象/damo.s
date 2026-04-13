	.file	"damo.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text._Z12min_noinlineii,"axG",@progbits,_Z12min_noinlineii,comdat
	.weak	_Z12min_noinlineii
	.type	_Z12min_noinlineii, @function
_Z12min_noinlineii:
.LFB1976:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.L2
	movl	-4(%rbp), %eax
	jmp	.L4
.L2:
	movl	-8(%rbp), %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1976:
	.size	_Z12min_noinlineii, .-_Z12min_noinlineii
	.text
	.globl	main
	.type	main, @function
main:
.LFB1978:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$3, -20(%rbp)
	movl	$5, -16(%rbp)
	movl	-20(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -20(%rbp)
	movl	%eax, -8(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jge	.L6
	movl	-8(%rbp), %eax
	jmp	.L10
.L6:
	movl	-4(%rbp), %eax
.L10:
	movl	%eax, -12(%rbp)
	movl	-20(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -20(%rbp)
	movl	-16(%rbp), %edx
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z12min_noinlineii
	movl	%eax, -12(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1978:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20260209"
	.section	.note.GNU-stack,"",@progbits
