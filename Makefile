TARGET = queue

CC = g++
CFLAGS = -Wall -g

SRCPREFIX = ./src/

SRC = $(wildcard $(SRCPREFIX)*.h)

$(TARGET): $(SRCPREFIX)main.cpp $(SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET)

