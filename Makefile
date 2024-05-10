CXX = g++
CXXFLAGS = -D _DEBUG -D _SHOW_STACK_TRACE -ggdb3 -std=c++17 -O0 -Wall -g
LDFLAGS = -lncurses

files = main.cpp 
headers = Snake.hpp View.hpp BotSnake.hpp
objects = $(files:.cpp=.o)

buildDir = build
srcDir = src

.PHONY: all clean prepare
all: prepare main

$(addprefix $(buildDir)/, $(objects)): $(buildDir)/%.o: $(srcDir)/%.cpp
		@echo [CC] $< -o $@
		@$(CXX) $(CXXFLAGS) -Iinclude -c $(realpath $<) -o $@ $(LDFLAGS)

main: $(addprefix $(buildDir)/, $(objects))
		@echo [CC] $^ -o $@
		@$(CXX) $(CXXFLAGS) $^ -o $(addprefix $(buildDir)/, $@) $(LDFLAGS)

clean:
		rm -f build/*.o all
		rm build/cte

prepare:
		@mkdir -p $(buildDir)	