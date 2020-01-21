main: NeedForCerignola.cpp player.o libreria.o lib.o oggetto.o livello.o
	g++ -o NeedForCerignola NeedForCerignola.cpp player.o libreria.o lib.o livello.o oggetto.o -lncurses

player.o: player.cpp player.h
	g++ -c player.cpp

oggetto.o: oggetto.cpp oggetto.h
	g++ -c oggetto.cpp

libreria.o: libreria.cpp libreria.h
	g++ -c libreria.cpp

livello.o: livello.cpp livello.o
	g++ -c livello.cpp