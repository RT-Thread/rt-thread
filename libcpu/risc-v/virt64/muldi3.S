#define FUNC_TYPE(X)	.type X,@function
#define FUNC_SIZE(X)	.size X,.-X

#define FUNC_BEGIN(X)		\
	.globl X;		\
	FUNC_TYPE (X);		\
X:

#define FUNC_END(X)		\
	FUNC_SIZE(X)


FUNC_BEGIN (__muldi3)
  mv     a2, a0
  li     a0, 0
.L1:
  andi   a3, a1, 1
  beqz   a3, .L2
  add    a0, a0, a2
.L2:
  srli   a1, a1, 1
  slli   a2, a2, 1
  bnez   a1, .L1
  ret
FUNC_END (__muldi3)