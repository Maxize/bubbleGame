#include "GameOverLayer.h"

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	auto gameOverLabel = Label::createWithSystemFont("Game over!", "Arital", 48);
	gameOverLabel->setPosition(size.width/2, size.height/2);
	this->addChild(gameOverLabel);
	return true;
}