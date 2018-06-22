//
// version
//
	.vers	6

//
// execution framework
//
__start:
	call	_main
	call	_exit
__stop:
	jmp	__stop

//
// Integer readInteger()
//
_readInteger:
	asf	0
	rdint
	popr
	rsf
	ret

//
// void writeInteger(Integer)
//
_writeInteger:
	asf	0
	pushl	-3
	wrint
	rsf
	ret

//
// Character readCharacter()
//
_readCharacter:
	asf	0
	rdchr
	popr
	rsf
	ret

//
// void writeCharacter(Character)
//
_writeCharacter:
	asf	0
	pushl	-3
	wrchr
	rsf
	ret

//
// Integer char2int(Character)
//
_char2int:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// Character int2char(Integer)
//
_int2char:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// void exit()
//
_exit:
	asf	0
	halt
	rsf
	ret

//
// void main()
//
_main:
	asf	6
	pushc	10
	popl	5
	call	_readInteger
	pushr
	popl	0
	pushc	2
	popl	1
	pushc	1
	popl	2
	pushc	1
	popl	3
	jmp	__2
__1:
	pushl	2
	pushl	1
	mul
	pushl	3
	pushc	1
	mul
	add
	popl	2
	pushl	3
	pushl	1
	mul
	popl	3
	pushl	1
	pushc	1
	add
	popl	1
__2:
	pushl	1
	pushl	0
	le
	brt	__1
__3:
	pushl	2
	pushl	3
	call	_gcd
	drop	2
	pushr
	popl	4
	pushl	2
	pushl	4
	div
	popl	2
	pushl	3
	pushl	4
	div
	popl	3
	pushl	2
	pushc	10
	pushl	5
	call	_powerOf
	drop	2
	pushr
	mul
	popl	2
	pushl	2
	pushl	3
	div
	popl	0
	pushl	5
	pushc	1
	sub
	popl	1
	pushl	0
	pushc	10
	pushl	5
	call	_powerOf
	drop	2
	pushr
	div
	call	_writeInteger
	drop	1
	pushc	44
	call	_writeCharacter
	drop	1
	jmp	__5
__4:
	pushl	0
	pushc	10
	pushl	1
	call	_powerOf
	drop	2
	pushr
	div
	pushc	10
	mod
	call	_writeInteger
	drop	1
	pushl	1
	pushc	1
	sub
	popl	1
__5:
	pushl	1
	pushc	0
	gt
	brt	__4
__6:
	pushc	10
	call	_writeCharacter
	drop	1
__0:
	rsf
	ret

//
// Integer gcd(Integer, Integer)
//
_gcd:
	asf	0
	jmp	__9
__8:
	pushl	-4
	pushl	-3
	gt
	brf	__11
	pushl	-4
	pushl	-3
	sub
	popl	-4
	jmp	__12
__11:
	pushl	-3
	pushl	-4
	sub
	popl	-3
__12:
__9:
	pushl	-4
	pushl	-3
	ne
	brt	__8
__10:
	pushl	-4
	popr
	jmp	__7
__7:
	rsf
	ret

//
// Integer powerOf(Integer, Integer)
//
_powerOf:
	asf	1
	pushl	-4
	popl	0
	jmp	__15
__14:
	pushl	0
	pushl	-4
	mul
	popl	0
	pushl	-3
	pushc	1
	sub
	popl	-3
__15:
	pushl	-3
	pushc	1
	gt
	brt	__14
__16:
	pushl	0
	popr
	jmp	__13
__13:
	rsf
	ret
