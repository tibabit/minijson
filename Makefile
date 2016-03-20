CC=g++
AR=ar

include src/src.mk
OUTPUT=libminijson.a
SRC:=$(wildcard src/*.c)
OBJ=$(SRC:%.c=%.o)

all: $(OBJ)
	@echo Archiving $^...
	@$(AR) -cvq $(OUTPUT) $^
	@echo Done.

clean:
	@echo Cleaning...
	@rm -f src/*.o
	@rm -f $(OUTPUT)
	@echo Done.
