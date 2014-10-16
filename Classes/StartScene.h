#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class StartLayer : public cocos2d::Layer
{
public:

	StartLayer();
	~StartLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
	void menuCloseCallback(Ref* pSender);

	void menuNewGameCallback(Ref* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StartLayer);
};

#endif  // __HELLOWORLD_SCENE_H__