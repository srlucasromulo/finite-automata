# ### A simple basic-purpose makefile ###
# 1) Change the executable name.
# 2) Change source path.

# Executable name
EXEC=automata

# Source files
SRC=./src/
C_SRC=$(wildcard $(SRC)*.c)
H_SRC=$(wildcard $(SRC)*.h)

# Objects
OBJ=$(subst src,obj,$(subst .c,.o,$(C_SRC)))

# Compiler
CC=cc

# Compiler flags
CFLAGS=-c -lm -Wall
CC_FLAGS=$(CFLAGS)


# Compiling and linking
#
all: objFolder $(OBJ)

install: all binFolder
	@ echo 'Building binary $(EXEC) using $(CC)...'
	@ $(CC) -o ./bin/$(EXEC) $(OBJ)
	@ echo 'Finished building $@.'

./obj/%.o: ./src/%.c
	@ echo 'Building $@ from $<...'
	@ $(CC) -o $@ $< $(CC_FLAGS)
	@ echo 'ok'

objFolder:
	@ [ -d ./obj ] || mkdir ./obj

binFolder:
	@ [ -d ./bin ] || mkdir ./bin

clean:
	@ echo 'Cleanning up...'
	@ rm -rf ./obj/*.o ./obj
	@ rm -rf ./bin/* ./bin
	@ echo 'ok'

.PHONY: all clean $(EXEC)
