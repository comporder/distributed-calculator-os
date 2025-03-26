CC = gcc
CFLAGS = -std=c99 -Wno-implicit-function-declaration

SRCS = calculator.c addition.c subtraction.c multiplication.c division.c saver.c
OBJS = $(SRCS:.c=.o)
EXEC = calculator
ADDER = addition
SUBTRACTOR = subtraction
MULTIPLIER = multiplication
DIVIDER = division
SAVER = saver
RESULT = results.txt
PIPE_FILES = adder_pipe subtractor_pipe multiplier_pipe divider_pipe

# Derleme işlemi
all: $(EXEC) $(ADDER) $(SUBTRACTOR) $(MULTIPLIER) $(DIVIDER) $(SAVER)

$(EXEC): calculator.o
	$(CC) $(CFLAGS) -o $@ $^

$(ADDER): addition.o
	$(CC) $(CFLAGS) -o $@ $^

$(SUBTRACTOR): subtraction.o
	$(CC) $(CFLAGS) -o $@ $^

$(MULTIPLIER): multiplication.o
	$(CC) $(CFLAGS) -o $@ $^

$(DIVIDER): division.o
	$(CC) $(CFLAGS) -o $@ $^

$(SAVER): saver.o
	$(CC) $(CFLAGS) -o $@ $^

# Kaynak dosyalarından nesne dosyaları oluşturma
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
run : all
	./calculator

# Temizlik komutu
clean:
	rm -f $(OBJS) $(EXEC) $(ADDER) $(SUBTRACTOR) $(MULTIPLIER) $(DIVIDER) $(SAVER) $(RESULT) 

# Temizleme ve derleme işlemi
fclean: clean 
	rm -f $(PIPE_FILES)

# Yeniden derleme
re: fclean all

.PHONY: all clean fclean re

