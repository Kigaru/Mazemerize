#include "player.h"


Player::Player() 
{
	m_Speed = START_SPEED;
	m_TileSize = TILE_SIZE;
	m_Texture.loadFromFile("./resources/textures/player.png");

	m_Sprite.setTexture(m_Texture);

	m_Sprite.setOrigin(10, 10);
	m_victory = false;
}

void Player::spawn(Vector2f position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
}


FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;

}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

void Player::moveLeft() 
{
	m_LeftPressed = true;
	m_Sprite.setRotation(90);
}

void Player::moveRight()
{
	m_RightPressed = true;
	m_Sprite.setRotation(270);
}

void Player::moveUp()
{
	m_UpPressed = true;
	m_Sprite.setRotation(180);
}

void Player::moveDown()
{
	m_DownPressed = true;
	m_Sprite.setRotation(0);
}

void Player::stopLeft() 
{
	m_LeftPressed = false;
} 

void Player::stopRight() 
{
	m_RightPressed = false;
}

void Player::stopUp() 
{
	m_UpPressed = false;

}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Level& rLevel, VertexArray& rVA)
{
	Vector2f playerTopLeft(m_Position.x - (m_Sprite.getLocalBounds().width / 2), m_Position.y - (m_Sprite.getLocalBounds().height / 2));
	Vector2f playerTopRight(m_Position.x + (m_Sprite.getLocalBounds().width / 2), m_Position.y - (m_Sprite.getLocalBounds().height / 2));
	Vector2f playerBottomLeft(m_Position.x - (m_Sprite.getLocalBounds().width / 2), m_Position.y + (m_Sprite.getLocalBounds().height / 2));
	Vector2f playerBottomRight(m_Position.x + (m_Sprite.getLocalBounds().width / 2), m_Position.y + (m_Sprite.getLocalBounds().height / 2));

	if (m_UpPressed)
	{
		bool collided = false;
		for (Vector2f vec : rLevel.getWalls())
		{
			//detect a collision walls
			if (playerBottomLeft.y > vec.y*m_TileSize && (vec.x * m_TileSize < playerTopRight.x && vec.y * m_TileSize + m_TileSize > playerTopRight.y - (m_Speed * elapsedTime)) && (vec.x * m_TileSize + m_TileSize > playerTopLeft.x && vec.y * m_TileSize + m_TileSize > playerTopLeft.y - (m_Speed * elapsedTime))) 
			{ 
				collided = true; 
			}
		}
		for (Vector2f vec : rLevel.getLockedDoors())
		{
			//detect a collision doors
			if (playerBottomLeft.y > vec.y* m_TileSize && (vec.x * m_TileSize < playerTopRight.x && vec.y * m_TileSize + m_TileSize > playerTopRight.y - (m_Speed * elapsedTime)) && (vec.x * m_TileSize + m_TileSize > playerTopLeft.x&& vec.y* m_TileSize + m_TileSize > playerTopLeft.y - (m_Speed * elapsedTime)))
			{
				collided = true;
			}
		}
		//detect a for final door collision
		if (playerBottomLeft.y > rLevel.getFinalDoor().y* m_TileSize && (rLevel.getFinalDoor().x * m_TileSize < playerTopRight.x && rLevel.getFinalDoor().y * m_TileSize + m_TileSize > playerTopRight.y - (m_Speed * elapsedTime)) && (rLevel.getFinalDoor().x * m_TileSize + m_TileSize > playerTopLeft.x&& rLevel.getFinalDoor().y* m_TileSize + m_TileSize > playerTopLeft.y - (m_Speed * elapsedTime)))
		{
			collided = true;
		}
		if(!collided) m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed)
	{
		bool collided = false;
		for (Vector2f vec : rLevel.getWalls())
		{
			//detect a collision
			if (playerTopLeft.y < vec.y* m_TileSize && (vec.x * m_TileSize < playerBottomRight.x && vec.y * m_TileSize < playerBottomRight.y + (m_Speed * elapsedTime)) && (vec.x * m_TileSize + m_TileSize > playerBottomLeft.x&& vec.y* m_TileSize < playerBottomLeft.y + (m_Speed * elapsedTime)))
			{
				collided = true;
			}

		}
		for (Vector2f vec : rLevel.getLockedDoors())
		{
			//detect a collision
			if (playerTopLeft.y < vec.y* m_TileSize && (vec.x * m_TileSize < playerBottomRight.x && vec.y * m_TileSize < playerBottomRight.y + (m_Speed * elapsedTime)) && (vec.x * m_TileSize + m_TileSize > playerBottomLeft.x&& vec.y* m_TileSize < playerBottomLeft.y + (m_Speed * elapsedTime)))
			{
				collided = true;
			}

		}
		//detect a collision for final door
		if (playerTopLeft.y < rLevel.getFinalDoor().y * m_TileSize && (rLevel.getFinalDoor().x * m_TileSize < playerBottomRight.x && rLevel.getFinalDoor().y * m_TileSize < playerBottomRight.y + (m_Speed * elapsedTime)) && (rLevel.getFinalDoor().x * m_TileSize + m_TileSize > playerBottomLeft.x&& rLevel.getFinalDoor().y* m_TileSize < playerBottomLeft.y + (m_Speed * elapsedTime)))
		{
			collided = true;
		}
		if(!collided) m_Position.y += m_Speed * elapsedTime;
	}
	if (m_RightPressed)
	{
		bool collided = false;
		for (Vector2f vec : rLevel.getWalls())
		{
			//detect a collision
			if (playerBottomLeft.x < vec.x* m_TileSize && (vec.x * m_TileSize < playerBottomRight.x + (m_Speed * elapsedTime) && vec.y * m_TileSize < playerBottomRight.y) && (vec.x * m_TileSize < playerTopRight.x + (m_Speed * elapsedTime) && vec.y* m_TileSize + m_TileSize > playerTopRight.y))
			{
				collided = true;
			}

		}
		for (Vector2f vec : rLevel.getLockedDoors())
		{
			//detect a collision
			if (playerBottomLeft.x < vec.x* m_TileSize && (vec.x * m_TileSize < playerBottomRight.x + (m_Speed * elapsedTime) && vec.y * m_TileSize < playerBottomRight.y) && (vec.x * m_TileSize < playerTopRight.x + (m_Speed * elapsedTime) && vec.y* m_TileSize + m_TileSize > playerTopRight.y))
			{
				collided = true;
			}

		}
		//detect a collision for final door
		if (playerBottomLeft.x < rLevel.getFinalDoor().x * m_TileSize && (rLevel.getFinalDoor().x * m_TileSize < playerBottomRight.x + (m_Speed * elapsedTime) && rLevel.getFinalDoor().y * m_TileSize < playerBottomRight.y) && (rLevel.getFinalDoor().x * m_TileSize < playerTopRight.x + (m_Speed * elapsedTime) && rLevel.getFinalDoor().y * m_TileSize + m_TileSize > playerTopRight.y))
		{
			collided = true;
		}

		if (!collided) m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed)
	{
		bool collided = false;
		for (Vector2f vec : rLevel.getWalls())
		{
			//detect a collision
			if (playerBottomRight.x > vec.x * m_TileSize + m_TileSize && (vec.x * m_TileSize + m_TileSize > playerTopLeft.x - (m_Speed * elapsedTime) && vec.y * m_TileSize + m_TileSize > playerTopLeft.y) && (vec.x * m_TileSize + m_TileSize > playerBottomLeft.x - (m_Speed * elapsedTime) && vec.y * m_TileSize < playerBottomLeft.y))
			{
				collided = true;
			}

		}
		for (Vector2f vec : rLevel.getLockedDoors())
		{
			//detect a collision
			if (playerBottomRight.x > vec.x * m_TileSize + m_TileSize && (vec.x * m_TileSize + m_TileSize > playerTopLeft.x - (m_Speed * elapsedTime) && vec.y * m_TileSize + m_TileSize > playerTopLeft.y) && (vec.x * m_TileSize + m_TileSize > playerBottomLeft.x - (m_Speed * elapsedTime) && vec.y * m_TileSize < playerBottomLeft.y))
			{
				collided = true;
			}

		}
		//detect a collision for final door 
		if (playerBottomRight.x > rLevel.getFinalDoor().x* m_TileSize + m_TileSize && (rLevel.getFinalDoor().x * m_TileSize + m_TileSize > playerTopLeft.x - (m_Speed * elapsedTime) && rLevel.getFinalDoor().y * m_TileSize + m_TileSize > playerTopLeft.y) && (rLevel.getFinalDoor().x * m_TileSize + m_TileSize > playerBottomLeft.x - (m_Speed * elapsedTime) && rLevel.getFinalDoor().y * m_TileSize < playerBottomLeft.y))
		{
			collided = true;
		}
		if (!collided) m_Position.x -= m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position);


	for (Vector2f& vec : rLevel.getChests())
	{
		bool collided = false;
		if (playerBottomLeft.x < vec.x * m_TileSize + m_TileSize && playerBottomLeft.y > vec.y* m_TileSize)
		{
			if (playerBottomRight.x > vec.x* m_TileSize&& playerBottomRight.y > vec.y* m_TileSize)
			{
				if (playerTopLeft.x < vec.x * m_TileSize + m_TileSize && playerTopLeft.y < vec.y* m_TileSize + m_TileSize)
				{
					if (playerTopRight.x > vec.x * m_TileSize && playerTopRight.y < vec.y * m_TileSize + m_TileSize)
					{
						collided = true;
					}
				}
			}
		}
		if (collided)
		{
			int verticalOffset = 2 * TILE_SIZE;
			rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * vec.x + vec.y * 4 + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * vec.x + vec.y * 4 + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * vec.x + vec.y * 4 + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * vec.x + vec.y * 4 + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			
			vec.x = -1;
			vec.y = -1;
			if (rLevel.getLockedDoors().size() > 0) 
			{
				Vector2f destroyedDoors = rLevel.getLockedDoors().back();
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
				rLevel.popLockedDoor();
			}
			else
			{
				//final door
				Vector2f destroyedDoors = rLevel.getFinalDoor();
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[(rVA.getBounds().height / TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
				rLevel.removeFinalDoor();

			}
			collided = false;
		}
	}

	if (playerBottomLeft.x < rLevel.getGoal().x * m_TileSize + m_TileSize && playerBottomLeft.y > rLevel.getGoal().y* m_TileSize)
	{
		if (playerBottomRight.x > rLevel.getGoal().x* m_TileSize&& playerBottomRight.y > rLevel.getGoal().y* m_TileSize)
		{
			if (playerTopLeft.x < rLevel.getGoal().x * m_TileSize + m_TileSize && playerTopLeft.y < rLevel.getGoal().y * m_TileSize + m_TileSize)
			{
				if (playerTopRight.x > rLevel.getGoal().x* m_TileSize&& playerTopRight.y < rLevel.getGoal().y * m_TileSize + m_TileSize)
				{
					m_victory = true;
				}
			}
		}
	}

}

bool Player::didPlayerWin()
{
	return m_victory;
}


