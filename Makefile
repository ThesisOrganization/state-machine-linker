CC = gcc
CFLAGS = -Wall -Wextra
TARGET = driver

PASSING_C =
PASSING_H =


SRCS = driver.c $(PASSING_C)
OBJS = $(SRCS:.c=.o)


DEPS= $(PASSING_H)
.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCS:.c=.o) $(SRCS:.c=.o.rs) $(TARGET)
