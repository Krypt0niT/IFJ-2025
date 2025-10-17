# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Výsledný binár uložený o priečinok vyššie
TARGET = scanner_tests

# Zdrojové súbory
SRC = scanner.c tests/scanner_tests.c
UTILS = $(wildcard ../utilities/*.c)

# Hlavičkové súbory
HEADERS = scanner.h token.h

# Objekty
OBJ = $(SRC:.c=.o) $(UTILS:.c=.o)

all: $(TARGET)

# Kompilácia bináru
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Kompilácia objektov
# pre SRC
scanner.o: scanner.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

tests/scanner_tests.o: tests/scanner_tests.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# pre UTILS
../utilities/%.o: ../utilities/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	make
	./scanner_tests

.PHONY: all clean
