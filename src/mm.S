.globl mm_zero
mm_zero:
    str xzr, [x0], #8
    subs x1, x1, #8
    b.gt mm_zero
    ret
    