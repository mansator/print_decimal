NAME 		:= print_decimal
SRC 		:= ./src/$(NAME).c

DEMO 		:= demo
DEMO_EXEC	:= $(DEMO).out
DEMO_SRC 	:= ./demo/$(DEMO).c

all: $(DEMO_EXEC)

$(DEMO_EXEC): $(DEMO_SRC) $(SRC)
	gcc $^ -o $@
	./$(DEMO_EXEC)

clean:
	rm -rf $(DEMO_EXEC)

.PHONY: all clean
