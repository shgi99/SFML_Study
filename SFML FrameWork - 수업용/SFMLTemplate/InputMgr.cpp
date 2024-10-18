#include "InputMgr.h"

std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::heldList;
std::list<sf::Keyboard::Key> InputMgr::upList;
    
void InputMgr::Clear()
{
    downList.clear();
    upList.clear();
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        // 범위 안에서 원하는 값을 찾는 함수 - 찾으면 첫번째로 일치하는 원소를 가리키는 iterator를 반환
        // 프레임단위로 키 입력을 리스트에 넣는데, 중복된 키 입력을 방지하도록 구현
        if (std::find(heldList.begin(), heldList.end(), ev.key.code) == heldList.end())
        {
            heldList.push_back(ev.key.code);
            downList.push_back(ev.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        heldList.remove(ev.key.code);
        upList.push_back(ev.key.code);
        break;
    }
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{   
    return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
    return std::find(heldList.begin(), heldList.end(), key) != heldList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}
