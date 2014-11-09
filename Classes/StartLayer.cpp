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
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	LabelTTF* pLabel = LabelTTF::create("Bubble Cat 2014", "Arial", 24 * 3);
	pLabel->setPosition(ccp(winSize.width / 2, winSize.height - 50));
	this->addChild(pLabel, 1);

	Sprite* pSprite = Sprite::create("StartScene_CN.jpg");
	pSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
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
