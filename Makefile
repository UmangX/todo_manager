build: 
	g++ -std=c++17 -o out src/main.cpp -lncurses 
	g++ -std=c++17 -o gui src/gui.cpp -lncurses 
gui:
	./gui
run:
	./out . 
