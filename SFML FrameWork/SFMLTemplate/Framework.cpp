#include "stdafx.h"
#include "Framework.h"
#include "SpriteGo.h"
void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width, height), name);
    // ���̺� ������ �ε�, ���̶� �����ϰ� ó������ ������ ����� ���ҽ� �ε�
    SCENE_MGR.Init();
}

void Framework::Do()
{

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        realTime += realDeltaTime;
        time += deltaTime;
        // �̺�Ʈ ����
        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }
        // ������Ʈ
        SCENE_MGR.Update(deltaTime);
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
            std::cout << "(" << InputMgr::GetMousePoint(window).x << ", " << InputMgr::GetMousePoint(window).y << ")" << std::endl;
        }
        //��ο�
        window.clear();
        SCENE_MGR.Draw(window);
        //window.draw(shape);
        //window.draw(player);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
}   
