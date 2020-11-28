CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = driver

PASSING_C =
PASSING_H =

#PASSING_C= tests_topology/state_machines/actuator-state-machine/src-gen/Statechart.c tests_topology/state_machines/prova_rapida/src-gen/Nomemio.c linking.c

#PASSING_H= tests_topology/state_machines/actuator-state-machine/src-gen/Statechart.h tests_topology/state_machines/actuator-state-machine/src/sc_types.h tests_topology/state_machines/prova_rapida/src-gen/Nomemio.h tests_topology/state_machines/prova_rapida/src/sc_types.h linking.h

SRCS = driver.c simulator_api.c $(PASSING_C)
OBJS = $(SRCS:.c=.o)

DEPS= simulator_api.h $(PASSING_H)

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCS:.c=.o) $(SRCS:.c=.o.rs) $(TARGET)
