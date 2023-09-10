#include "menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
menu::menu(float width, float height)
{
	if (!font1.loadFromFile("font/KdamThmorPro-Regular.ttf"))
	{
		//error
	}
	menutext[0].setFont(font1);
	menutext[0].setCharacterSize(50);
	menutext[0].setFillColor(Color::Green);
	menutext[0].setString("PLAY");
	menutext[0].setPosition(width/2, height/(max_items+1)*1);

	menutext[1].setFont(font1);
	menutext[1].setCharacterSize(30);
	menutext[1].setFillColor(Color::White);
	menutext[1].setString("Help");
	menutext[1].setPosition(width / 2, height / (max_items + 1) * 2);

	menutext[2].setFont(font1);
	menutext[2].setCharacterSize(30);
	menutext[2].setFillColor(Color::White);
	menutext[2].setString("Quit");
	menutext[2].setPosition(width / 2, height / (max_items + 1) * 3);
	selecteditem = 0;

	menutextbg[0].setSize(Vector2f(150.f, 70.f));
	menutextbg[0].setFillColor(Color::Transparent);
	menutextbg[0].setOutlineThickness(2.f);
	menutextbg[0].setOutlineColor(Color::White);
	menutextbg[0].setPosition(width / 2, height / (max_items + 1) * 1);

	menutextbg[1].setSize(Vector2f(120.f, 50.f));
	menutextbg[1].setFillColor(Color::Transparent);
	menutextbg[1].setOutlineThickness(2.f);
	menutextbg[1].setOutlineColor(Color::Green);
	menutextbg[1].setPosition(width / 2, height / (max_items + 1) * 2);

	menutextbg[2].setSize(Vector2f(120.f, 50.f));
	menutextbg[2].setFillColor(Color::Transparent);
	menutextbg[2].setOutlineThickness(2.f);
	menutextbg[2].setOutlineColor(Color::Green);
	menutextbg[2].setPosition(width / 2, height / (max_items + 1) * 3);

	
}

menu::~menu()
{

}

void menu::draw(RenderWindow& window)
{
	menuspike1.setSize(Vector2f(50.f, 50.f));
	menuspike1.setFillColor(Color::Red);
	menuspike1.setPosition(0, 0);
	Texture spikes1;
	spikes1.loadFromFile("font/spike3.png");
	menuspike1.setTexture(&spikes1);
	spikes1.setSmooth(0);

	menuspike2.setSize(Vector2f(50.f, 50.f));
	menuspike2.setFillColor(Color::Red);
	menuspike2.setPosition(0, 0);
	Texture spikes2;
	spikes2.loadFromFile("font/spike2.png");
	menuspike2.setTexture(&spikes2);
	spikes2.setSmooth(0);

	menuspike3.setSize(Vector2f(50.f, 50.f));
	menuspike3.setFillColor(Color::Red);
	menuspike3.setPosition(0, 0);
	Texture spikes3;
	spikes3.loadFromFile("font/spike1.png");
	menuspike3.setTexture(&spikes3);
	spikes3.setSmooth(0);

	menuspike4.setSize(Vector2f(50.f, 50.f));
	menuspike4.setFillColor(Color::Red);
	menuspike4.setPosition(0, 0);
	Texture spikes4;
	spikes4.loadFromFile("font/spike4.png");
	menuspike4.setTexture(&spikes4);
	spikes4.setSmooth(0);
	for (int i = 0; i < max_items; i++)
	{
		window.draw(menutextbg[i]);
		window.draw(menutext[i]);
	}
	for (int i = 0; i < 1350; i = i + 50)
	{
		menuspike1.setPosition(i,0);
		window.draw(menuspike1);
	}
	for (int j = 50; j < 550; j = j + 50)
	{
		menuspike2.setPosition(1300, j);
		window.draw(menuspike2);
	}
	for (int i = 0; i < 1350; i = i + 50)
	{
		menuspike3.setPosition(i, 550);
		window.draw(menuspike3);
	}
	for (int j = 50; j < 550; j = j + 50)
	{
		menuspike4.setPosition(0, j);
		window.draw(menuspike4);
	}
}

void menu::moveup()
{
	if (selecteditem -1>=0)
	{
		menutext[selecteditem].setFillColor(Color::White);
		menutext[selecteditem].setCharacterSize(30);
		menutextbg[selecteditem].setSize(Vector2f(120.f, 50.f));
		menutextbg[selecteditem].setOutlineThickness(2.f);
		menutextbg[selecteditem].setOutlineColor(Color::Green);
		selecteditem--;
		menutext[selecteditem].setFillColor(Color::Green);
		menutext[selecteditem].setCharacterSize(50);
		menutextbg[selecteditem].setSize(Vector2f(150.f, 70.f));
		menutextbg[selecteditem].setOutlineThickness(2.f);
		menutextbg[selecteditem].setOutlineColor(Color::White);
	}
}

void menu::movedown()
{
	if (selecteditem + 1 < max_items)
	{
		menutext[selecteditem].setFillColor(Color::White);
		menutext[selecteditem].setCharacterSize(30);
		menutextbg[selecteditem].setSize(Vector2f(120.f, 50.f));
		menutextbg[selecteditem].setOutlineThickness(2.f);
		menutextbg[selecteditem].setOutlineColor(Color::Green);
		selecteditem++;
		menutext[selecteditem].setFillColor(Color::Green);
		menutext[selecteditem].setCharacterSize(50);
		menutextbg[selecteditem].setSize(Vector2f(150.f, 70.f));
		menutextbg[selecteditem].setOutlineThickness(2.f);
		menutextbg[selecteditem].setOutlineColor(Color::White);
	}
}