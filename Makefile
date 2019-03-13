LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: PolyQuarto

main.o: main.cpp
	mkdir obj 
	g++ -c "main.cpp" -o obj/main.o	
	
GameEngine.o: src/GameEngine.cpp
	g++ -c "src/GameEngine.cpp" -o obj/GameEngine.o
	
Pawn.o: src/Pawn.cpp
	g++ -c "src/Pawn.cpp" -o obj/Pawn.o
	
Player.o: src/Player.cpp
	g++ -c "src/Player.cpp" -o obj/Player.o

PolyQuarto: main.o GameEngine.o Pawn.o Player.o
	@echo "** Building the game"
	g++ -o PolyQuarto obj/main.o obj/GameEngine.o obj/Pawn.o obj/Player.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f PolyQuarto
	rm -r obj

install:
	@echo '** Installing...'
	cp PolyQuarto /usr/bin

uninstall:
	@echo '** Uninstalling...'
	rm -f /usr/bin/PolyQuarto
