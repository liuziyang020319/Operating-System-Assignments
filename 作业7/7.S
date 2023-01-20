	.file	"7.c"
	.text
	.globl	GetTop
	.type	GetTop, @function
GetTop:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movl	(%rax), %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	GetTop, .-GetTop
	.globl	Pop
	.type	Pop, @function
Pop:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L7
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L4
.L7:
	nop
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	Pop, .-Pop
	.globl	Ins
	.type	Ins, @function
Ins:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	-28(%rbp), %edx
	movl	%edx, (%rax)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	Ins, .-Ins
	.globl	Moniter_init
	.type	Moniter_init, @function
Moniter_init:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_mutex_init@PLT
	movq	-24(%rbp), %rax
	addq	$48, %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_cond_init@PLT
	movq	-24(%rbp), %rax
	movl	$16, 96(%rax)
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 8(%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, (%rax)
	movl	$0, -8(%rbp)
	jmp	.L10
.L11:
	call	rand@PLT
	movl	%eax, %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$3, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	sall	$2, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	Ins
	addl	$1, -8(%rbp)
.L10:
	cmpl	$15, -8(%rbp)
	jle	.L11
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	Moniter_init, .-Moniter_init
	.globl	Monitor_getTASK
	.type	Monitor_getTASK, @function
Monitor_getTASK:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	pthread_mutex_lock@PLT
	movq	-40(%rbp), %rax
	movl	96(%rax), %eax
	cmpl	$1, %eax
	jne	.L13
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	jmp	.L17
.L13:
	movq	-40(%rbp), %rax
	movl	96(%rax), %eax
	leal	-1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 96(%rax)
	jmp	.L15
.L16:
	movq	-40(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	$48, %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pthread_cond_wait@PLT
.L15:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	cmpl	$1, %eax
	jle	.L16
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	GetTop
	movl	%eax, -24(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	Pop
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	GetTop
	movl	%eax, -20(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	Pop
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	movl	$0, -16(%rbp)
	movl	$1, -12(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	Monitor_getTASK, .-Monitor_getTASK
	.globl	Monitor_putResult
	.type	Monitor_putResult, @function
Monitor_putResult:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	pthread_mutex_lock@PLT
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	-12(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	Ins
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	cmpl	$2, %eax
	jne	.L19
	movq	-8(%rbp), %rax
	addq	$48, %rax
	movq	%rax, %rdi
	call	pthread_cond_signal@PLT
.L19:
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	Monitor_putResult, .-Monitor_putResult
	.section	.rodata
.LC0:
	.string	"%d %p\n"
	.text
	.globl	worker
	.type	worker, @function
worker:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	worker, .-worker
	.comm	thread,72,32
	.section	.rodata
.LC1:
	.string	"%d "
.LC2:
	.string	""
	.align 8
.LC3:
	.string	"============== TASK begin =============="
.LC4:
	.string	"Reduce sum = %d Target = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movl	$104, %edi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	Moniter_init
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movl	$0, -64(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -48(%rbp)
	jmp	.L23
.L24:
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	addl	%eax, -64(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -48(%rbp)
.L23:
	cmpq	$0, -48(%rbp)
	jne	.L24
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movq	$0, -56(%rbp)
	jmp	.L25
.L26:
	movq	-56(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-56(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	leaq	thread(%rip), %rax
	leaq	(%rdx,%rax), %rdi
	leaq	-32(%rbp), %rax
	movq	%rax, %rcx
	leaq	worker(%rip), %rdx
	movl	$0, %esi
	call	pthread_create@PLT
	movl	$1, %edi
	call	usleep@PLT
	movq	-56(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -56(%rbp)
.L25:
	movq	-56(%rbp), %rax
	cmpq	$7, %rax
	jle	.L26
	movl	$0, -60(%rbp)
	jmp	.L27
.L28:
	movl	-60(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	thread(%rip), %rax
	movq	(%rdx,%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	addl	$1, -60(%rbp)
.L27:
	cmpl	$7, -60(%rbp)
	jle	.L28
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movl	(%rax), %eax
	movl	-64(%rbp), %edx
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
