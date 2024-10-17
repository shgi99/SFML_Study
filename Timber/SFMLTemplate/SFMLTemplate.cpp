#include <SFML/Graphics.hpp>
#include<iostream>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL)); // 현재 시간이 반환됨

    sf::VideoMode vm(1920, 1080);
    sf::RenderWindow window(vm, "Timber~", sf::Style::Default);

    sf::Vector2u winSize = window.getSize();
    sf::Vector2f centerPos = (sf::Vector2f)(winSize / 2u);

    // 이미지 리소스를 담는 객체 - Texture
    sf::Texture texBackground; 
    texBackground.loadFromFile("graphics/background.png");
    sf::Texture texCloud;
    texCloud.loadFromFile("graphics/cloud.png");
    sf::Texture texBee;
    texBee.loadFromFile("graphics/bee.png");
    sf::Texture texTree;
    texTree.loadFromFile("graphics/tree.png");

    // 이미지 리소스를 가지고 실제로 그리는 객체 - Sprite
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(texBackground); // 텍스쳐 세팅
    sf::Sprite spriteCloud[3];
    int flagCloud[3] = { 0 };
    for (int i = 0; i < 3; i++)
    {
        flagCloud[i] = rand() % 2;
        float randScale = rand() % 2 + 0.4;
        spriteCloud[i].setTexture(texCloud);
        if (flagCloud[i] == 0)
        {
            spriteCloud[i].setPosition(sf::Vector2f(-(spriteCloud[i].getLocalBounds().width + 50.f), texCloud.getSize().y * i));
            spriteCloud[i].setScale(sf::Vector2f(randScale, randScale));
        }
        else
        {
            spriteCloud[i].setPosition(sf::Vector2f(winSize.x + 50.f, texCloud.getSize().y * i));
            spriteCloud[i].setScale(sf::Vector2f(-randScale, randScale));
        }
    }
    sf::Sprite spriteBee;
    spriteBee.setTexture(texBee);
    spriteBee.setPosition(sf::Vector2f(0, vm.height * 0.5f + 200));
    spriteBee.setScale(-1.f, 1.f); // 뒤집기
    sf::Vector2f startBeePos = spriteBee.getPosition();

    sf::Sprite spriteTree;
    spriteTree.setTexture(texTree);
    spriteTree.setOrigin(texTree.getSize().x * 0.5f, 0);
    spriteTree.setPosition(sf::Vector2f(centerPos.x, 0.0f));
    
    
    sf::Vector2f speedCloud[3]; 
    sf::Vector2f sizeCloud[3];
    for (int i = 0; i < 3; i++)
    {
        speedCloud[i] = sf::Vector2f((rand() % 200 + 80), 0.f);
    }

    sf::Clock clock; // 시간, 시계 관련 객체

    while (window.isOpen())
    {
        sf::Time dt = clock.restart(); // 지난 시간 반환(처음엔 0)
        float deltaTime = dt.asSeconds();

        sf::Event event;

        // 메세지(이벤트) 루프
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window.close(); // 종료 버튼 누를시 꺼지도록 이벤트 처리
                break;
            case sf::Event::EventType::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Space:
                    int randomNumber = rand() % 2;
                    std::cout << randomNumber << " ";
                    break;
                }
            default:
                break;
            }
        }

        // 벌의 위치를 속도와 시간을 이용하여 이동시킴
        sf::Vector2f beePos = spriteBee.getPosition();
        beePos.x += 100.f * deltaTime;
        beePos.y = startBeePos.y + (sin(beePos.x / 70) * 100.f);
        spriteBee.setPosition(beePos);

        for (int i = 0; i < 3; i++)
        {
            sf::Vector2f cloudPos = spriteCloud[i].getPosition();

            if (cloudPos.x < -(spriteCloud[i].getLocalBounds().width + 100.f) || cloudPos.x > winSize.x + 100.f) {
                flagCloud[i] = rand() % 2;
                float randScale = rand() % 2 + 0.4;

                if (flagCloud[i] == 0) 
                {
                    spriteCloud[i].setPosition(sf::Vector2f(-(spriteCloud[i].getLocalBounds().width + 50.f), texCloud.getSize().y * i));
                    spriteCloud[i].setScale(sf::Vector2f(randScale, randScale));
                }
                else 
                {
                    spriteCloud[i].setPosition(sf::Vector2f(winSize.x + 50.f, texCloud.getSize().y * i));
                    spriteCloud[i].setScale(sf::Vector2f(-randScale, randScale));
                }
            }

            cloudPos = spriteCloud[i].getPosition();

            if (flagCloud[i] == 0) 
            {
                cloudPos += speedCloud[i] * deltaTime;
            }
            else 
            {
                cloudPos -= speedCloud[i] * deltaTime;
            }
            spriteCloud[i].setPosition(cloudPos);
        }

        // 업데이트
        window.clear();

        // 그리기
        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteCloud[i]);
        }
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display(); // 화면에 갱신한다
    }

    return 0;
}