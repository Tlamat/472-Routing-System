.model small
PUBLIC _IncreaseConv_ISR

; external variables
extrn _PwdOffTime:word

;code section

.code

_IncreaseConv_ISR proc
	push	bp
   push	dx
   push	ax
   mov	bp,sp
   ;PwdOffTime = PwdOffTime - 30
	sub	_PwdOffTime,30
   ;If PwdOffTime < 0
	cmp	_PwdOffTime,0
   JGE   EXIT
   ;Pwd Off time = 0
	mov	_PwdOffTime, 0
   jmp	EXIT
   ;EOI
   EXIT:
   mov	dx, 0FF22h
	mov	ax, 8000h
   out	dx,ax
   ;restore
   mov 	sp,bp
   pop	ax
   pop	dx
   pop	bp

iret

_IncreaseConv_ISR endp
end