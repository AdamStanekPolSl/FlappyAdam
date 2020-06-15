#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

extern unsigned int resX;
extern unsigned int resY;
extern string directory;

class Pipe :public Drawable
{
public:
	Pipe(float x = resX, float y = resY, bool flipped=0);//flipped = true - sprite will be flipped by 180 degrees
	~Pipe() = default;

	void update();
	void restart(float x = resX, float y = resY);
	void gameOver();//resets velocity

	float left();//sides of pipe objects (for collision detecting)
	float right();
	float up();
	float down();

	void move();
private:
	float scaleX;
	float scaleY;
	float spriteWidth;//on screen Width and Height
	float spriteHeight;
	Texture texture;
	Sprite sprite;
	Vector2f startVelocity{ resX / -256.f, 0.f };
	Vector2f accelaration{ resX / 1280000.f , 0.f };//pipes are accelerating
	Vector2f velocity{ startVelocity };
	void draw(RenderTarget& target, RenderStates state) const override;
};
