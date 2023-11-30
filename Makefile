TARGET = queue

CC = g++
CFLAGS = -Wall -g

SRCPREFIX = ./src/

SRC = $(filter-out $(SRCPREFIX)main.cpp, $(wildcard $(SRCPREFIX)*.cpp))

$(TARGET): $(SRCPREFIX)main.cpp
	$(CC) $(CFLAGS) $^ -o $@

deps.mk: $(SRC)
	$(CC) -MM $^ > $@

clean:
	rm -rf $(TARGET)

