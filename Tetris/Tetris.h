#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
constexpr int HEIGHT = 800, WIDTH = 800;

class Tetris
{
public:
	Tetris();
	~Tetris();
	void run();
private:
	void draw();
	void pollEvent();
	void pollEvent2();
	void drawMesh();
private:
	sf::RenderWindow window;
	Board board;
	int frameCounter = 0;
	bool gameState = true;
};