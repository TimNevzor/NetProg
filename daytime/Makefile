CC = g++
CFLAGS = -Wall -g
TARGET = daytime

all: $(TARGET)

$(TARGET): daytime.o
	$(CC) -o $(TARGET) daytime.o

daytime.o: daytime.cpp
	$(CC) $(CFLAGS) -c daytime.cpp

clean:
	rm -f $(TARGET) *.o
