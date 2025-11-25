CC = gcc
CFLAGS = -I. -lm

SRC = src/function.c src/keyboard.c src/main.c

TARGET = pong

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) pontos.txt