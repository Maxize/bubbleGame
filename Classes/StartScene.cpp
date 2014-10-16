#include "StartScene.h"
#include "BubbleConstant.h"
#include "GameScene.h"

using namespace cocos2d;

StartLayer::StartLayer()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("main_music.mp3", true);
}

StartLayer::~StartLayer()
{
	
}

Scene* StartLayer::scene()
{
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StartLayer *layer = StartLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! Layer::init());

		Size winSize = Director::getInstance()->getWinSize();

		LabelTTF *label = LabelTTF::create("New Game", "Arial", 24 * 2);
		MenuItemLabel *pMenuItem = MenuItemLabel::create(label, this, menu_selector(StartLayer::menuNewGameCallback));
		pMenuItem->setTag(1);
		pMenuItem->setPosition(winSize.width / 2, winSize.height / 2);
		
        Menu* pMenu = Menu::create(pMenuItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 1);

        LabelTTF* pLabel = LabelTTF::create("Bubble Cat 2014", "Arial", 24 * 3);
        CC_BREAK_IF(! pLabel);
        pLabel->setPosition(ccp(winSize.width / 2, winSize.height - 50));
        this->addChild(pLabel, 1);

        Sprite* pSprite = Sprite::create("StartScene_CN.jpg");
        CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pSprite, 0);

        bRet = true;
    } while (0);

    return bRet;
}

void StartLayer::menuCloseCallback(Ref* pSender)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}

void StartLayer::menuNewGameCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::scene());
}

