#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

extern unsigned int resX;
extern unsigned int resY;
extern string directory;

class Cloud:public Drawable
{
public:
	Cloud(float x = resX, float y = resY, int textureNumber=1);
	~Cloud() = default;

	void update();//include move() function
	void restart(float x = resX, float y = resY, int textureNumber=1);//moves cloud to new starting position

	float right();//returns right side of cloud

	void move();//moves cloud
private:
	float scaleX;
	float scaleY;
	float spriteWidth;
	float spriteHeight;
	Texture texture;
	Sprite sprite;
	Vector2f startVelocity{};
	void draw(RenderTarget & target, RenderStates state) const override;//draws object in render target (window)
};

