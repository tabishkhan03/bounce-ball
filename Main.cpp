#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include<string>
#include "menu.h"

using namespace std;
using namespace sf;

void rungame();
void help();

int main()
{
	srand(time(NULL));
	//window creation
	RenderWindow window(VideoMode(1350, 600), "Bounce Ball", Style::Default);
	menu menu(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(580);
	//sound effect or menu
	SoundBuffer popsound;
	popsound.loadFromFile("sound/pop.wav");
	Sound pop;
	pop.setBuffer(popsound);
	//game loop
	while (window.isOpen())
	{
		Event event;


		//event polling
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				break;

			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.moveup();
					pop.play();
					break;
				case Keyboard::Down:
					menu.movedown();
					pop.play();
					break;
				case Keyboard::Return:
					switch (menu.getpresseditem())
					{
					case 0:
						rungame();
						break;
					case 1:
						help();
						break;
					case 2:
							window.close();
						break;
					}

				}
				break;
			}


		}
		//RENDER
		window.clear(Color(66, 150, 219, 200));
		menu.draw(window);
		window.display();
	}
	return 0;
}
void rungame()
{
	
	int jump = 1;

	srand(time(NULL));
	//window creation for game
	RenderWindow window(VideoMode(1350, 600), "Bounce Ball", Style::Default);
	window.setFramerateLimit(580);
	//ball
	

	CircleShape circle;
	circle.setFillColor(Color(255, 127, 80, 255));
	circle.setRadius(40.f);
	circle.setPosition(30.f, 253.f);

	Texture ball;
	ball.loadFromFile("Ball-Red-PNG-Clipart.png");
	circle.setTexture(&ball);
	ball.setSmooth(0);

	//ground
	vector<RectangleShape>grd;
	RectangleShape ground(Vector2f(100000.f, 50.f));
	ground.setFillColor(Color::Transparent);
	ground.setPosition(0.0f, 460.f);


	//Font
	Font font;
	font.loadFromFile("font/KdamThmorPro-Regular.ttf");
	Text lifetext;
	lifetext.setFont(font);
	lifetext.setCharacterSize(30);
	lifetext.setFillColor(Color::Green);
	lifetext.setString("LIFE");
	lifetext.setPosition(500.f, 0.f);

	//GAMEOVER FONT
	Text Gameover;
	Gameover.setFont(font);
	Gameover.setCharacterSize(100);
	Gameover.setFillColor(Color::Red);
	Gameover.setString("GAME OVER");
	Gameover.setPosition(400, 200);

	Text Gameoveresc;
	Gameoveresc.setFont(font);
	Gameoveresc.setCharacterSize(20);
	Gameoveresc.setFillColor(Color::Red);
	Gameoveresc.setString("Press Esc to exit");
	Gameoveresc.setPosition(400, 400);


	//OBSTACLE
	RectangleShape obstacle;

	obstacle.setSize(Vector2f(70.f, 60.f));
	obstacle.setFillColor(Color::Red);
	vector<RectangleShape> obstacles;
	obstacles.push_back(RectangleShape(obstacle));
	Texture spike;
	spike.loadFromFile("Font/spike2.png");
	obstacle.setTexture(&spike);
	spike.setSmooth(0);

	int obstaclespawn = 350;


	//HP BAR
	float hp = 10;
	RectangleShape hpbar;
	hpbar.setFillColor(Color::Green);
	hpbar.setSize(Vector2f(hp * 20.f, 20.f));
	hpbar.setPosition(600.f, 10.f);

	//SCORE
	int score = 0;
	Text scoretext;
	scoretext.setFont(font);
	scoretext.setCharacterSize(30);
	scoretext.setFillColor(Color::Green);
	scoretext.setString("SCORE:" + to_string(score));
	scoretext.setPosition(1000.f, 0.f);

	//SOUND EFFECTS
	SoundBuffer collision, gameover;

	collision.loadFromFile("sound/collisionsound.wav");
	gameover.loadFromFile("sound/gameoversound.wav");
	Sound collisionsound, gameoversound;
	collisionsound.setBuffer(collision);
	gameoversound.setBuffer(gameover);

	//BACKGROUND
	RectangleShape bg;
	bg.setSize(Vector2f(1350.f, 600));
	circle.setPosition(0.f, 0.f);

	Texture background;
	background.loadFromFile("bg.jpeg");
	bg.setTexture(&background);
	background.setSmooth(0);

	
	//game loop
	while (window.isOpen())
	{
		Event event;


		//event polling
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
			}

		}
		//PLAYER MOVEMENT
		Vector2f velocity;
		velocity.x = 0;
		velocity.y = 0;
		const float movementspeed = 1;
		const float jumpspeed = 10;
		const float gravity = 1;
		float jumph = 0;

		if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left) && circle.getPosition().x > 0)
		{
			velocity.x += -movementspeed;		//circle.move(-1.0f, 0.0f);
			circle.rotate(0.0f);
			//ground.move(1.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right) && circle.getPosition().x + circle.getGlobalBounds().height < window.getSize().x)
		{
			velocity.x += movementspeed;		//circle.move(1.0f, 0.0f);		
			circle.rotate(0.0f);
			//ground.move(-1.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up) && circle.getPosition().y > 1)
		{
			velocity.y += -gravity;			//velocity.y = -sqrtf(2.f * jumph);     
												//circle.move(0.0f, -1.0f);	
		}
		else if (circle.getPosition().y + circle.getScale().y < ground.getPosition().y - ground.getSize().y *1.5 )
		{

			velocity.y += gravity;				//velocity.y = sqrtf(2.f * jumph); 
												//circle.move(0.0f, 1.0f);
												//velocity.y += +jumpspeed;
		}
		/*if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down) && circle.getPosition().y + circle.getScale().y < ground.getPosition().y - ground.getSize().y * 1.5)
		{
			velocity.y += movementspeed;				//circle.move(0.0f, 1.0f);
			circle.rotate(0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up) && circle.getPosition().y > 0)
		{
			velocity.y += -movementspeed;				//circle.move(0.0f, -1.0f);
		}*/

		circle.move(velocity);

		//algorithm for obstalce spawning
		int n = 350;
		if (score == 5000)
		{
			n = 150;
		}
		if (obstaclespawn < n)
		{
			obstaclespawn++;
		}
		if (obstaclespawn >= n)
		{
			obstacle.setPosition(1300, (rand() % int(420)));
			obstacles.push_back(RectangleShape(obstacle));

			obstaclespawn = 0;
		}
		//scoring algorithm
		for (size_t i = 0; i < obstacles.size(); i++)
		{
			obstacles[i].move(-1.0f, 0.0f);
			if (obstacles[i].getPosition().x < obstacle.getGlobalBounds().width)
			{
				scoretext.setString("SCORE:" + to_string(score));
				score = score + 10;
				obstacles.erase(obstacles.begin() + i);
			}
			if (circle.getGlobalBounds().intersects(obstacles[i].getGlobalBounds()))
			{
				hp = hp - 1;
				collisionsound.play();
				hpbar.setSize(Vector2f(hp * 20.f, 20.f));
				obstacles.erase(obstacles.begin() + i);
			}
			if (hp == 0)
			{
				gameoversound.play();

				for (size_t i = 0; i < 1500; i++)
				{
					Gameover.setCharacterSize(100);
					window.draw(Gameover);
					window.draw(Gameoveresc);
					window.display();
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}
				
			}

		}
		

		//RENDER
		window.clear();
		window.draw(bg);
		window.draw(circle);
		window.draw(hpbar);
		window.draw(lifetext);
		window.draw(scoretext);


		window.draw(ground);
		for (size_t i = 0; i < obstacles.size(); i++)
		{
			window.draw(obstacles[i]);
		}
		

		window.display();
	}

}

//HELP 

void help()
{
	//Font
	Font font;
	font.loadFromFile("font/KdamThmorPro-Regular.ttf");
	Text Instruction,detailed_instruction;
	Instruction.setFont(font);
	Instruction.setCharacterSize(50);
	Instruction.setFillColor(Color::Green);
	Instruction.setString("Instruction");
	Instruction.setPosition(10.f, 0.f);

	detailed_instruction.setFont(font);
	detailed_instruction.setCharacterSize(30);
	detailed_instruction.setFillColor(Color::Green);
	detailed_instruction.setString("1)To move forward press right arrow key or D\n2)To move backward press left arrow key or A\n3)To jump press Up arrow key or W");
	detailed_instruction.setPosition(30.f, 50.f);

	//window
	RenderWindow window(VideoMode(1350, 600), "Bounce Ball", Style::Default);
	window.setFramerateLimit(580);

	//game loop
	while (window.isOpen())
	{
		Event event;


		//event polling
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
			}

		}
			//RENDER
			window.clear(Color(66, 150, 219, 255));
			window.draw(Instruction);
			window.draw(detailed_instruction);
			window.display();
		
	}

}