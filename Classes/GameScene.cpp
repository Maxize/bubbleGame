#include "GameScene.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool GameScene::init(){
	if (!Scene::init()){
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game_scene_bg.mp3", true);
	SimpleAudioEngine::getInstance()->playEffect("ready_go.mp3");

	this->addChild(GameLayer::create());
	return true;
}

