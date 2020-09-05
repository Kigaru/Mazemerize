#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "level.h"

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float TILE_SIZE = 50;
	//where is the player?
	Vector2f m_Position;

	//player sprite
	Sprite m_Sprite;

	//player texture
	Texture m_Texture;

	//how big is each tile of the arena
	int m_TileSize;

	//which directions is the player currently moving in?
	bool m_UpPressed, m_DownPressed, m_LeftPressed, m_RightPressed;

	//speed in pixels per second
	float m_Speed;

	//score
	bool m_victory;



public:
	Player();

	void spawn(Vector2f position);

	//where is the player?
	FloatRect getPosition();

	//where is the center of the player?
	Vector2f getCenter();

	//which angle is the player facing
	float getRotation();

	//get sprite
	Sprite getSprite();

	//move the player
	void moveLeft(), moveRight(), moveUp(), moveDown();

	//stop the player moving in a specific direction
	void stopLeft(), stopRight(), stopUp(), stopDown();

	//called every frame
	void update(float elapsedTime, Level& rLevel, VertexArray& rVA);

	//has the player won?
	bool didPlayerWin();
};
#endif