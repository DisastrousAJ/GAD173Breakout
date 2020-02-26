// Brief1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Game.h"
#include <conio.h>
int windowWidth = 1000;
int windowHeight = 600;
int speed = 6;
using namespace std;


int main()
{
    Game myGame;
    if (!myGame.Start())
    {
        return EXIT_FAILURE;
    }
    return myGame.Update();

    return 0;
}

Brick brick;
vector<Brick> Bricks(31, Brick(brick));



bool Game::Start()
{
    paddleSoundBuffer.loadFromFile("SFX/paddlebounce.flac");
    wallSoundBuffer.loadFromFile("SFX/wallbounce.wav");
    brickSoundBuffer.loadFromFile("SFX/brickbounce.wav");

    font.loadFromFile("arial.ttf");
    scoreText.setFont(font);
    livesText.setFont(font);
    scoreText.setPosition(0, windowHeight - 50);
    livesText.setPosition(windowWidth - 100, windowHeight - 50);
    scoreText.setCharacterSize(24);
    livesText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    livesText.setFillColor(sf::Color::White);

    sf::VideoMode vMode(windowWidth, windowHeight);
    window.create(vMode, "Breakout!");
    window.setFramerateLimit(60);
    
    srand(time(NULL));
    for (int i = 0; i < 31; i++)
    {
        Bricks[i].bShape.setSize(sf::Vector2f(100, 50));
        if (i <= 10)
        {
            Bricks[i].bShape.setFillColor(sf::Color(rand()% 281 + 50, 73, 255, 255));
            Bricks[i].bShape.setPosition(100 * i, 0);
        }
        else if (i > 20)
        {
            Bricks[i].bShape.setFillColor(sf::Color(rand() % 255 + 50, 255, 99, 255));
            Bricks[i].bShape.setPosition(100 * (i-21), 100);
        }
        else if (i > 10)
        {
            Bricks[i].bShape.setFillColor(sf::Color(rand() % 299 + 50, 34, 223, 255));
            Bricks[i].bShape.setPosition(100 * (i-11), 50);
        }
    }

    top.setSize(sf::Vector2f(windowWidth, 1));
    top.setPosition(0, 0);
    top.setFillColor(sf::Color::Black);
    bottom.setSize(sf::Vector2f(windowWidth, 1));
    bottom.setPosition(sf::Vector2f(0, windowHeight - 1));
    bottom.setFillColor(sf::Color::Black);
    left.setSize(sf::Vector2f(1, windowHeight));
    left.setPosition(sf::Vector2f(0, 0));
    left.setFillColor(sf::Color::Black);
    right.setSize(sf::Vector2f(1, windowHeight));
    right.setPosition(sf::Vector2f(windowWidth - 1, 0));
    right.setFillColor(sf::Color::Black);

    return true;
}

int Game::Update() 
{
    Paddle paddle;
    paddle.pShape.setSize(sf::Vector2f(120.f, 15.f));
    paddle.pShape.setFillColor(sf::Color::Green);
    paddle.pShape.setPosition(windowHeight - (windowHeight / 5), windowWidth / 2);
    
    Ball ball;
    ball.ballShape.setRadius(ball.ballRadius);
    ball.ballShape.setPosition(paddle.pShape.getPosition().x, paddle.pShape.getPosition().y - 75);
    ball.ballShape.setFillColor(sf::Color::Cyan);
    ball.ballVelocity.x = rand() % 10;
    ball.ballVelocity.y = -5;

    

    while (window.isOpen())
    {
        if (sf::Mouse::getPosition(window).x > paddle.pShape.getSize().x / 2 && sf::Mouse::getPosition(window).x < window.getSize().x - paddle.pShape.getSize().x/2)
        {
            paddle.pShape.setPosition(sf::Mouse::getPosition(window).x - paddle.pShape.getSize().x/2, paddle.pShape.getPosition().y);
        }

        ball.ballShape.move(ball.ballVelocity);
        if(top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(0);
            sound.setBuffer(wallSoundBuffer);
            sound.play();
        }
        if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(0);
            lives -= 1;
            if (lives == 0)
            {
                return 1;
            }
        }
        //wall colliders
        if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) || right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(1);
            sound.setBuffer(wallSoundBuffer);
            sound.play();
        }
        //paddle collides with the ball
        if (paddle.pShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(0);
            sound.setBuffer(paddleSoundBuffer);
            sound.play();
        }

        for (int i = 0; i < Bricks.size(); i++)
        {
            if (Bricks[i].bShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
            {
                ball.Bounce(0);
                Bricks[i].bShape.setPosition(1200, 0);
                score += 1;
                ball.ballVelocity = ball.ballVelocity * 1.03f;
                if (score == 30)
                {
                    return 1;
                }
                sound.setBuffer(brickSoundBuffer);
                sound.play();
            }
        }

        sf::Event event;
        //PollEvent is our window updating
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        for (int i = 0; i < Bricks.size(); i++)
        {
            window.draw(Bricks[i].bShape);
        }
        scoreText.setString("Score: " + to_string(score));
        livesText.setString("Lives: " + to_string(lives));
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(paddle.pShape);
        window.draw(ball.ballShape);
        window.display();
    }
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
