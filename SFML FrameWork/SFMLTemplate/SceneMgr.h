#pragma once
class Scene; // 전방 선언 - 이 클래스가 존재함을 미리 컴파일때 알리는 것
class SceneMgr
{
protected:
	std::vector<Scene*> scenes;
public:

};

