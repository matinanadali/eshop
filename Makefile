INCLUDE = -I./include -I../include
SRC = ./src/
CC = g++
TEST_FILE = unit_tests

# Compile options
CFLAGS = -Wall $(INCLUDE)
LDFLAGS = -lm

# Detect all source files and generate object file list
SRCS = $(wildcard $(SRC)*.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

# Output executable name
EXEC = oop24
ARGS = ./files/categories.txt ./files/products.txt ./files/users.txt

# Default target (native build with GCC)
all: $(EXEC)

# Link the object files into the final executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile individual source files into object files and generate dependencies
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Include auto-generated dependency files
-include $(DEPS)

# Generate dependency files
%.d: %.cpp
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

# Run the program with default arguments
run: $(EXEC)
	./$(EXEC) $(ARGS)

# Run the program with valgrind
valgrind_run: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)

# Clean build artifacts
clean:
	rm -f $(SRC)*.o $(SRC)*.d $(EXEC)

run_test: 
	./$(TEST_FILE)