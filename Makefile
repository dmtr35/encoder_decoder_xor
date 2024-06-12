CC = gcc
CFLAGS = -Wall -g

all: encoder decoder

encoder:
	$(CC) $(CFLAGS) encoder.c -o encoder_xor

decoder:
	$(CC) $(CFLAGS) decoder.c -o decoder_xor

