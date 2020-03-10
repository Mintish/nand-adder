#include<stdio.h>
#include<stdlib.h>

/*
 * Add without adding (or "nothing but nand, and oh yeah a shift or two").
 */

// ideally we'd have a nand operator...
int nand(int k, int l) {
  return ~(k & l);
}

int or(int k, int l) {
  int k_not = nand(k, k);
  int l_not = nand(l, l);
  int k_or_l = nand(k_not, l_not);
  return k_or_l;
}

int and(int k, int l) {
  int not_k_and_l = nand(k, l);
  int k_and_l = nand(not_k_and_l, not_k_and_l);
  return k_and_l;
}

// classically: (~l & k) | (~k & l)
int xor(int k, int l) {
  int l_not = nand(l, l);
  int k_not = nand(k, k);
  int k_xor_l = or(and(l_not, k), and(k_not, l));
  return k_xor_l;
}

int add(int a, int b) {
  int unshifted_carry = and(a, b);
  int carry = unshifted_carry << 1;
  int half_add = xor(a, b);

  while (and(carry, half_add) > 0) {
    int carry_new = and(half_add, carry);
    int half_add_new = xor(half_add, carry);
    half_add = half_add_new;
    carry = carry_new << 1;
  }

  int add = or(half_add, carry);
}

int main(int argc, char** argv) {
  const int a = atoi(argv[1]);
  const int b = atoi(argv[2]);

  int result = add(a, b);

  printf("%d\n", result);
}
