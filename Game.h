#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Brick
{
public:
	sf::RectangleShape bShape;
	sf::Color bColour;
	sf::Vector2f bSize;
	sf::Vector2f bPos;
};

class Ball
{
public:
	void Bounce(int dir)
	{

		switch (dir)
		{
		case 0:
			ballVelocity.y = -ballVelocity.y;
			break;
		case 1:
			ballVelocity.x = -ballVelocity.x;
			break;
		case 2:
			ballVelocity.y = -ballVelocity.y;
			ballVelocity.x = -ballVelocity.x;
			break;
		}
	};
	sf::CircleShape ballShape;
	sf::Vector2f ballStartPos;
	sf::Vector2f ballVelocity;
	float ballRadius = 10.f;	
};


class Game
{
public:
	bool Start();
	int Update();

private:
	sf::RenderWindow window;
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;
	float windowWidth = 1000;
	float windowHeight = 600;
	int score = 0;
	int lives = 3;
	sf::Font font;
	sf::Text scoreText;
	sf::Text livesText;
	sf::SoundBuffer paddleSoundBuffer;
	sf::SoundBuffer wallSoundBuffer;
	sf::SoundBuffer brickSoundBuffer;
	sf::Sound sound;
};

