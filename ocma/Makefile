PARAMS = -g -W -pedantic
all: ocma.js bot_A bot_B
	node ocma bot_A bot_B
bot_B: bot_B.c io localizationB
	gcc bot_B.c io.o localizationB.o -o bot_B $(PARAMS)
bot_A: bot_A.c io localizationA
	gcc bot_A.c io.o localizationA.o -o bot_A $(PARAMS)
io:
	gcc io.c -c $(PARAMS)
localizationA:
	gcc localizationA.c -c $(PARAMS)
localizationB:
	gcc localizationB.c -c $(PARAMS)
bot_test: bot_test.c
	gcc bot_test.c -o bot_test $(PARAMS)
debug:
	node ocma -d bot_A bot_test