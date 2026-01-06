CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = src/main.c src/vector.c src/matrix. c src/renderer.c src/object.c
OBJ = $(SRC:.c=.o)
TARGET = ascii3d

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY : all clean
