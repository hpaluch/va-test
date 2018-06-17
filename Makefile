
CXXFLAGS = -g -Wall
LDFLAGS  = -g

all : va-test

va-test : va-test.o

va-test.o : va-test.cpp

.PHONY: run
run: all
	./va-test

.PHONY: clean
clean:
	rm -f va-test va-test.o


