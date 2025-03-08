CC = g++
CFLAGS = -Wall -Wextra -g

TARGET = server_manager

SRCS = $(wildcard *.c)
HDRS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

test:
	bats $(wildcard ./bats/*.sh)

valgrind:
	echo "pwd\nexit" | valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./$(TARGET)
	echo "pwd\nexit" | valgrind --tool=helgrind --error-exitcode=1 ./$(TARGET)

.PHONY: all clean test

