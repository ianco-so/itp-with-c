PARAMS = -g -W -pedantic
all: ocma.js bot_A bot_B
	node ocma bot_A bot_B
debug: ocma.js bot_test bot_A
	node ocma -d -mr 50 -mm 1000 bot_test bot_A 
test: ocma.js bot_test bot_A
	node ocma -mr 100 -mm 10000 bot_test bot_A
bot_B: bot_B.c io localizationB
	gcc bot_B.c io.o localizationB.o -o bot_B $(PARAMS)
bot_A: bot_A.c io localizationA
	gcc bot_A.c io.o localizationA.o -o bot_A $(PARAMS)
bot_test: bot_test.c
	gcc bot_test.c -o bot_test $(PARAMS)
io: io.c
	gcc io.c -c $(PARAMS)
localizationA: localizationA.c
	gcc localizationA.c -c $(PARAMS)
localizationB: localizationB.c
	gcc localizationB.c -c $(PARAMS)
