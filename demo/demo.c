/* Copyright (c) 2025 Tolstenev Gleb */

/*
 * demo.c | The use of print_decimal.h
 */

#include <stdio.h>

#include "../src/print_decimal.h"

int main() {
  s21_decimal d = {{0, 0, 0, 0}};
  char *bin_str =
      "101001110000111100111011100110001011111010011111000110001111100110";

  binstr_to_decimal(bin_str, &d);
  set_sign_decimal(&d);
  set_scale_decimal(&d, 5);

  printf("This is a s21_decimal initialization view\n");
  print_decimal_init_unsigned(d);
  printf("\n");

  printf("This is a s21_decimal number\n");
  print_decimal(d);
  printf("\n");

  printf("This is a s21_decimal binary view\n");
  print_bit_decimal(d);

  return 0;
}