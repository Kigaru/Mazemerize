#include "level.h"


Level::Level(Vector2f playerSpawn,
	std::vector<Vector2f> walls,
	std::vector<Vector2f> chests,
	std::vector<Vector2f> lockedDoors,
	Vector2f finalDoor,
	Vector2f goal)
{
	m_playerspawn = playerSpawn;
	m_walls = walls;
	m_lockedDoors = lockedDoors;
	m_finalDoor = finalDoor;
	m_goal = goal;
	m_chests = chests;
}


Vector2f Level::getPlayerSpawn()
{
	return m_playerspawn;
}

std::vector<Vector2f> Level::getWalls()
{
	return m_walls;
}

std::vector<Vector2f>& Level::getChests()
{
	return m_chests;
}

std::vector<Vector2f> Level::getLockedDoors()
{
	return m_lockedDoors;
}

Vector2f Level::getFinalDoor()
{
	return m_finalDoor;
}

Vector2f Level::getGoal()
{
	return m_goal;
}

void Level::popLockedDoor()
{
	m_lockedDoors.pop_back();
}

void Level::removeFinalDoor()
{
	m_finalDoor.x = -1;
	m_finalDoor.y = -1;
}
