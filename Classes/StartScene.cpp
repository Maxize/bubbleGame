#include "StartScene.h"
#include "StartLayer.h"
#include "BubbleConstant.h"
#include "GameScene.h"

using namespace CocosDenshion;
bool StartScene::init()
{
	if (!Scene::init()){
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("main_music.mp3", true);

	this->addChild(StartLayer::create());
	return true;
}



