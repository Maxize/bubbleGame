#ifndef _STARTLAYER_H_
#define _STARTLAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class StartLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(StartLayer);

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	void menuNewGameCallback(Ref* pSender);
};
#endif