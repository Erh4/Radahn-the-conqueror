CC = gcc
OPTIONS = -Wall -ansi -pedantic
EXECUTABLE = programme

SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)
all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJETS)
	$(CC) $(OPTIONS) $(OBJETS) -o $(EXECUTABLE)
%.o: %.c 
	$(CC) $(OPTIONS) -MMD -c $<
clean:
	rm -vf *.o *.d
-include *.d

