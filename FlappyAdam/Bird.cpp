#include "Bird.h"


Bird::Bird(float x, float y)
{
	scaleX = resX / 8000.f;
	scaleY = resY / 4500.f;
	texture.loadFromFile(directory + "PNG/bird.png");
	sprite.setTexture(this->texture);
	sprite.setScale(this->scaleX, this->scaleY);
	spriteWidth = (texture.getSize().x / 4);
	spriteHeight = texture.getSize().y;
	sourceSprite.width = spriteWidth;
	sourceSprite.height = spriteHeight;
	sprite.setTextureRect(sourceSprite);
	sprite.setPosition(x-(scaleX*spriteWidth/2.f), y-(scaleY*spriteHeight/2.f));
}
void Bird::update()
{
	this->velocity += this->gravity;
	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
	{
		if (clock.getElapsedTime().asMilliseconds() > 15.f)//animation
		{
			if (sourceSprite.left >= 3 * spriteWidth)
				sourceSprite.left = 0;
			else
				sourceSprite.left += spriteWidth;
			clock.restart();
		}
		velocity.y = -static_cast<int>(resY) / 72.f;
	}
	else
		sourceSprite.left = 0;//no animation
	sprite.setTextureRect(this->sourceSprite);
	sprite.move(this->velocity);
}
bool Bird::screenCollision()
{
	if (this->down() >= resY)
		return true;
	if (this->up() <= 0)
		return true;
	return false;
}
float Bird::left()
{
	return this->sprite.getPosition().x;
}
float Bird::right()
{
	return this->sprite.getPosition().x + sprite.getGlobalBounds().width;
}
float Bird::up()
{
	return this->sprite.getPosition().y;
}
float Bird::down()
{
	return this->sprite.getPosition().y+ sprite.getGlobalBounds().height;
}
void Bird::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}
void Bird::restart(float x, float y)
{
	this->velocity = this->startVelocity;
	sprite.setPosition(x - (scaleX * spriteWidth / 2.f), y - (scaleY * spriteHeight / 2.f));
}