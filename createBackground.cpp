#include "Mazemerize.h"



Level createBackground(VertexArray& rVA)
{

	
	//level data
	Image levelData;
	levelData.loadFromFile("./resources/textures/level.png");
	/*
	------------LEVEL DETAILS------------
	| BLACK (#000000) - WALL			|
	| WHITE (#FFFFFF) - NOTHING			|
	| GRAY (#777777) - PATH				|
	| RED (#FF0000) - CHEST				|
	| BLUE (#0000FF) - LOCKED DOOR		|
	| YELLOW (#FFFF00) - FINAL DOOR		|
	| GREEN (#00FF00) - GOAL			|
	| PINK (#FF00FF) - PLAYER START		|
	-------------------------------------
	*/

	//map data vars
	const Color wall(0, 0, 0);
	const Color nothing(255, 255, 255);
	const Color path(119, 119, 119);
	const Color chest(255, 0, 0);
	const Color lockedDoor(0, 0, 255);
	const Color finalDoor(255, 255, 0);
	const Color goal(0, 255, 0);
	const Color playerStart(255, 0, 255);

	const int TILE_SIZE = 50;
	const int TILE_TYPES = 6;
	const int VERTS_IN_QUAD = 4;
	Vector2f v_playerStart;
	std::vector<Vector2f> v_walls;
	std::vector<Vector2f> v_chests;
	std::vector<Vector2f> v_lockedDoors;
	Vector2f v_finalDoor;
	Vector2f v_goal;

	rVA.setPrimitiveType(Quads);
	rVA.resize(levelData.getSize().x * levelData.getSize().y * VERTS_IN_QUAD);
	int currentVertex = 0;

	for (int w = 0; w < levelData.getSize().x; w++)
	{
		for (int h = 0; h < levelData.getSize().y; h++)
		{
			//get the current level data pixel
			Color pixel = levelData.getPixel(w, h);

			//pos each vertex in current quad
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);


			//define pos in texture to draw for current quad
			//wall
			if (pixel == nothing)
			{
			int verticalOffset = 0 * TILE_SIZE;
			rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}
			else if (pixel == wall)
			{
				v_walls.push_back(Vector2f(w, h));
				int verticalOffset = 1 * TILE_SIZE;
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}
			
			else if(pixel == path)
			{
				int verticalOffset = 2 * TILE_SIZE;
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}
			else if (pixel == chest)
			{
				v_chests.push_back(Vector2f(w, h));
				int verticalOffset = 3 * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}
			else if (pixel == lockedDoor)
			{

				v_lockedDoors.push_back(Vector2f(w, h));
				int verticalOffset = 4 * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}
			else if (pixel == finalDoor)
			{
				v_finalDoor = Vector2f(w, h);
				int verticalOffset = 5 * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}
			else if (pixel == goal)
			{
				v_goal = Vector2f(w, h);
				int verticalOffset = 6 * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}
			else if(pixel == playerStart)
			{
				v_playerStart = Vector2f(w, h);
				int verticalOffset = 2 * TILE_SIZE;
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}
			//pos ready for next vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	//delete first locked door (for testing & semantics of the game)
	int verticalOffset = 2 * TILE_SIZE;
	Vector2f destroyedDoors = v_lockedDoors.back();
	v_lockedDoors.pop_back();
	rVA[(rVA.getBounds().height/TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 0].texCoords = Vector2f(0, 0 + verticalOffset);
	rVA[(rVA.getBounds().height/TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
	rVA[(rVA.getBounds().height/TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
	rVA[(rVA.getBounds().height/TILE_SIZE) * 4 * destroyedDoors.x + destroyedDoors.y * 4 + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

	return Level(v_playerStart,v_walls, v_chests, v_lockedDoors, v_finalDoor, v_goal);
}