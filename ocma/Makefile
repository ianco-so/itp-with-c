PARAMS = -g -W -pedantic
all: bot_A.c io localization
	gcc bot_A.c io.o localization.o -o bot_A $(PARAMS)
io:
	gcc io.c -c $(PARAMS)
localization:
	gcc localization.c -c $(PARAMS)