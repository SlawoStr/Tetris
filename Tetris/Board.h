#pragma once

#include <list>
#include <SFML/Graphics.hpp>

struct Square
{
	int xCoordinate;
	int yCoordinate;
	int transformNumber;
	sf::Color colour;
	Square(int x, int y, sf::Color colour) { this->xCoordinate = x; this->yCoordinate = y; this->colour = colour; this->transformNumber = 0; }

	void setCoordinates(int x, int y) { xCoordinate = x; yCoordinate = y; }
	void addTransformation() { transformNumber += 1; if (transformNumber > 3)transformNumber = 0; }
};

class Board
{
public:
	Board();
	~Board();
	void render(sf::RenderTarget * target);
	void update(int direction = 3);
	bool checkGameState();
	void resetGame();
	void transformFigure();
	void checkRows();
private:
	std::list<Square>squareList;
	std::list<Square>currentFigure;
	void spawnSquare();
	int *tab;
	int figureNumber;
};
