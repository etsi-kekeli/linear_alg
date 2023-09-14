# Define the compiler
CC = gcc

# Flags for the compiler
CFLAGS = -c -Wall

# Source files (all .c files in the current directory)
SRC_FILES := $(wildcard *.c)

# Object files (replace .c with .o)
OBJ_FILES := $(SRC_FILES:.c=.o)

# Target executable
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)
