#include <stdio.h>

#include "demo.h"
#include "print_bit.h"

int main() {
  // demo_print_bit_decimal();
  // demo_print_bit_float();
  demo_print_bit_int();
  // demo_print_decimal();
  return 0;
}

void demo_print_decimal() {
  s21_decimal d = {{5, 0, 0, 0}};
  set_sign_decimal(&d);
  set_scale_decimal(&d, 2);
  print_decimal(d);
}

void demo_print_bit_int() {
  int i = 5;
  print_bit_int(i);
}

void demo_print_bit_float() {
  float f = 7.42;
  print_bit_float(f);
}

void demo_print_bit_decimal() {
  s21_decimal d = {{0, 0, 0, 0}};
  char *bin_str = "1101101101011011110101101110001011001101000100111";

  from_binstr_to_decimal(bin_str, &d);
  set_sign_decimal(&d);
  set_scale_decimal(&d, 5);
  print_bit_decimal(d);
  print_decimal_init_unsigned(d);
}