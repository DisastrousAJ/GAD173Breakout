#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:
    void UpdatePosition(float dir)
    {
        pShape.setPosition(dir * speed, pShape.getPosition().y);
       
    }
    sf::RectangleShape pShape;
    float speed = 10.f;
    sf::Vector2f pSize;
    sf::Color pColour;
};

