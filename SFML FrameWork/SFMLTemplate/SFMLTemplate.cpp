#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputMgr.h"
#include "ResourceMgr.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Frameworks!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    ResourceMgr<sf::Texture>::Instance().Load("graphics/player.png");
    sf::Sprite player;
    player.setTexture(ResourceMgr<sf::Texture>::Instance().Get("graphics/player.png"));

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

        if (InputMgr::GetMouse(sf::Mouse::Left))
        {
            std::cout << "Left Pressed" << std::endl;
        }
        if (InputMgr::GetMouseDown(sf::Mouse::Left))
        {
            std::cout << "Left Down" << std::endl;
        }
        if (InputMgr::GetMouseUp(sf::Mouse::Left))
        {
            std::cout << "Left Up" << std::endl;
        }

        if (InputMgr::GetMouse(sf::Mouse::Right))
        {
            std::cout << "Right Pressed" << std::endl;
        }
        if (InputMgr::GetMouseDown(sf::Mouse::Right))
        {
            std::cout << "Right Down" << std::endl;
        }
        if (InputMgr::GetMouseUp(sf::Mouse::Right))
        {
            std::cout << "Right Up" << std::endl;
        }

        if (InputMgr::GetMouseDown(sf::Mouse::Middle))
        {
            std::cout << "(" << InputMgr::GetMousePoint().x << ", " << InputMgr::GetMousePoint().y << ")" << std::endl;
        }

        window.clear();
        window.draw(shape);
        window.draw(player);
        window.display();
    }

    return 0;
}