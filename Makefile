INCLUDE = -I./include -I../include
SRC = ./src

CC = g++

# Compile options
CFLAGS = -Wall $(INCLUDE)
LDFLAGS = -lm

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Object files for native build
OBJS = $(SRC)/User.o $(SRC)/main.o $(SRC)/Eshop.o $(SRC)/Administrator.o $(SRC)/Customer.o  $(SRC)/Product.o 
EXEC = oop24
ARGS = ./files/categories.txt ./files/products.txt ./files/users.txt

# Default target (native build with GCC)
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

run: $(EXEC)
	./$(EXEC) $(ARGS)

