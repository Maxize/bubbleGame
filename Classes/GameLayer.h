#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
#include "Bubble.h"
#include "BubbleConstant.h"

#include <list>
#include <vector>

using namespace cocos2d;

typedef std::list<Bubble*> BUBBLE_LIST;
typedef std::list<RowCol>  ROWCOL_LIST;

class GameLayer : public Layer{
public:

	GameLayer();
	~GameLayer();

public:
	virtual bool init();
	CREATE_FUNC(GameLayer);

	void loop(float);
	void update(float);

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);

private:
	Bubble* randomBubble();
	Bubble* createBubble(BUBBLE_COLOR color);

	void clear();

	bool initScheduler();
	bool initReadyBubble();
	bool initBoard();
	bool initWaitBubble();

	bool isCollisionWithBorder();	//是否和左右边缘碰撞

	bool isCollisionWithTopBorder(Bubble *pBubble);	//是否和顶层边缘碰撞，
	bool isCollisionWithBubble(Point pos1, float radius1, Point pos2, float radius2);	//是否和上方的球碰撞
	bool isCollision();	//是否碰撞，仅包括是否和上方所有的球碰撞和顶层边缘碰撞， 不包括和左右边缘碰撞

	void adjustBubblePosition();

	//查找需要清除的球的集合
	ROWCOL_LIST findClearBubble(Bubble *pReadyBubble);
	//找到同样的球，并返回找到的同样的球的集合
	ROWCOL_LIST findSameBubble(Bubble *pReadyBubble);
	//查找金银色球所对应的要消除的球的集合
	ROWCOL_LIST findGoldenBubble(Bubble *pReadyBubble);
	ROWCOL_LIST findSliveryBubble(Bubble* pReadyBubble);

	//根据调整过后的球的位置和颜色类型， 作出相应的处理，如：金银色特殊泡泡的爆炸，球的下落等
	void execClearBubble(Bubble* pReadyBubble);

	//清除球的集合
	void clearBubble(const ROWCOL_LIST &bubbleList);

	//清除一个球的表现动作
	void removeBubbleAction(Bubble* pBubble);
	void callbackRemoveBubble(Node *obj);

	ROWCOL_LIST checkFallBubble();
	//执行可以掉落的泡泡
	void FallBubble(const ROWCOL_LIST &fallBubbleList);
	//掉落泡泡
	void downBubbleAction(Bubble *pBubble);

	//将wait状态的球换成ready状态
	void changeWaitToReady();

	void setEnable();
	void setDisableEnable();

	inline bool hasBall(int row, int col)
	{
		return m_board[row][col] != NULL;
	}

private:
	Bubble* m_board[MAX_ROWS][MAX_COLS];		//整个面板所有能放的泡泡

	Bubble* m_wait[MAX_WAIT_BUBBLE];			//正在等待发射的泡泡队列

	Bubble* m_curReady;							//当前正要发射的泡泡

	BUBBLE_LIST m_listBubble;		//当前图上所有的球

	double m_dRadian;						//范围为30度为150;默认为90度， 竖直方向
	int m_nRotation;						//发射器角度改变方向，也是玩的反弹角度

	int m_nWidth;			//游戏界面的宽度和高度
	int m_nHeight;

	int m_nScore;			//游戏所得到的分数

	int m_nGoldenBubbleCount;
	int m_nSliveryBubbleCount;

	GameState m_state;

	Point m_real;
};
#endif