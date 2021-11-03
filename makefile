CC = gcc
CFLAGS = -Wall -Werror
OUTPUT = helloworld.out
DEBUG = -g
SOURCES = helloworld.c
WIRING = wiringPi

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT) -l $(WIRING)
debug:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
fresh:
	make clean
	make all




