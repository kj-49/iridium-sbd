
LIB_PATH = ..
INC_PATH = ../include

CC = gcc
# -I tells the compiler where the headers (.h) are
CFLAGS = -Wall -Wextra -I$(INC_PATH)
# -L tells the linker where the binary (.a) is
LDFLAGS = -L$(LIB_PATH)
# -l tells the linker the name (automatically looks for libNAME.a)
LDLIBS = -liridium-sbd

TARGET = demo.exe
SRC = main.c
OBJ = $(SRC:.c=.o)

all: build_lib $(TARGET)

build_lib:
	$(MAKE) -C $(LIB_PATH)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	$(RM) *.o $(TARGET)
	$(MAKE) -C $(LIB_PATH) clean
