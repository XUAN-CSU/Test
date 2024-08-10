CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lpthread
TARGET := program
SRC := main.c
OBJ := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean

