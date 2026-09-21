CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC_DIR = src
BUILD   = taskflow

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/TaskManager.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(BUILD)

$(BUILD): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BUILD)
	./$(BUILD)

clean:
	rm -f $(OBJS) $(BUILD) tasks.txt

.PHONY: all run clean
