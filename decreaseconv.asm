.model small

PUBLIC _DecreaseConv_ISR
; external variables

extrn _PwdOffTime:word

;code section

.code

_DecreaseConv_ISR proc

	push	bp
   push	dx
   push	ax
   mov	bp,sp

   ;PwdOffTime = PwdOffTime + 30
	add	_PwdOffTime,30
   ;If PwdOffTime >=  200
	cmp	_PwdOffTime,200
   JLE   EXIT
   ;Pwd Off time = 0h;
	mov	_PwdOffTime,200
   jmp 	EXIT
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

_DecreaseConv_ISR endp
end