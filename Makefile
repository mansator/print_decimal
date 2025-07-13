NAME 		:= print_bit
SRC 		:= $(NAME).c

DEMO 		:= demo
DEMO_SRC 	:= $(DEMO).c

all: $(DEMO)

$(DEMO): $(DEMO_SRC) $(SRC)
	gcc $^ -o $@
	./$(DEMO)

clean:
	rm -rf $(DEMO)
