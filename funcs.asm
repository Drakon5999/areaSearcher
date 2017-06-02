GLOBAL _f1
_f1: 
finit
fld qword[esp + 4]
fldl2e
fmulp ;x*lne
fld st0 ; xlne xlne
frndint
fsub st1, st0
fxch
f2xm1
fld1
faddp
fscale
fld1
fxch
fdivp
fld1
fadd st1, st0
fadd st1, st0
faddp
ret

GLOBAL _f2
_f2: 
finit
fld qword[esp + 4]
fld1
fld1 
faddp
fmulp
fld1 
fld1
faddp
fchs
faddp
ret

GLOBAL _f3
_f3: 
finit
fld1
fld qword[esp + 4]
fdivp
ret

GLOBAL _f11
_f11: 
finit
fld qword[esp + 4]
fldl2e
fmulp ;xlne
fld st0 ; xlne xlne
frndint
fsub st1, st0
fxch
f2xm1 
fld1
faddp
fscale
fld1
fxch
fdivp
fchs
ret

GLOBAL _f21
_f21: 
finit
fld1
fld1
faddp
ret

GLOBAL _f31
_f31: 
finit
fld1
fchs
fld qword[esp + 4]
fld st0
fmulp
fdivp
ret