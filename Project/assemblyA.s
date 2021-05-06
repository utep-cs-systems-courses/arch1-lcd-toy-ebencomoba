	.arch msp430g2553
	.p2align 1,0

	.data
t1:	.word 4
	
	.text
	.global keepScope
keepScope:
	mov ship_col, r12	;ship_col
	add t1, r12		;ship_col+4
	mov #0xffff, r13	;Parameter2
	call #drawScope		;drawScope(t1, COLOR_WHITE)
	pop r0			;return

	.text
jt:
	.word case0
	.word case1
	.word case2
	.word case3
	.word case4
	.word case5
	.word case6

	.global selectPrey
selectPrey:
	cmp #7, r12	;prey_state-2
	jhs other	;Jump to other
	add r12, r12
	mov jt(r12), r0
case0:
case1:
case2:	
	mov #0, r12
	jmp esac
case3:
case4:	
	mov #1, r12
	jmp esac
case5:
case6:	
	mov #2, r12
	jmp esac
other:
	mov #3, r12
esac:
	pop r0
	
