# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Ciele
TARGET = tokenizer_tests

# Zdrojové súbory
SRC = tokenizer.c tests/tokenizer_tests.c

# Hlavičkové súbory
HEADERS = tokenizer.h token.h

# Výsledný objekt
OBJ = $(SRC:.c=.o)

all: $(TARGET)

# Kompilácia hlavného programu
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Objekty zo zdrojov
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Vyčisti objektové súbory a výsledný binár
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
