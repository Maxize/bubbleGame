/************************************************************************/
/* 
**  Date   :   2013/9/21

** author  :   Bright Moon

** blog :  
** CSDN: http://blog.csdn.net/chenhaobright
** github: https://github.com/chenhaobright

** function:   ��Ϸ�����߼���ȫ�����ڴ�ģ���У� ��Ҫ������
			   1����Ϸ���ݺ͵ȴ���������ݳ�ʼ��
			   2����Ϸ�����Ŀ��غʹ���
			   3�����ݵ���ײ���ʹ����������ݵ�λ�ã�
			   4����ײ�������ͬ���ݵ��㷨
			   5�����ݵ�����
			   6���������Ƿ����������ݵļ��
*/
/************************************************************************/

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
};
#endif
