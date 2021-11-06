CC = g++ -std=c++17 -g -Wall -pedantic
TARGET = lab1

all: $(TARGET) clean

clean:
	rm -f *.o

run: all
	./$(TARGET)

%.o: %.cpp
	$(CC) -c -o $@ $<

$(TARGET): main.o game.o utils.o
	$(CC) -o $@ $^ 