include Makefile.properties

all: build run

clean:
	rm main

build: main.c
	@$(CC) $(CC_FLAGS) \
	main.c \
	card.c \
	hand.c \
	deck.c \
	-o main

run:
	@./main
