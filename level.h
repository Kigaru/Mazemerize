#ifndef level_h
#define level_h

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
class Level 
{
private:
	std::vector<Vector2f> m_walls;
	Vector2f m_playerspawn;
	std::vector<Vector2f> m_chests;
	std::vector<Vector2f> m_lockedDoors;
	Vector2f m_finalDoor;
	Vector2f m_goal;

public:
	Level(Vector2f playerSpawn,
		std::vector<Vector2f> walls,
		std::vector<Vector2f> chests,
		std::vector<Vector2f> lockedDoors,
		Vector2f finalDoor,
		Vector2f goal);


	Vector2f getPlayerSpawn();
	std::vector<Vector2f> getWalls();
	std::vector<Vector2f>& getChests();
	std::vector<Vector2f> getLockedDoors();
	void popLockedDoor();
	void removeFinalDoor();
	Vector2f getFinalDoor();
	Vector2f getGoal();
};

#endif