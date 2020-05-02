#include "Cloud.h"

Cloud::Cloud(float x, float y, int textureNumber)
{
	scaleX = resX / 4000.f * textureNumber;
	scaleY = resY / 2250.f * textureNumber;
	texture.loadFromFile(directory + "PNG/cloud"+to_string(textureNumber) +".png");
	sprite.setTexture(this->texture);
	sprite.setScale(this->scaleX, this->scaleY);
	spriteWidth = scaleX * texture.getSize().x;
	spriteHeight = scaleY * texture.getSize().y;
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(x + 0.5 * spriteWidth, y - 0.5 * spriteHeight);
}
float Cloud::right()
{
	return this->sprite.getPosition().x + 0.4 * spriteWidth;
}
void Cloud::update()
{
	sprite.move(this->startVelocity);
}
void Cloud::restart(float x, float y, int textureNumber)
{
	this->startVelocity.x = -scaleX * textureNumber;
	texture.loadFromFile(directory + "PNG/cloud" + to_string(textureNumber) + ".png");
	sprite.setTexture(this->texture);
	this->sprite.setPosition(x + 0.5 * spriteWidth, y - 0.5 * spriteHeight);
}
void Cloud::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}
void Cloud::move()
{
	this->sprite.move(0.5 * spriteWidth, 0);
}