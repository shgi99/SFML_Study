#pragma once
#include <list>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

class InputMgr
{
private:
	static std::list<sf::Keyboard::Key> downKeyList;
	static std::list<sf::Keyboard::Key> upKeyList;
	static std::list<sf::Keyboard::Key> heldKeyList;
	static std::list<sf::Mouse::Button> downMouseList;
	static std::list<sf::Mouse::Button> upMouseList;
	static std::list<sf::Mouse::Button> heldMouseList;
	static sf::Vector2i posMouse;

public:
	static void Clear();
	static void UpdateEvent(sf::Event ev);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetMouseDown(sf::Mouse::Button button);
	static bool GetMouse(sf::Mouse::Button button);
	static bool GetMouseUp(sf::Mouse::Button button);
	static sf::Vector2i GetMousePoint();
};