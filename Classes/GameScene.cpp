#include "GameScene.h"
#include "GameLayer.h"



bool GameScene::init(){
	if (!Scene::init()){
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game_scene_bg.mp3", true);
	SimpleAudioEngine::getInstance()->playEffect("ready_go.mp3");

	this->addChild(GameLayer::create());
	return true;
}

