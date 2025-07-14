#include "print_bit.h"

/*-------------------------v float v-------------------------*/
/*--------------------------v int v--------------------------*/

/**
 * Проверяет бит по индексу index в переменной value типа int
 * @param value
 * @param index
 * @return 1 - бит установлен; 0 - бит не установлен
 */
unsigned get_bit_int(unsigned value, unsigned index) {
  unsigned mask = 1 << index;
  return (value & mask) != 0;
}

/**
 * Печатает содержимое переменной value в бинарном виде с пробелами
 * @param value
 */
void print_binary_int(unsigned value) {
  for (int i = 31; i >= 0; --i) {
    if (get_bit_int(value, i)) {
      printf("%3d", 1);
    } else {
      printf("%3d", 0);
    }
  }
}

/**
 * Печатает индексы битов для 32-битных переменных
 */
void print_index_32(void) {
  for (int i = 31; i >= 0; --i) {
    printf("|%2d", i);
  }
}

/**
 * Печатает биты, содержащиеся в int в подробном виде
 * @param value
 */
void print_bit_int(unsigned value) {
  print_index_32();
  printf("  <- index\n");
  print_binary_int(value);
  printf("  <- bit\n");
  printf("%96u", value);
  printf("  <- value\n");
}

/*--------------------------^ int ^--------------------------*/

/**
 * Печатает биты, содержащиеся в float в подробном виде
 * @param num
 */
void print_bit_float(float value) {
  unsigned int fbits;
  fbits = *((unsigned int *)&value);

  print_index_32();
  printf("  <- index\n");
  print_binary_int(fbits);
  printf("  <- bit\n");
  printf(
      "sign \\_________exp________/  "
      "\\_____________________________mantissa____________________________/\n");
  printf("%96f", value);
  printf("  <- value\n");
}

/*-------------------------^ float ^-------------------------*/

/*----------------------v s21_decimal v----------------------*/

/**
 * Печатает индексы битов для 128-битных переменных.
 * Используется для четырёх последовательных вызовов.
 */
void print_index_decimal(void) {
  static int index = 127;
  if (index == -1) {
    index = 127;
  }
  int index_support = 0;

  for (; index >= 0; --index) {
    index_support = index;
    if (index % 32) {
      if (index > 99) {
        index_support -= 100;
        if (110 > index) {
          printf("|0%d", index_support);
        } else {
          printf("|%2d", index_support);
        }
      } else {
        printf("|%2d", index_support);
      }
    } else {
      printf("|%2d", index);
      index--;
      break;
    }
  }
}

/**
 * Проверяет бит в s21_decimal
 * @return 1 есть бит 0 нет бита
 */
unsigned get_bit_decimal(const s21_decimal *ptr_decimal, int index) {
  unsigned mask = 0;
  unsigned i = index / 32;      // индекс нужного int'а в decimal
  unsigned shift = index % 32;  // индекс бита в int'е (величина сдвига)

  mask = 1u << shift;
  return (ptr_decimal->bits[i] & mask) != 0;
}

/**
 * Устанавливает 0 или 1 по индексу в int
 * @param ptr_int указатель на int
 * @param index индекс по которому нужно установить бит
 * @param bit значение бита, которое нужно установить (0 или 1)
 */
void set_bit_int(unsigned *ptr_int, unsigned index, unsigned bit) {
  unsigned mask = 0;
  if (bit == 1) {
    mask = 1u << index;
    *ptr_int |= mask;
  } else if (bit == 0) {
    mask = ~(1u << index);
    *ptr_int &= mask;
  }
}

/**
 * Устанавливает 0 или 1 по индексу в s21_decimal
 * @param ptr_decimal указатель на s21_decimal
 * @param index индекс по которому нужно установить бит
 * @param bit значение бита, которое нужно установить (0 или 1)
 */
void set_bit_decimal(s21_decimal *ptr_decimal, unsigned index, unsigned bit) {
  unsigned mask = 0;
  unsigned i = index / 32;      // индекс нужного int'а в decimal
  unsigned shift = index % 32;  // индекс бита в int'е (величина сдвига)

  set_bit_int(&(ptr_decimal->bits[i]), shift, bit);
}

/**
 * Устанавливает 0 в бит знака переменной value типа s21_decimal
 * @param ptr_decimal указатель на s21_decimal
 */
void clear_sign_decimal(s21_decimal *ptr_decimal) {
  set_bit_decimal(ptr_decimal, 127, 0);
}

/**
 * Узнает знак s21_decimal
 * @param ptr_decimal указатель на s21_decimal
 * @return 1, если число отрицательное
 */
unsigned get_sign_decimal(const s21_decimal *ptr_decimal) {
  return get_bit_int(ptr_decimal->bits[3], 31);
}

/**
 * Устанавливает знак в s21_decimal
 * @param ptr_decimal указатель на s21_decimal
 */
void set_sign_decimal(s21_decimal *ptr_decimal) {
  set_bit_int(&(ptr_decimal->bits[3]), 31, 1);
}

/**
 * Получает степень s21_decimal без валидации
 * @return int степень числа
 */
unsigned get_scale_decimal(s21_decimal decimal) {
  clear_sign_decimal(&decimal);
  return decimal.bits[3] >>= 16;
}

/**
 * Устанавливает показатель степени. Диапазон от 0 до 28
 */
void set_scale_decimal(s21_decimal *ptr_decimal, unsigned scale) {
  unsigned sign = get_sign_decimal(ptr_decimal);

  ptr_decimal->bits[3] = scale;
  ptr_decimal->bits[3] <<= 16;

  if (sign == 1) {
    set_sign_decimal(ptr_decimal);
  }
}

/**
 * Печатает биты, содержащиеся в s21_decimal в подробном виде
 * @param number
 */
void print_bit_decimal(s21_decimal decimal) {
  char char_sign = (get_sign_decimal(&decimal)) ? '-' : '+';
  char *str_sign = (char_sign == '+') ? "positive" : "negative";
  unsigned int scale = get_scale_decimal(decimal);
  for (int i = 3; i >= 0; --i) {
    print_index_decimal();
    printf("  <- index\n");
    print_binary_int(decimal.bits[i]);
    printf("  <- bit\n");
    if (i == 3) {
      printf(
          " '%c' <- sign (%s) %8s |<- scale:%2d ->|"
          "%24s bits[%d] = [%10u]  <- int value\n",
          char_sign, str_sign, "", scale, "", i, decimal.bits[i]);      
    } else {
      printf("%73s bits[%d] = [%10u]  <- int value\n", "", i, decimal.bits[i]);
    }
  }
}

/**
 * Переводит строку, содержащее число в бинароном виде, в s21_decimal
 * @param binstr
 * @param dst
 * @return 1 - некорректная строка; 0 - ОК
 */
int from_binstr_to_decimal(char *binstr, s21_decimal *dst) {
  int error = 0;
  int n = strlen(binstr) - 1, c = n + 1, i = 0;

  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;

  if (n < 128) {
    for (; n >= 0; n--, i++) {
      if (binstr[n] == '0') {
        set_bit_decimal(dst, i, 0);
      } else if (binstr[n] == '1') {
        set_bit_decimal(dst, i, 1);
      } else {
        error = 1;
      }
    }
    for (; c < 128; ++c) {
      set_bit_decimal(dst, c, 0);
    }
  } else {
    error = 1;
  }
  return error;
}

/**
 * Печатает строку в виде инициализации структуры для языка Си
 * в беззнаковом формате чисел
 * @param decimal
 * @return 1 - некорректная строка; 0 - ОК
 */
void print_decimal_init_unsigned(s21_decimal decimal) {
  printf("{{%u, %u, %u, %u}}\n",
    decimal.bits[0],
    decimal.bits[1],
    decimal.bits[2],
    decimal.bits[3]);
}

/**
 * Печатает строку в виде инициализации структуры для языка Си
 * в знаковом формате чисел
 * @param decimal
 * @return 1 - некорректная строка; 0 - ОК
 */
void print_decimal_init_signed(s21_decimal decimal) {
  printf("{{%d, %d, %d, %d}}\n",
    decimal.bits[0],
    decimal.bits[1],
    decimal.bits[2],
    decimal.bits[3]);
}

/**
 * Прибавляет единицу к decimal_digits
 * @param dd - указатель на объект decimal_digits
 */
void add_1_to_digits(decimal_digits *dd) {
  int carry = 1;
  for (int i = 0; i < dd->length && carry > 0; ++i) {
    int temp = dd->digits[i] + carry;
    dd->digits[i] = temp % 10;
    carry = temp / 10;
  }
  if (carry > 0) {
    dd->digits[dd->length++] = carry;
  }
}

/**
 * Умножает decimal_digits на 2
 * @param dd - указатель на объект decimal_digits
 */
void multiply_digits_by_2(decimal_digits *dd) {
  int carry = 0;
  for (int i = 0; i < dd->length; ++i) {
    int temp = dd->digits[i] * 2 + carry;
    dd->digits[i] = temp % 10;
    carry = temp / 10;
  }
  if (carry > 0) {
    dd->digits[dd->length++] = carry;
  }
}
 
/**
 * Присваивает ноль в decimal_digits
 * @param dd - указатель на объект decimal_digits
 */
void clear_decimal_digits(decimal_digits *dd) {
  memset(dd->digits, 0, sizeof(dd->digits));
  dd->length = 1;
}

/**
 * Печатает s21_decimal в десятичном виде
 * @param decimal
 */
void print_decimal(s21_decimal decimal) {
  decimal_digits dd;
  clear_decimal_digits(&dd);

  // Перевод из двоичного вида s21_decimal в массив десятичных цифр
  for (int i = 95; i >= 0; i--) {
    multiply_digits_by_2(&dd);
    if (get_bit_decimal(&decimal, i)) {
      add_1_to_digits(&dd);
    }
  }

  int scale = get_scale_decimal(decimal);
  int leading_zeros = scale - dd.length + 1;
  bool need_dot = scale > 0 ? true : false;

  if (get_sign_decimal(&decimal)) {
    printf("%c", '-');
  }
  while (leading_zeros > 0) {
    printf("%c", '0');
    if (need_dot) {
      printf("%c", '.');
      need_dot = false;
    }
    leading_zeros--;
  }
  for (int i = dd.length - 1; i >= 0; --i) {
    if (i + 1 == scale && need_dot) {
      printf("%c", '.');
    }
    printf("%d", dd.digits[i]);
  }
  printf("\n");
}

/*----------------------^ s21_decimal ^----------------------*/
