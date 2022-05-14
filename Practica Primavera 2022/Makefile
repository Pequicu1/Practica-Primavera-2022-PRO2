OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cjt_Jugadores.o Cjt_Torneos.o Jugador.o Torneo.o
	g++ -o program.exe *.o 

Cjt_Jugadores.o: Cjt_Jugadores.cc Cjt_Jugadores.hh Jugador.hh
	g++ -c Cjt_Jugadores.cc $(OPCIONS)

Cjt_Torneos.o: Cjt_Torneos.cc Cjt_Torneos.hh Torneo.hh
	g++ -c Cjt_Torneos.cc $(OPCIONS)

Jugador.o: Jugador.cc Jugador.hh
	g++ -c Jugador.cc $(OPCIONS)

Torneo.o: Torneo.cc Torneo.hh BinTree.hh
	g++ -c Torneo.cc $(OPCIONS) 

program.o: program.cc Cjt_Jugadores.hh Cjt_Torneos.hh
	g++ -c program.cc $(OPCIONS) 

tar: program.cc Cjt_Jugadores.cc Cjt_Jugadores.hh Torneo.cc Torneo.hh Cjt_Torneos.cc Cjt_Torneos.hh Jugador.cc Jugador.hh
	tar -cvf practica.tar program.cc Cjt_Jugadores.cc Cjt_Jugadores.hh Torneo.cc Torneo.hh Cjt_Torneos.cc Cjt_Torneos.hh Jugador.cc Jugador.hh

clean:
	rm -f *.o *.gch *.exe *.tar

practica.tar: Makefile Jugador.hh Jugador.cc Torneo.hh Torneo.cc Cjt_torneos.cc Cjt_torneos.hh Cjt_jugadores.hh Cjt_jugadores.cc BinTree.hh program.cc 
	tar -cvf practica.tar *.cc *.hh Makefile

FC=gfortran -m32
