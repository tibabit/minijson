CC=g++
AR=ar

include src/src.mk

SRC:=$(wildcard src/*.c)
OBJ=$(SRC:%.c=%.o)

all: $(OBJ)
	@echo Archiving $^...
	@$(AR) -cvq libminijson.a $^
	@echo Done.

clean:
	@echo Cleaning...
	@rm src/*.o
	@echo Done.
