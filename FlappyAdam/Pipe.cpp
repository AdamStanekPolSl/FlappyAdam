#include "Pipe.h"

Pipe::Pipe(float x, float y, bool flipped)
{
	scaleX = resX / 8000.f;
	scaleY = resY / 4500.f;
	texture.loadFromFile(directory + "PNG/pipe.png");
	sprite.setTexture(this->texture);
	sprite.setScale(this->scaleX, this->scaleY);
	spriteWidth = scaleX * texture.getSize().x;
	spriteHeight = scaleY * texture.getSize().y;
	sprite.setOrigin(texture.getSize().x/ 2.f, texture.getSize().y/2.f);
	sprite.setRotation(flipped * 180);
	sprite.setPosition(x+0.5*spriteWidth, y-0.5*spriteHeight);
}
float Pipe::left()
{
	return this->sprite.getPosition().x-0.4*spriteWidth;
}
float Pipe::right()
{
	return this->sprite.getPosition().x + 0.4*spriteWidth;
}
float Pipe::up()
{
	return this->sprite.getPosition().y - 0.45 * spriteHeight;
}
float Pipe::down()
{
	return this->sprite.getPosition().y + 0.47*spriteHeight;
}
void Pipe::update()
{
	this->velocity -= this->accelaration;
	sprite.move(this->velocity);
}
void Pipe::restart(float x, float y)
{
	this->sprite.setPosition(x+0.5*spriteWidth, y-0.5*spriteHeight);
}
void Pipe::gameOver()
{
	this->velocity.x = resX / -256.f;
}
void Pipe::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}
void Pipe::move()
{
	this->sprite.move(0.5*spriteWidth, 0);
}