/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

#include "bits.h"

// P1
int signMask(void) {
  return 1 << 31;
}

// P2
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}

// P3
int negativePart(int x){
  int sign = x >> 31;
  return sign & (~x + 1);
}

// P4
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int byte = (x >> srcShift) & 0xFF;
  int mask = ~(0xFF << dstShift);
  return (x & mask) | (byte << dstShift);
}

// P5
int logicalShift(int x, int n) {
  int shifted = x >> n;
  int mask = ~(((1 << 31) >> n) << 1);
  return shifted & mask;
}

// P6
int swapNibblePairs(int x) {
  /* 用 0x0F 拼出 0x0F0F0F0F 和 0xF0F0F0F0 */
  int lowMask = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  int highMask = lowMask << 4;
  int low = x & lowMask;
  int high = x & highMask;
  return (low << 4) | ((high >> 4) & lowMask);
}

// P7
int secondLowestZeroBit(int x) {
  int y = x | (x + 1);
  return ~y & (y + 1);
}

// P8
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return ~x & 1;
}

// P9
int rotateRightBits(int x, int n) {
  int s = n & 31;
  int right = (x >> s) & ~(((1 << 31) >> s) << 1);
  int left = x << (32 + (~s + 1));
  return right | left;
}

// P10
int roundEvenPow2(int x, int n) {
  int mask = (1 << n) + ~0;          // (1<<n)-1
  int y = x >> n;
  int r = x & mask;
  int half = 1 << (n + ~0);          // 1<<(n-1)
  int odd = y & 1;
  int diff = half + ~r + 1;          // half - r
  int r_gt_half = (diff >> 31) & 1;  // r > half ? 1 : 0
  int eq = !(r ^ half);
  int round_up = r_gt_half | (eq & odd);
  return (y + round_up) << n;
}

// P11
int midpointTowardFirst(int x, int y) {
  int t = x ^ y;
  int avg = (x & y) + (t >> 1);
  int odd = t & 1;
  int sx = x >> 31;
  int sy = y >> 31;
  int same_sign = ~(sx ^ sy);
  int diff = x + ~y + 1;
  int x_gt_y = (same_sign & (~diff >> 31)) | (~same_sign & ~sx);
  return avg + (odd & (x_gt_y & 1));
}

// P12
int isBetweenEitherOrder(int x, int a, int b) {
  int mask = ((~a & b) | (~(a ^ b) & ~(a + ~b + 1))) >> 31; // a >= b ? -1 : 0
  int min = (a & ~mask) | (b & mask);
  int max = (a & mask) | (b & ~mask);
  int ge_min = ((~x & min) | (~(x ^ min) & ~(x + ~min + 1))) >> 31 & 1; // x >= min
  int le_max = ((~max & x) | (~(max ^ x) & ~(max + ~x + 1))) >> 31 & 1; // max >= x
  return ge_min & le_max;
}

// P13
int mul5Sat(int x) {
  int result = (x << 2) + x;
  int sign_x = x >> 31;

  // 正数阈值 0x1999999A
  int th_pos = 0x19;
  th_pos = (th_pos << 8) | 0x99;
  th_pos = (th_pos << 8) | 0x99;
  th_pos = (th_pos << 8) | 0x9A;

  // 负数阈值 0xE6666667 (即 -0x19999999)
  int th_neg = 0xE6;
  th_neg = (th_neg << 8) | 0x66;
  th_neg = (th_neg << 8) | 0x66;
  th_neg = (th_neg << 8) | 0x67;

  int pos_over = (~sign_x) & (~((x + ~th_pos + 1) >> 31) & 1);
  int neg_over = sign_x & ((x + ~th_neg + 1) >> 31 & 1);

  int mask_pos = ~pos_over + 1;
  int mask_neg = ~neg_over + 1;
  int int_min = 1 << 31;
  int int_max = ~int_min;
  int mask_all = mask_pos | mask_neg;

  return (result & ~mask_all) | (int_max & mask_pos) | (int_min & mask_neg);
}

// P14
int classifyAdd3(int x, int y, int z) {
  int sum1 = x + y;
  int sum2 = sum1 + z;
  int C1 = ((x & y) | ((x | y) & ~sum1)) >> 31 & 1;
  int C2 = ((sum1 & z) | ((sum1 | z) & ~sum2)) >> 31 & 1;
  int C = C1 + C2;
  int neg_count = (x >> 31) + (y >> 31) + (z >> 31);
  int D = C + neg_count;

  int D_neg = D >> 31;
  int D_nonzero = ((D | (~D + 1)) >> 31);
  int D_zero = ~D_nonzero;
  int D_pos = ~D_neg & D_nonzero;

  int Dp1 = D + 1;
  int Dp1_nonzero = ((Dp1 | (~Dp1 + 1)) >> 31);
  int D_neg1 = ~Dp1_nonzero;

  int D_less_neg1 = D_neg & ~D_neg1;

  int sum2_msb = (sum2 >> 31) & 1;
  int sum2_mask = ~sum2_msb + 1;

  int pos_over = D_pos | (D_zero & sum2_mask);
  int neg_over = D_less_neg1 | (D_neg1 & ~sum2_mask);

  return (pos_over & 1) | (neg_over & ~0);
}

// P15
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if (exp == 0xFF) return uf;

  if (exp == 0) {
    if (frac == 0) return uf;
    unsigned sig3 = frac * 3;
    unsigned q = sig3 >> 1;
    unsigned r = sig3 & 1;
    if (r && (q & 1)) q++;
    if (q >= (1 << 23)) {
      exp = 1;
      frac = q - (1 << 23);
    } else {
      exp = 0;
      frac = q;
    }
    return sign | (exp << 23) | frac;
  }

  unsigned M = (1 << 23) | frac;
  unsigned M3 = M * 3;

  int k;
  if (M3 & (1 << 25)) {
    k = 25;
  } else {
    k = 24;
  }

  unsigned new_exp = exp + k - 24;
  if (new_exp >= 255) {
    return sign | (0xFF << 23);
  }

  unsigned mant = M3 >> (k - 23);
  unsigned round_bit = (M3 >> (k - 24)) & 1;
  unsigned sticky = M3 & ((1 << (k - 24)) - 1);

  if (round_bit && (sticky || (mant & 1))) {
    mant++;
  }
  if (mant >= (1 << 24)) {
    mant >>= 1;
    new_exp++;
  }

  unsigned new_frac = mant & 0x7FFFFF;
  return sign | (new_exp << 23) | new_frac;
}

// P16
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if (exp == 0xFF) return uf;
  if (exp == 0) return sign; // 0 或 -0
  if (exp >= 150) return uf; // 已经大于等于 2^23，是整数

  unsigned M = (1 << 23) | frac;
  int sh = 150 - exp;
  unsigned q;
  if (sh > 24) {
    q = 0;
  } else {
    q = M >> sh;
    unsigned r = M & ((1u << sh) - 1);
    unsigned half = 1u << (sh - 1);
    if (r > half || (r == half && (q & 1))) q++;
  }

  if (q == 0) return sign;

  int k = 31;
  while (!(q & (1u << k))) k--;

  unsigned new_exp = 127 + k;
  unsigned new_frac = (q << (23 - k)) & 0x7FFFFF;
  return sign | (new_exp << 23) | new_frac;
}

// P17
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned absX;
  unsigned exp;
  unsigned frac;

  if (x == 0) return 0;
  if (x < 0) {
    sign = 0x80000000;
    absX = -x;
  } else {
    absX = x;
  }

  int msb = 31;
  while (!(absX & (1u << msb))) msb--;

  exp = msb + 127;

  if (msb <= 23) {
    frac = (absX << (23 - msb)) & 0x7FFFFF;
  } else {
    int shift = msb - 23;
    frac = (absX >> shift) & 0x7FFFFF;
    unsigned roundPart = absX & ((1u << shift) - 1);
    unsigned half = 1u << (shift - 1);
    if (roundPart > half || (roundPart == half && (frac & 1))) {
      frac++;
      if (frac == 0x800000) {
        frac = 0;
        exp++;
      }
    }
  }

  if (exp >= 0xFF) return sign | 0x7F800000;
  return sign | (exp << 23) | frac;
}

// P18
int bitCount(int x) {
  int msb = (x >> 31) & 1;
  x = x & ~(1 << 31); // 清除最高位，变为非负数

  int mask1 = 0x55 | (0x55 << 8) | (0x55 << 16) | (0x55 << 24);
  int mask2 = 0x33 | (0x33 << 8) | (0x33 << 16) | (0x33 << 24);
  int mask4 = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);

  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x & mask4) + ((x >> 4) & mask4);

  x = (x & 0x0F) + ((x >> 8) & 0x0F) + ((x >> 16) & 0x0F) + ((x >> 24) & 0x0F);
  return x + msb;
}

// P19
int bitReverse(int x) {
  int msb = (x >> 31) & 1;
  x = x & ~(1 << 31);               // 清除最高位

  int m4 = 0x0F | (0x0F << 8);
  m4 = m4 | (m4 << 16);             // 0x0F0F0F0F
  int m2 = m4 ^ (m4 << 2);          // 0x33333333
  int m1 = m2 ^ (m2 << 1);          // 0x55555555
  int m8 = 0xFF | (0xFF << 16);     // 0x00FF00FF

  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);

  int mask16 = (1 << 16) + ~0;      // 0x0000FFFF
  x = ((x >> 16) & mask16) | (x << 16);

  return (x & ~1) | msb;
}