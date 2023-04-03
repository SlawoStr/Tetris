#include "Tetris.h"
#include <iostream>
#include<windows.h>

Tetris::Tetris() : window(sf::VideoMode(HEIGHT, WIDTH), "TetrisGame", sf::Style::Close | sf::Style::Titlebar), board()
{
	window.setFramerateLimit(60);
}

Tetris::~Tetris()
{
}

void Tetris::run()
{
	while (window.isOpen())
	{
		if (gameState)
		{
			window.clear(sf::Color::White);
			draw();
			window.display();
			pollEvent();
			frameCounter += 1;
			frameCounter %= 60;
		}
		else
		{
			pollEvent2();
		}
	}
}

void Tetris::draw()
{
	sf::RectangleShape rect(sf::Vector2f(400.0f, 800.0f));
	rect.setPosition(sf::Vector2f(400.0f, 0.0f));
	rect.setFillColor(sf::Color::Black);
	window.draw(rect);
	board.render(&window);
	drawMesh();
}

void Tetris::pollEvent()
{
	sf::Event e;
	sf::Vector2f mousePos;
	bool buttonPressed = false;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Up)
			{
				board.update(1);
			}
			else if (e.key.code == sf::Keyboard::Right)
			{
				board.update(2);

			}
			else if (e.key.code == sf::Keyboard::Down)
			{
				board.update();
			}
			else if (e.key.code == sf::Keyboard::Left)
			{
				board.update(4);
			}
		}
	}
	if (frameCounter % 60 == 0)
	{
		board.update();
	}
	board.checkRows();
	gameState = board.checkGameState();
}

void Tetris::pollEvent2()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::KeyPressed)
		{
			board.resetGame();
			gameState = true;
		}
	}
}

void Tetris::drawMesh()
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0,0)),
		sf::Vertex(sf::Vector2f(0,0))
	};
	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
	
	for (int i = 0; i < (HEIGHT/40)+1; i++)
	{
		line[0].position = sf::Vector2f(0, i * 40);
		line[1].position = sf::Vector2f(HEIGHT-400, i * 40);
		window.draw(line, 2, sf::Lines);
	}
	for (int i = 0; i < (WIDTH / 40)-9 ; i++)
	{
		line[0].position = sf::Vector2f(i * 40, 0);
		line[1].position = sf::Vector2f(i * 40, WIDTH);
		window.draw(line, 2, sf::Lines);
	}
}
