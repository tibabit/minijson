CC=gcc

DEPS:=$(wildcard *.h)
%.o:%.c $(DEPS)
	@echo Compilng $< ...
	@$(CC) -c -Wall $< -o $@
