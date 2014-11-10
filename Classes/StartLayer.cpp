#include "StartLayer.h"
#include "GameScene.h"

bool StartLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();

	LabelTTF *label = LabelTTF::create("New Game", "Arial", 24 * 2);
	MenuItemLabel *pMenuItem = MenuItemLabel::create(label, this, menu_selector(StartLayer::menuNewGameCallback));
	pMenuItem->setTag(1);
	pMenuItem->setPosition(winSize.width / 2, winSize.height / 2);

	Menu* pMenu = Menu::create(pMenuItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);

	LabelTTF* pLabel = LabelTTF::create("Bubble Cat 2014", "Arial", 24 * 3);
	Point labelPoint = Point(winSize.width / 2, winSize.height - 50);
	pLabel->setPosition(labelPoint);
	CCLOG("labelPoint x = %f, y = %f", labelPoint.x, labelPoint.y);

	this->addChild(pLabel, 1);

	Sprite* pSprite = Sprite::create("StartScene_CN.jpg");
	pSprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(pSprite, 0);
	return true;
}

void StartLayer::menuCloseCallback(Ref* pSender)
{
	// "close" menu item clicked
	Director::getInstance()->end();
}

void StartLayer::menuNewGameCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::create());
}
