include .env

CFLAGS = -std=c++17 -Iinclude -I. -I$(SFML_PATH)/include

LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
TARGET = a.out
SRC := $(shell find src -name "*.cpp") $(wildcard *.cpp)

$(TARGET): $(SRC)
	g++ $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

.PHONY: test clean
test: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(TARGET)