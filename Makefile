all:
	g++ -c main.cpp
	g++ main.cpp -o main sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	echo ./sfml-app
