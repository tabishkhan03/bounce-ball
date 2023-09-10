#pragma once
#include<SFML/Graphics.hpp>
#define max_items 3
using namespace sf;
class menu
{
public:
	menu(float width, float height);
	~menu();

	void draw(RenderWindow &window);
	void moveup();
	void movedown();
	int getpresseditem() { return selecteditem; }
private:
	int selecteditem;
	Font font1;
	Text menutext[max_items];
	RectangleShape menuspike1, menuspike2, menuspike3, menuspike4, menutextbg[max_items];
};