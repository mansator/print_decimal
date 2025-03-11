#include <limits.h>
#include <stdio.h>

#include "print_bit.h"

int main() {
  s21_decimal d = {{0, 0, 0, 0}};  
  char *bin_str = "1101101101011011110101101110001011001101000100111";
  
  from_binstr_to_decimal(bin_str, &d);
  set_sign_decimal(&d);
  set_scale_decimal(&d, 5);
  print_bit_decimal(d);
  
  return 0;
}