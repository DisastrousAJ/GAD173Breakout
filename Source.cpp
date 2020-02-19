#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:
    Paddle(sf::Vector2f size, sf::Color color)
    {
        paddle.setSize(size);
        paddle.setFillColor(color);
        paddle.setOutlineThickness(1);
    }

    void drawTo(sf::RenderWindow& window)
    {
        window.draw(paddle);
    }

    void setPos(sf::Vector2f newPos)
    {
        paddle.setPosition(newPos);
    }

    void Move(sf::Vector2f distance)
    {
        paddle.move(distance);
    }


private:
    sf::RectangleShape paddle;
};