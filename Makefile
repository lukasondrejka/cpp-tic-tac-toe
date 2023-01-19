.PHONY: all clean

all: app

app: main.cpp
	g++ -std=c++14 $^ -o app

clean:
	rm -f *.o app
