CC = g++ -std=c++17 -g -Wall -pedantic
GTEST = /usr/lib/libgtest.so
TARGET = lab2

all: $(TARGET) test clean

clean:
	rm -f **/*.o

%.o: %.cpp
	$(CC) -c -o $@ $<

test: test/tests.o
	./$(TARGET)

$(TARGET): test/tests.o
	$(CC) -o $@ $^ $(GTEST)