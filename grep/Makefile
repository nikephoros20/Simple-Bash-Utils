TARGET=s21_grep
FLAGS=-Wall -Werror -Wextra
SRCS= s21_grep.c

.PHONY: clean, all, rebuild

all:
	gcc $(SRCS) -o $(TARGET) $(FLAGS)


rebuild:
	make clean
	make all
		
clean:
	rm -rf $(TARGET)

