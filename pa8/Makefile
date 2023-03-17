#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17 -Wall -g
TARGETS = Order DictionaryTest WordFrequency
all: $(TARGETS)

WordFrequency: WordFrequency.o Dictionary.o
	$(CC) -o WordFrequency WordFrequency.o Dictionary.o

Order: Order.o Dictionary.o
	$(CC) -o Order Order.o Dictionary.o

DictionaryTest: DictionaryTest.o Dictionary.o
	$(CC) -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryClient: DictionaryClient.o Dictionary.o
	$(CC) -o DictionaryClient DictionaryClient.o Dictionary.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(TARGETS) *.o

