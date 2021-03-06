LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: PolyQuarto

main.o: main.cpp
	mkdir -p obj 
	g++ -c "main.cpp" -o obj/main.o	
	
GameEngine.o: src/GameEngine.cpp
	g++ -c "src/GameEngine.cpp" -o obj/GameEngine.o
	
Pawn.o: src/Pawn.cpp
	g++ -c "src/Pawn.cpp" -o obj/Pawn.o
	
Player.o: src/Player.cpp
	g++ -c "src/Player.cpp" -o obj/Player.o
	
Shape.o: src/Shape.cpp
	g++ -c "src/Shape.cpp" -o obj/Shape.o

Menu.o: src/Menu.cpp
	g++ -c "src/Menu.cpp" -o obj/Menu.o

Button.o: src/Button.cpp
	g++ -c "src/Button.cpp" -o obj/Button.o

Clickable.o: src/Clickable.cpp
	g++ -c "src/Clickable.cpp" -o obj/Clickable.o

ImageButton.o: src/ImageButton.cpp
	g++ -c "src/ImageButton.cpp" -o obj/ImageButton.o

PolyQuarto: main.o GameEngine.o Pawn.o Player.o Shape.o Menu.o Button.o Clickable.o ImageButton.o
	@echo "** Building the game"
	g++ -o PolyQuarto obj/main.o obj/GameEngine.o obj/Pawn.o obj/Player.o obj/Shape.o obj/Menu.o obj/Button.o obj/Clickable.o obj/ImageButton.o $(LIBS)

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
