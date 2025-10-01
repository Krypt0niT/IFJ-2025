# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Ciele
TARGET = scanner_tests

# Zdrojové súbory
SRC = scanner.c tests/scanner_tests.c
UTILS = $(wildcard ../utilities/*.c)

# Hlavičkové súbory
HEADERS = scanner.h token.h

# Výsledný objekt
OBJ = $(SRC:.c=.o) $(UTILS:.c=.o)

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
