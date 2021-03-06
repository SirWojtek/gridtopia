
SRC = $(wildcard src/*.cpp src/**/*.cpp)
LIBS = -lboost_program_options


gridtopia:
		g++ $(SRC) -Wall -std=c++14 -pthread $(LIBS) -O3 -o target/gridtopia

gridtopia-debug:
		g++ $(SRC) -Wall -std=c++14 -pthread $(LIBS) -g -o target/gridtopia-debug

all: gridtopia gridtopia-debug
