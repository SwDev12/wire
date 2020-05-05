all: wire 

wire: wire.c
	gcc wire.c -Wall -Wextra -Werror -std=c11 -O0 -o wire

clean:
	rm wire
