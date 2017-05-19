%include "io.inc"
SECTION .data
e dq 2.71828182845904523536028747135
SECTION .text
CEXTERN pow
GLOBAL _f1
_f1: 
push ebp
mov ebp, esp
sub esp, 12 
push dword[ebp+12]
push dword[ebp+8]
push dword[e]
call pow
add eax, 3
mov esp, ebp
pop ebp
ret

GLOBAL _f2
_f2: 
push ebp
mov ebp, esp
mov eax, dword[ebp + 8]
lea eax, [eax*2 - 2]
mov esp, ebp
pop ebp
ret

GLOBAL _f3
_f3: 



GLOBAL _f11
_f11: 
push ebp
mov ebp, esp

GLOBAL _f21
_f21: 
GLOBAL _f31
_f31: 


GLOBAL CMAIN
CMAIN:
xor eax, eax
ret