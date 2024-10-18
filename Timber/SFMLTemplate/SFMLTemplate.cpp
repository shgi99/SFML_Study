#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

enum class Sides
{
    Left,
    Right,
    None,
};

int main()
{
    srand(time(NULL)); // 현재 시간이 반환됨
    int score = 0;
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
    texTree.loadFromFile("graphics/tree2.png");
    sf::Texture texBranch;
    texBranch.loadFromFile("graphics/branch.png");
    sf::Texture texPlayer;
    texPlayer.loadFromFile("graphics/player.png");
    sf::Texture texRIP;
    texRIP.loadFromFile("graphics/rip.png");
    
    
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    sf::Text guideText;
    guideText.setFont(font);
    guideText.setString("PRESS SPACE TO START!");
    guideText.setCharacterSize(70);
    guideText.setFillColor(sf::Color::White);
    guideText.setOrigin(guideText.getLocalBounds().width / 2, guideText.getLocalBounds().height / 2);
    guideText.setPosition(centerPos);
    bool isPause = true;
    bool isGameOver = false;

    // 이미지 리소스를 가지고 실제로 그리는 객체 - Sprite
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(texBackground); // 텍스쳐 세팅   
    sf::Sprite spriteCloud[3];
    int flagCloud[3] = { 0 };
    for (int i = 0; i < 3; i++)
    {
        flagCloud[i] = rand() % 2;
        float randScale = float(rand() % 2) + 0.4;
        spriteCloud[i].setTexture(texCloud);
        if (flagCloud[i] == 0)
        {
            spriteCloud[i].setPosition(sf::Vector2f(-(spriteCloud[i].getLocalBounds().width + 50.f), (float)(rand() % 500)));
            spriteCloud[i].setScale(sf::Vector2f(randScale, randScale));
        }
        else
        {
            spriteCloud[i].setPosition(sf::Vector2f(winSize.x + 50.f, (float)(rand() % 500)));
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

    const int numOfBranches = 6;
    Sides sideBranches[numOfBranches] = { Sides::None };

    sf::Sprite spriteBranches[numOfBranches];
    sf::Vector2f originBranch;
    originBranch.x = -(texTree.getSize().x * 0.5f);
    originBranch.y = texBranch.getSize().y * 0.5f;

    Sides sidePlayer = Sides::Right;
    bool isLeftKey = false;
    bool isRightKey = false;
    bool isLeftKeyDown = false;
    bool isRightKeyDown = false;

    sf::Vector2f playerPosArray[2];
    playerPosArray[0].x = centerPos.x - texTree.getSize().x;
    playerPosArray[0].y = texTree.getSize().y - 50;
    playerPosArray[1].x = centerPos.x + texTree.getSize().x;
    playerPosArray[1].y = texTree.getSize().y - 50;

    sf::Vector2f playerScaleArray[2];
    playerScaleArray[0] = { -1.f, 1.f };
    playerScaleArray[1] = { 1.f, 1.f };


    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texPlayer);
    spritePlayer.setOrigin(spritePlayer.getLocalBounds().width * 0.5f, spritePlayer.getLocalBounds().height);
    spritePlayer.setScale(playerScaleArray[(int)sidePlayer]);
    spritePlayer.setPosition(playerPosArray[(int)sidePlayer]);

    sf::Vector2f posBranch(centerPos.x, 800.f);
    for (int i = 0; i < numOfBranches; i++)
    {
        if (i != 0)
        {
            sideBranches[i] = (Sides)(rand() % 3);
        }
        spriteBranches[i].setTexture(texBranch);
        spriteBranches[i].setOrigin(originBranch);
        spriteBranches[i].setPosition(posBranch);
        // spriteBranches[i].setPosition(centerPos);
        posBranch.y -= 150.f;

        spriteBranches[i].setScale(sideBranches[i] == Sides::Right ? 1.f : -1.f, 1.f);
    }

    float timeBarWidth = 400.f;
    float timeBarHeight = 80.f;
    float timeBarDuration = 3.f;
    float timeAddTime = 0.5f;
    float timeBarSpeed = timeBarWidth / timeBarDuration;


    sf::RectangleShape timeBar;
    timeBar.setSize(sf::Vector2f(timeBarWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition(centerPos.x - timeBar.getLocalBounds().width * 0.5, winSize.y - 100.f);
    
    // timeBar.setOrigin(timeBar.getLocalBounds().width / 2, timeBar.getLocalBounds().height / 2);
    
    sf::Vector2f speedCloud[3]; 
    sf::Vector2f sizeCloud[3];
    for (int i = 0; i < 3; i++)
    {
        speedCloud[i] = sf::Vector2f((rand() % 200 + 80), 0.f);
    }

    

    sf::Clock clock; // 시간, 시계 관련 객체
    float timeScale = 1.f;
   

    while (window.isOpen())
    {
        sf::Time dt = clock.restart(); // 지난 시간 반환(처음엔 0)
        float deltaTime = dt.asSeconds();
        deltaTime *= timeScale;

        isLeftKeyDown = false;
        isRightKeyDown = false;

        sf::Event event;

        // 메세지(이벤트) 루프
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window.close(); // 종료 버튼 누를시 꺼지도록 이벤트 처리
                break;
            case sf::Event::EventType::KeyReleased: // 꾹 누르는 연속 입력을 방지하기 위한 부분
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    isLeftKey = false;
                case sf::Keyboard::Right:
                    isRightKey = false;
                }
                break;
            case sf::Event::EventType::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Return:
                    if (isGameOver)
                    {
                        scoreText.setString("Score: 0");
                        guideText.setString("PRESS SPACE TO START!");
                        guideText.setOrigin(guideText.getLocalBounds().width / 2, guideText.getLocalBounds().height / 2);
                        guideText.setPosition(centerPos);
                        isPause = true;
                        isGameOver = false;

                        int flagCloud[3] = { 0 };
                        for (int i = 0; i < 3; i++)
                        {
                            flagCloud[i] = rand() % 2;
                            float randScale = float(rand() % 2) + 0.4;
                            spriteCloud[i].setTexture(texCloud);
                            if (flagCloud[i] == 0)
                            {
                                spriteCloud[i].setPosition(sf::Vector2f(-(spriteCloud[i].getLocalBounds().width + 50.f), (float)(rand() % 500)));
                                spriteCloud[i].setScale(sf::Vector2f(randScale, randScale));
                            }
                            else
                            {
                                spriteCloud[i].setPosition(sf::Vector2f(winSize.x + 50.f, (float)(rand() % 500)));
                            }
                                spriteCloud[i].setScale(sf::Vector2f(-randScale, randScale));
                        }

                        spriteBee.setPosition(sf::Vector2f(0, vm.height * 0.5f + 200));
                        spriteBee.setScale(-1.f, 1.f); // 뒤집기

                        spriteTree.setOrigin(texTree.getSize().x * 0.5f, 0);
                        spriteTree.setPosition(sf::Vector2f(centerPos.x, 0.0f));


                        sidePlayer = Sides::Right;
                        isLeftKey = false;
                        isRightKey = false;
                        isLeftKeyDown = false;
                        isRightKeyDown = false;

                        spritePlayer.setTexture(texPlayer);
                        spritePlayer.setOrigin(spritePlayer.getLocalBounds().width * 0.5f, spritePlayer.getLocalBounds().height);
                        spritePlayer.setScale(playerScaleArray[(int)sidePlayer]);
                        spritePlayer.setPosition(playerPosArray[(int)sidePlayer]);

                        sf::Vector2f posBranch(centerPos.x, 800.f);
                        for (int i = 0; i < numOfBranches; i++)
                        {
                            if (i != 0)
                            {
                                sideBranches[i] = (Sides)(rand() % 3);
                            }

                            // 플레이어와 가지가 겹치지 않도록 처리
                            if (i == 0 && sidePlayer == sideBranches[0])
                            {
                                // 플레이어가 오른쪽에 있으면, 첫 번째 가지는 왼쪽에 생성되도록 강제
                                sideBranches[0] = Sides::Left;
                            }
                            spriteBranches[i].setOrigin(originBranch);
                            spriteBranches[i].setPosition(posBranch);
                            // spriteBranches[i].setPosition(centerPos);
                            posBranch.y -= 150.f;

                            spriteBranches[i].setScale(sideBranches[i] == Sides::Right ? 1.f : -1.f, 1.f);
                        }

                        for (int i = 0; i < 3; i++)
                        {
                            speedCloud[i] = sf::Vector2f((rand() % 200 + 80), 0.f);
                        }
                        timeBar.setSize(sf::Vector2f(timeBarWidth, timeBarHeight));
                        timeBar.setFillColor(sf::Color::Red);
                        timeBar.setPosition(centerPos.x - timeBar.getLocalBounds().width * 0.5, winSize.y - 100.f);
                        score = 0;
                    }
                    break;
                case sf::Keyboard::Space:
                    if (!isGameOver)
                    {
                        isPause = !isPause;
                        guideText.setString(isPause ? "PRESS SPACE TO RESUME!" : "");
                        guideText.setOrigin(guideText.getLocalBounds().width / 2, guideText.getLocalBounds().height / 2);
                        guideText.setPosition(centerPos);
                    }
                    break;
                case sf::Keyboard::Num1:
                    score += 10;
                    break;
                case sf::Keyboard::Num2:
                    score -= 10;
                    break;
                case sf::Keyboard::Left:
                    // 플레이어 좌우 이동
                    if (!isLeftKey)
                    {
                        isLeftKeyDown = true;
                    }
                    isLeftKey = true;
                    break;
                case sf::Keyboard::Right:
                    if (!isRightKey)
                    {
                        isRightKeyDown = true;
                    }
                    isRightKey = true;
                    break;
                }
                break;
            default:
                break;
            }
        }

        if (!isPause)
        {
            guideText.setString(" ");
            // 타임바(체력바)가 0이 될때까지 줄어들도록 함
            sf::Vector2f timeSize = timeBar.getSize();
            timeSize.x -= timeBarSpeed * deltaTime;
            if (timeSize.x < 0.f)
            {
                spritePlayer.setTexture(texRIP);
                guideText.setString("\t\t     GAME OVER!\n\t\t   YOUR SCORE: " + std::to_string(score) + "\nPRESS ENTER TO START NEW GAME!");
                guideText.setOrigin(guideText.getLocalBounds().width / 2, guideText.getLocalBounds().height / 2);
                guideText.setPosition(centerPos);
                isPause = true;
                isGameOver = true;
            }
            timeBar.setSize(timeSize);

            if (isLeftKeyDown || isRightKeyDown)
            {
                // 나무가지를 1칸씩 내려가게 하기 위해 Sides 배열을 한칸씩 당기고 맨 끝 칸은 초기화시켜주면서 스케일도 초기화해준다.
                   // 그려주는 것은 밑에서 갱신된걸로 드로우를 계속 해준다는 것을 인지할 것
                for (int i = 1; i < numOfBranches; i++)
                {
                    sideBranches[i - 1] = sideBranches[i];
                }
                sideBranches[numOfBranches - 1] = (Sides)(rand() % 3);
                for (int i = 0; i < numOfBranches; i++)
                {
                    spriteBranches[i].setScale(sideBranches[i] == Sides::Right ? 1.f : -1.f, 1.f);
                }
                sidePlayer = isLeftKeyDown ? Sides::Left : Sides::Right;
                spritePlayer.setScale(playerScaleArray[(int)sidePlayer]);
                spritePlayer.setPosition(playerPosArray[(int)sidePlayer]);

                if (sidePlayer == sideBranches[0] || timeBar.getSize().x <= 0)
                {
                    spritePlayer.setTexture(texRIP);
                    guideText.setString("\t\t     GAME OVER!\n\t\t   YOUR SCORE: " + std::to_string(score) + "\nPRESS ENTER TO START NEW GAME!");
                    guideText.setOrigin(guideText.getLocalBounds().width / 2, guideText.getLocalBounds().height / 2);
                    guideText.setPosition(centerPos);
                    isPause = true;
                    isGameOver = true;
                }
                else
                {
                    score += 10;
                    sf::Vector2f timeBarSize = timeBar.getSize();
                    timeBarSize.x += timeBarSpeed * timeAddTime;
                    if (timeBarSize.x > timeBarWidth)
                    {
                        timeBarSize.x = timeBarWidth;
                    }
                    timeBar.setSize(timeBarSize);
                }
            }
            // 벌의 위치를 속도와 시간을 이용하여 이동시킴
            sf::Vector2f beePos = spriteBee.getPosition();
            beePos.x += 100.f * deltaTime;
            beePos.y = startBeePos.y + (sin(beePos.x / 70) * 100.f);
            spriteBee.setPosition(beePos);

            // 구름이 화면밖으로 나갈때 랜덤하게 양쪽 중 한 곳에서 초기화하여 생성
            for (int i = 0; i < 3; i++)
            {
                sf::Vector2f cloudPos = spriteCloud[i].getPosition();

                if (cloudPos.x < -(spriteCloud[i].getLocalBounds().width + 100.f) || cloudPos.x > winSize.x + 100.f) {
                    flagCloud[i] = rand() % 2;
                    float randomScale = float(rand() % 2) + 0.4;

                    if (flagCloud[i] == 0)
                    {
                        spriteCloud[i].setPosition(sf::Vector2f(-(spriteCloud[i].getLocalBounds().width + 50.f), (float)(rand() % 500)));
                        spriteCloud[i].setScale(sf::Vector2f(randomScale, randomScale));
                    }
                    else
                    {
                        spriteCloud[i].setPosition(sf::Vector2f(winSize.x + 50.f, (float)(rand() % 500)));
                        spriteCloud[i].setScale(sf::Vector2f(-randomScale, randomScale));
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
            // 스코어 UI 점수 갱신
            scoreText.setString("SCORE: " + std::to_string(score));

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
        window.draw(spritePlayer);
        for (int i = 0; i < numOfBranches; i++)
        {
            if (sideBranches[i] != Sides::None)
            {
                window.draw(spriteBranches[i]);
            }
        }
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(guideText);
        window.draw(timeBar);
        window.display(); // 화면에 갱신한다
    }

    return 0;
}