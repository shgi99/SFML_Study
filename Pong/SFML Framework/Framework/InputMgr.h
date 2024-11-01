#pragma once
#include <list>
enum class Axis
{
	Horizontal,
	Vertical,
};
struct AxisInfo
{
	Axis axis;
	std::list<int> positives;
	std::list<int> negatives;
	float sensi = 10.f;
	float value = 0.f; // -1.f ~ 1.f

	void AddKey(bool positive, int code)
	{
		if (positive)
		{
			positives.push_back(code);
		}
		else
		{
			negatives.push_back(code);
		}
	}
};
class InputMgr
{
private:
	static std::list<int> downKeys;
	static std::list<int> heldKeys;
	static std::list<int> upKeys;
	
	static sf::Vector2i mousePosition;

	static std::unordered_map<Axis, AxisInfo> axisInfoMap;
public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);	

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);

	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButton(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);

	static sf::Vector2i GetMousePosition() { return mousePosition; }

	static float GetAxisRaw(Axis axis);
	static float GetAxis(Axis axis);
private:
	static bool Contains(const std::list<int>& list, int code);
	static void Remove(std::list<int>& list, int code);
};

