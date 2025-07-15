CC			:= gcc
CFLAGS		:= -std=c11 -pedantic -Wall -Wextra -Werror

NAME 		:= print_decimal
SRC 		:= ./src/$(NAME).c
OBJ 		:= ./obj/$(NAME).o

LIB_NAME	:= libprint_decimal.a

DEMO_EXEC	:= demo.out
DEMO_SRC 	:= ./demo/demo.c

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $<

$(OBJ): $(SRC)
	mkdir obj
	$(CC) $(CFLAGS) -c $< -o $@

demo: $(DEMO_SRC) $(LIB_NAME)
	$(CC) $(CFLAGS) $^ -o $(DEMO_EXEC)
	./$(DEMO_EXEC)

clean:
	rm -rf $(DEMO_EXEC) obj/

.PHONY: all demo clean
