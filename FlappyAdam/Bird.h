#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

extern unsigned int resX;
extern unsigned int resY;
extern string directory;

class Bird :public Drawable
{
public:
	Bird(float x=resX/3.f, float y=resY/2.f);
	~Bird() = default;

	void update();//similar to other clases
	void restart(float x = resX / 3.f, float y = resY / 2.f);
	bool screenCollision();//true when bird fly out of the screen

	float left();//sides of object for detecting collisions
	float right();
	float up();
	float down();
private:
	float scaleX;
	float scaleY;
	float spriteWidth;
	float spriteHeight;
	Texture texture;
	IntRect sourceSprite;//stores rectangle of texture dimensions
	Sprite sprite;
	Clock clock;// clock for animation
	Vector2f startVelocity{ 0.f, resY / -72.f };
	Vector2f velocity{startVelocity};
	Vector2f gravity{ 0.f,resY/1800.f };//gravity acceleration
	void draw(RenderTarget& target, RenderStates state) const override;
};

