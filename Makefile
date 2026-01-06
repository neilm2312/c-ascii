CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = source/main.c source/vector.c source/matrix.c source/renderer.c source/object.c
OBJ = $(SRC:.c=.o)
TARGET = ascii3d

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

source%.o: source/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY : all clean
