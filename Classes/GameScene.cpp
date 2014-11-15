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
	Size size = Director::getInstance()->getVisibleSize();
	/*m_gameOverLayer = createGameOverLayer();
	if (m_gameOverLayer)
	{
		m_gameOverLayer->setContentSize(size);
		this->addChild(m_gameOverLayer);
		m_gameLayer->setVisible(false);
	}*/

	m_gameLayer = GameLayer::create();
	if (m_gameLayer)
	{
		m_gameLayer->setContentSize(size);
		this->addChild(m_gameLayer);
	}

	return true;
}

GameOverLayer* GameScene::createGameOverLayer()
{
	return GameOverLayer::create();

}

