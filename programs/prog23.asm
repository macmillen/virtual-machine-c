//
// version
//
	.vers	7

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
	call	_readInteger
	pushr
	popl	0
	pushl	0
	pushc	0
	le
	brf	__1
	pushc	0
	call	_writeInteger
	drop	1
	jmp	__2
__1:
	pushl	0
	pushc	1
	eq
	brf	__3
	pushc	1
	call	_writeInteger
	drop	1
	jmp	__4
__3:
	pushc	0
	popl	1
	pushc	1
	popl	2
	pushc	2
	popl	3
	jmp	__6
__5:
	pushl	2
	popl	4
	pushl	1
	pushl	2
	add
	popl	5
	pushl	4
	popl	1
	pushl	5
	popl	2
	pushl	3
	pushc	1
	add
	popl	3
__6:
	pushl	3
	pushl	0
	le
	brt	__5
__7:
	pushl	2
	call	_writeInteger
	drop	1
__4:
__2:
	pushc	10
	call	_writeCharacter
	drop	1
__0:
	rsf
	ret
