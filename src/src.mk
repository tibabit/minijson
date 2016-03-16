CC=gcc

%.o:%.c
	@echo Compilng $< ...
	@$(CC) -c -Wall $< -o $@
