#include "StartLayer.h"
#include "GameScene.h"

bool StartLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto label = Label::create("New Game", "Arial", 24 * 2);
	MenuItemLabel *pMenuItem = MenuItemLabel::create(label, this, menu_selector(StartLayer::menuNewGameCallback));
	pMenuItem->setTag(1);
	pMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	Menu* pMenu = Menu::create(pMenuItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);

	auto pLabel = Label::create("Bubble Cat 2014", "Arial", 24 * 3);
	pLabel->setPosition(visibleSize.width / 2, visibleSize.height - 50);

	this->addChild(pLabel, 1);

	Sprite* pSprite = Sprite::create("StartScene_CN.jpg");
	pSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
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
