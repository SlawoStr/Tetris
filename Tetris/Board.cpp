#include "Board.h"
#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <ctime>
#include <vector>

Board::Board()
{
	spawnSquare();
	srand(time(NULL));
	tab = new int[20];
	for (int i = 0; i < 20; i++)
	{
		tab[i] = 0;
	}
}

Board::~Board()
{
	delete[] tab;
}

void Board::render(sf::RenderTarget * target)
{
	sf::RectangleShape rect(sf::Vector2f(40.0f, 40.0f));
	for (auto const & square : currentFigure)
	{
		rect.setPosition(sf::Vector2f(square.xCoordinate * 40, square.yCoordinate * 40));
		rect.setFillColor(square.colour);
		target->draw(rect);
	}
	for (auto const & square : squareList)
	{
		rect.setPosition(sf::Vector2f(square.xCoordinate * 40, square.yCoordinate * 40));
		rect.setFillColor(square.colour);
		target->draw(rect);
	}
}

void Board::update(int direction)
{
	bool spawnNext = false;
	if (direction == 3)
	{
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			if ((*it).yCoordinate >= 19)
			{
				spawnNext = true;
				break;
			}
			for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
			{
				if ((*it).xCoordinate == (*it2).xCoordinate && (*it).yCoordinate + 1 == (*it2).yCoordinate)
				{
					spawnNext = true;
					break;
				}
			}
			if (spawnNext)
				break;
		}
	}
	else if (direction == 2 || direction == 4)
	{
		if (direction == 2)
		{
			for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
			{
				if ((*it).xCoordinate + 1 > 9)
				{
					return;
				}

				for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
				{
					if ((*it).yCoordinate == (*it2).yCoordinate && (*it).xCoordinate + 1 == (*it2).xCoordinate)
					{
						return;
					}
				}
			}
			for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
			{
				(*it).xCoordinate += 1;
			}
			return;
		}
		else if (direction == 4)
		{
			for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
			{
				if ((*it).xCoordinate - 1 < 0)
				{
					return;
				}
				for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
				{
					if ((*it).yCoordinate == (*it2).yCoordinate && (*it).xCoordinate - 1 == (*it2).xCoordinate)
					{
						return;
					}
				}
			}
			for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
			{
				(*it).xCoordinate -= 1;
			}
			return;
			
		}
		
	}
	else if (direction == 1)
	{
		transformFigure();
		return;

	}
	if (spawnNext)
	{
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			squareList.push_front(*it);
			if ((*it).yCoordinate < 0)
			{
				return;
			}
			tab[(*it).yCoordinate] += 1;
		}
		currentFigure.clear();
		spawnSquare();
	}
	else
	{
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			(*it).yCoordinate += 1;
		}
	}
}

bool Board::checkGameState()
{
	bool gameState = true;
	for (auto it = squareList.begin(); it != squareList.end(); it++)
	{
		if ((*it).yCoordinate < 0)
		{
			gameState = false;
			break;
		}
	}
	return gameState;
}

void Board::resetGame()
{
	currentFigure.clear();
	squareList.clear();
	for (int i = 0; i < 20; i++)
		tab[i] = 0;
	spawnSquare();
}

void Board::transformFigure()
{
	if (figureNumber == 1)
		return;
	else if(figureNumber == 0)
	{
		int tab[4][8] = { {1,-2,0,-1,-1,0,-2,1},{2,2,1,1,0,0,-1,-1},{-1,1,0,0,1,-1,2,-2},{-2,-1,-1,0,0,1,1,2} };

		int transformNumber = currentFigure.front().transformNumber;
		int counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			if ((*it).yCoordinate + tab[transformNumber][counter + 1] > 19)
				return;
			else if ((*it).xCoordinate + tab[transformNumber][counter] > 9 || (*it).xCoordinate + tab[transformNumber][counter] < 0)
				return;
			for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
			{
				if ((*it).yCoordinate + tab[transformNumber][counter + 1] == (*it2).yCoordinate && (*it).xCoordinate + tab[transformNumber][counter] == (*it2).xCoordinate)
				{
					return;
				}
			}
			counter += 2;
		}
		
		counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			(*it).xCoordinate += tab[transformNumber][counter];
			(*it).yCoordinate += tab[transformNumber][counter + 1];
			(*it).addTransformation();
			counter += 2;
		}
	}
	else if (figureNumber == 2)
	{
		int tab[4][8] = { {1,-1,0,0,-1,1,1,1},{1,1,0,0,-1,-1,-1,1},{-1,1,0,0,1,-1,-1,-1},{-1,-1,0,0,1,1,1,-1} };

		int transformNumber = currentFigure.front().transformNumber;
		int counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			if ((*it).yCoordinate + tab[transformNumber][counter + 1] > 19)
				return;
			else if ((*it).xCoordinate + tab[transformNumber][counter] > 9 || (*it).xCoordinate + tab[transformNumber][counter] < 0)
				return;
			for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
			{
				if ((*it).yCoordinate + tab[transformNumber][counter + 1] == (*it2).yCoordinate && (*it).xCoordinate + tab[transformNumber][counter] == (*it2).xCoordinate)
				{
					return;
				}
			}
			counter += 2;
		}

		counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			(*it).xCoordinate += tab[transformNumber][counter];
			(*it).yCoordinate += tab[transformNumber][counter + 1];
			(*it).addTransformation();
			counter += 2;
		}
	}
	else if (figureNumber == 3)
	{
		int tab[4][8] = { {2,0,1,-1,0,-2,-1,-1},{-1,2,0,1,1,0,0,-1},{-2,0,-1,1,0,2,1,1},{1,-2,0,-1,-1,0,0,1} };

		int transformNumber = currentFigure.front().transformNumber;
		int counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			if ((*it).yCoordinate + tab[transformNumber][counter + 1] > 19)
				return;
			else if ((*it).xCoordinate + tab[transformNumber][counter] > 9 || (*it).xCoordinate + tab[transformNumber][counter] < 0)
				return;
			for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
			{
				if ((*it).yCoordinate + tab[transformNumber][counter + 1] == (*it2).yCoordinate && (*it).xCoordinate + tab[transformNumber][counter] == (*it2).xCoordinate)
				{
					return;
				}
			}
			counter += 2;
		}

		counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			(*it).xCoordinate += tab[transformNumber][counter];
			(*it).yCoordinate += tab[transformNumber][counter + 1];
			(*it).addTransformation();
			counter += 2;
		}
	}
	else if (figureNumber == 4)
	{
		int tab[4][8] = { {1,2,0,1,-1,0,0,-1},{-2,0,-1,-1,0,-2,1,-1},{0,-2,1,-1,2,0,1,1},{1,0,0,1,-1,2,-2,1} };

		int transformNumber = currentFigure.front().transformNumber;
		int counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			if ((*it).yCoordinate + tab[transformNumber][counter + 1] > 19)
				return;
			else if ((*it).xCoordinate + tab[transformNumber][counter] > 9 || (*it).xCoordinate + tab[transformNumber][counter] < 0)
				return;
			for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
			{
				if ((*it).yCoordinate + tab[transformNumber][counter + 1] == (*it2).yCoordinate && (*it).xCoordinate + tab[transformNumber][counter] == (*it2).xCoordinate)
				{
					return;
				}
			}
			counter += 2;
		}

		counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			(*it).xCoordinate += tab[transformNumber][counter];
			(*it).yCoordinate += tab[transformNumber][counter + 1];
			(*it).addTransformation();
			counter += 2;
		}
	}
	else if (figureNumber == 5)
	{
		int tab[4][8] = { {0,-2,0,0,0,0,-2,0},{0,2,0,0,0,0,2,0},{0,-2,0,0,0,0,-2,0},{0,2,0,0,0,0,2,0} };

		int transformNumber = currentFigure.front().transformNumber;
		int counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			if ((*it).yCoordinate + tab[transformNumber][counter + 1] > 19)
				return;
			else if ((*it).xCoordinate + tab[transformNumber][counter] > 9 || (*it).xCoordinate + tab[transformNumber][counter] < 0)
				return;
			for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
			{
				if ((*it).yCoordinate + tab[transformNumber][counter + 1] == (*it2).yCoordinate && (*it).xCoordinate + tab[transformNumber][counter] == (*it2).xCoordinate)
				{
					return;
				}
			}
			counter += 2;
		}

		counter = 0;
		for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
		{
			(*it).xCoordinate += tab[transformNumber][counter];
			(*it).yCoordinate += tab[transformNumber][counter + 1];
			(*it).addTransformation();
			counter += 2;
		}
	}
	else if (figureNumber == 6)
	{
	int tab[4][8] = { {0,2,0,0,0,0,-2,0},{0,-2,0,0,0,0,2,0},{0,2,0,0,0,0,-2,0},{0,-2,0,0,0,0,2,0} };

	int transformNumber = currentFigure.front().transformNumber;
	int counter = 0;
	for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
	{
		if ((*it).yCoordinate + tab[transformNumber][counter + 1] > 19)
			return;
		else if ((*it).xCoordinate + tab[transformNumber][counter] > 9 || (*it).xCoordinate + tab[transformNumber][counter] < 0)
			return;
		for (auto it2 = squareList.begin(); it2 != squareList.end(); it2++)
		{
			if ((*it).yCoordinate + tab[transformNumber][counter + 1] == (*it2).yCoordinate && (*it).xCoordinate + tab[transformNumber][counter] == (*it2).xCoordinate)
			{
				return;
			}
		}
		counter += 2;
	}

	counter = 0;
	for (auto it = currentFigure.begin(); it != currentFigure.end(); it++)
	{
		(*it).xCoordinate += tab[transformNumber][counter];
		(*it).yCoordinate += tab[transformNumber][counter + 1];
		(*it).addTransformation();
		counter += 2;
	}
	}
}

void Board::spawnSquare()
{

	int newFigureNumber = rand() % 7;
	figureNumber = newFigureNumber;
	int R = rand() % 255;
	int G = rand() % 255;
	int B = rand() % 255;
	Square square(0, 0, sf::Color(R, G, B));
	Square square2(0, 0, sf::Color(R, G, B));
	Square square3(0, 0, sf::Color(R, G, B));
	Square square4(0, 0, sf::Color(R, G, B));

	switch (figureNumber)
	{
	case 0:
		square.setCoordinates(3, -1);
		square2.setCoordinates(4, -1);
		square3.setCoordinates(5, -1);
		square4.setCoordinates(6, -1);
		break;

	case 1:

		square.setCoordinates(4, -2);
		square2.setCoordinates(5, -2);
		square3.setCoordinates(4, -1);
		square4.setCoordinates(5, -1);
		break;

	case 2:

		square.setCoordinates(3, -1);
		square2.setCoordinates(4, -1);
		square3.setCoordinates(5, -1);
		square4.setCoordinates(4, -2);
		break;

	case 3:

		square.setCoordinates(4, -3);
		square2.setCoordinates(4, -2);
		square3.setCoordinates(4, -1);
		square4.setCoordinates(5, -1);
		break;

	case 4:

		square.setCoordinates(5, -3);
		square2.setCoordinates(5, -2);
		square3.setCoordinates(5, -1);
		square4.setCoordinates(4, -1);
		break;

	case 5:

		square.setCoordinates(3, -1);
		square2.setCoordinates(4, -1);
		square3.setCoordinates(4, -2);
		square4.setCoordinates(5, -2);
		break;

	case 6:
		square.setCoordinates(3, -2);
		square2.setCoordinates(4, -2);
		square3.setCoordinates(4, -1);
		square4.setCoordinates(5, -1);
		break;

	}

	currentFigure.push_back(square);
	currentFigure.push_back(square2);
	currentFigure.push_back(square3);
	currentFigure.push_back(square4);
}

void Board::checkRows()
{
	std::list<Square> newSquareList;
	std::vector<int>rowList;
	int rowToDelete = -1;
	int size;
	for (int i = 19; i >= 0; i--)
	{
		if (tab[i] == 10)
		{
			rowList.push_back(i);
		}
	}


	for (int j = 0; j < rowList.size(); j++)
	{
		for (int i = rowList[j]-j; i >= 0; i--)
		{
			if (i != 0)
			{
				tab[i] = tab[i - 1];
			}
			else
			{
				tab[i] = 0;
			}
		}
	}

	if (rowList.size() == 0)
		return;

	for (int i = 0; i < rowList.size(); i++)
	{
		for (auto it = squareList.begin(); it != squareList.end(); it++)
		{
			if ((*it).yCoordinate == rowList[i]-i)
			{
				(*it).colour = sf::Color::Black;
				continue;
			}
			else if ((*it).yCoordinate < rowList[i]-i)
			{
				(*it).yCoordinate += 1;
			}
		}
	}
	for (auto it = squareList.begin(); it != squareList.end(); it++)
	{
		if ((*it).colour != sf::Color::Black)
		{
			Square square((*it).xCoordinate, (*it).yCoordinate, (*it).colour);
			newSquareList.push_back(square);
		}
	}
	squareList.clear();
	squareList = newSquareList;
}
