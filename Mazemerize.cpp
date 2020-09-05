#include <SFML/Graphics.hpp>
#include "Mazemerize.h"
#include <iostream>
#include "player.h"
#include "level.h"

using namespace sf;
int main() 
{

	//resolution
	Vector2f resolution;
	const int fpsCap = 60;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(VideoMode(resolution.x, resolution.y), "Mazemerize", Style::Fullscreen);
	window.setFramerateLimit(fpsCap);
	//sfml view 
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	//game stuff
	IntRect level;
	Player player;
	
	VertexArray world;
	Level levelData = createBackground(world);

	Texture textures;
	textures.loadFromFile("./resources/textures/textures.png");
	//time stuff
	Clock clock;
	Time gameTimeTotal;

	player.spawn(Vector2f(levelData.getPlayerSpawn().x * 50, levelData.getPlayerSpawn().y * 50));

	View victoryView(FloatRect(0, 0, resolution.x, resolution.y));
	Texture victoryTexture;
	victoryTexture.loadFromFile("./resources/textures/victory.png");
	Sprite victorySprite(victoryTexture);

	while (window.isOpen())
	{
		/*
		************
		HANDLE INPUT
		************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}
		if (!player.didPlayerWin())
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}
		/*
		****************
		UPDATE THE FRAME
		****************
		*/
		Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();
		player.update(dtAsSeconds, levelData, world);
		if (!player.didPlayerWin())
		{
			mainView.setCenter(player.getCenter());
		}
		/*
		**************
		DRAW THE SCENE
		**************
		*/
		window.clear();
		window.setView(mainView);
		if (!player.didPlayerWin())
		{
			window.draw(world, &textures);
			window.draw(player.getSprite());
		}
		else
		{
			window.setView(victoryView);
			window.draw(victorySprite);
		}
		window.display();
	}




	return 0;
}