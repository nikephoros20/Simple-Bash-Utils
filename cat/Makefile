TARGET=s21_cat
FLAGS=-Wall -Werror -Wextra
SRCS= s21_cat.c

.PHONY: clean, all, rebuild

all:
	gcc $(SRCS) -o $(TARGET) $(FLAGS)


rebuild:
	make clean
	make all
		
clean:
	rm -rf $(TARGET)