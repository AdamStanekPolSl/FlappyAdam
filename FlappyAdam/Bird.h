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

	void update();
	void restart(float x = resX / 3.f, float y = resY / 2.f);
	bool screenCollision();

	float left();
	float right();
	float up();
	float down();
private:
	float scaleX;
	float scaleY;
	float spriteWidth;
	float spriteHeight;
	Texture texture;
	IntRect sourceSprite;
	Sprite sprite;
	Clock clock;
	Vector2f startVelocity{ 0.f, resY / -72.f };
	Vector2f velocity{startVelocity};
	Vector2f gravity{ 0.f,resY/1800.f };
	void draw(RenderTarget& target, RenderStates state) const override;
};

