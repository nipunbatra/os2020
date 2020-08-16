	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movl	$10, -20(%rbp)
	movslq	-20(%rbp), %rax
	shlq	$2, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -16(%rbp)
	movl	$0, -24(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str(%rip), %rdi
	movl	-24(%rbp), %esi
	movq	-16(%rbp), %rax
	movslq	-24(%rbp), %rcx
	shlq	$2, %rcx
	addq	%rcx, %rax
	movq	%rax, %rdx
	movb	$0, %al
	callq	_printf
	movl	%eax, -28(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB0_1
LBB0_4:
	leaq	L_.str.1(%rip), %rdi
	leaq	_main(%rip), %rax
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.2(%rip), %rdi
	leaq	-20(%rbp), %rsi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%dth position of ptr is at:%p\n"

L_.str.1:                               ## @.str.1
	.asciz	"Main is at: %p\n"

L_.str.2:                               ## @.str.2
	.asciz	"Num is at: %p\n"


.subsections_via_symbols
