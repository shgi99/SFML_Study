#pragma once
#include <list>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

class InputMgr
{
private:
	static std::list<sf::Keyboard::Key> downList;
	static std::list<sf::Keyboard::Key> heldList;
	static std::list<sf::Keyboard::Key> upList;
	
public:
	static void Clear();
	static void UpdateEvent(const sf::Event& ev);

	// 매개변수로 넘어오는 키가 눌려있는지 아닌지
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	// 매개변수로 넘어오는 키가 떼어졌는지 아닌지
	static bool GetKeyUp(sf::Keyboard::Key key);
};

