#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputMgr.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Frameworks!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }

        if (InputMgr::GetKey(sf::Keyboard::Num1))
        {
            std::cout << "Num 1 Pressed" << std::endl;
        }
        if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
        {
            std::cout << "Num 1 Down" << std::endl;
        }
        if (InputMgr::GetKeyUp(sf::Keyboard::Num1))
        {
            std::cout << "Num 1 Up" << std::endl;
        }
        if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
        {
            std::cout << "Num 2 Down" << std::endl;
        }
        if (InputMgr::GetKeyUp(sf::Keyboard::Num2))
        {
            std::cout << "Num 2 Up" << std::endl;
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}