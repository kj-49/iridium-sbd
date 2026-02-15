
CC = gcc
CFLAGS = -Wall -Wextra -I../include
# We don't link the actual libiridium-sbd.a here because 
# FFF is providing the implementation of hello_world for now
TARGET = run_tests.exe

all: $(TARGET)

$(TARGET): test_main.c
	$(CC) $(CFLAGS) test_main.c -o $@

test: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
