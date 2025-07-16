/* Copyright (c) 2025 Tolstenev Gleb */

/*
 * print_decimal.h | The set of functions to represent the s21_decimal numbers
 */

#ifndef PRINT_DECIMAL_H
#define PRINT_DECIMAL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Тип s21_decimal для хранения чисел с плавающей точкой
 * и точностью до 28 знаков
 */
typedef struct {
  unsigned int bits[4];
} s21_decimal;

/**
 * Хранит десятичное представление мантиссы числа s21_decimal
 */
typedef struct {
  int digits[30];  // цифры числа (в обратном порядке: [0] - младший разряд)
  int length;
} decimal_digits;

unsigned get_bit_int(unsigned value, unsigned index);
void set_bit_int(unsigned *ptr_int, unsigned index, unsigned bit);
void print_binary_int(unsigned value);
void print_index_32(void);
void print_bit_int(unsigned value);

void print_bit_float(float value);

unsigned get_bit_decimal(s21_decimal value, int index);
unsigned get_sign_decimal(s21_decimal value);
unsigned get_scale_decimal(s21_decimal decimal);
void set_bit_decimal(s21_decimal *ptr_decimal, unsigned index, unsigned bit);
void set_sign_decimal(s21_decimal *ptr_decimal);
void set_scale_decimal(s21_decimal *ptr_decimal, unsigned scale);
void clear_sign_decimal(s21_decimal *ptr_decimal);
void print_index_128(void);
void print_bit_decimal(s21_decimal decimal);
void print_decimal_init_signed(s21_decimal decimal);
void print_decimal_init_unsigned(s21_decimal decimal);
int binstr_to_decimal(char *binstr, s21_decimal *dst);

void add_1_to_digits(decimal_digits *ptr_digits);
void multiply_digits_by_2(decimal_digits *ptr_digits);
void clear_decimal_digits(decimal_digits *ptr_digits);
void print_decimal(s21_decimal decimal);

#endif  // PRINT_DECIMAL_H
