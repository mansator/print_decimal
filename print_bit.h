#ifndef PRINT_BIT
#define PRINT_BIT

#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

/*----------------------v s21_decimal v----------------------*/
/*-------------------------v float v-------------------------*/
/*--------------------------v int v--------------------------*/
unsigned get_bit_int(unsigned value, unsigned index);
void set_bit_int(unsigned *ptr_int, unsigned index, unsigned bit);
void print_binary_int(unsigned value);
void print_index_32(void);
void print_bit_int(unsigned value);
/*--------------------------^ int ^--------------------------*/
void print_bit_float(float value);
/*-------------------------^ float ^-------------------------*/
unsigned get_bit_decimal(const s21_decimal *ptr_decimal, int index);
unsigned get_sign_decimal(const s21_decimal *ptr_decimal);
unsigned get_scale_decimal(s21_decimal decimal);
void set_bit_decimal(s21_decimal *ptr_decimal, unsigned index, unsigned bit);
void set_sign_decimal(s21_decimal *ptr_decimal);
void set_scale_decimal(s21_decimal *ptr_decimal, unsigned scale);
void clear_sign_decimal(s21_decimal *ptr_decimal);
void print_index_decimal(void);
void print_bit_decimal(s21_decimal decimal);
void print_decimal_init(s21_decimal decimal);
int from_binstr_to_decimal(char *binstr, s21_decimal *dst);
/*----------------------^ s21_decimal ^----------------------*/

#endif  // PRINT_BIT
