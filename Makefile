CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = libiridium-sbd.a

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) src*.o libiridium-sbd.a
