
GLOBAL _f1
_f1: 
fld qword[esp + 4]
fldl2e
fmulp
fld st0
frndint
fsub st1, st0
fxch
f2xm1
fld1
faddp
fxch
fld1
fscale
fmulp
fld1
fld1
fadd
faddp
faddp
ret

GLOBAL _f2
_f2: 
fld qword[esp + 4]
fld1
fld1 
faddp
fmulp
fld1 
fld1
faddp
fxch
faddp
ret

GLOBAL _f3
_f3: 
fld1
fld qword[esp + 4]
fdivp
ret

GLOBAL _f11
_f11: 
fld qword[esp + 4]
fldl2e
fmulp
fld st0
frndint
fsub st1, st0
fxch
f2xm1
fld1
faddp
fxch
fld1
fscale
fmulp
fld1
fchs
fmulp
ret

GLOBAL _f21
_f21: 
fld1
fld1
faddp
ret

GLOBAL _f31
_f31: 
fld1
fchs
fld qword[esp + 4]
fld st0
fmulp
fdivp
ret