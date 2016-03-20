CC=gcc

DEPS:=$(wildcard *.h)
%.o:%.c $(DEPS)
	@echo Compilng $< ...
	@$(CC) -c -g -Wall -DDEBUG $< -o $@
