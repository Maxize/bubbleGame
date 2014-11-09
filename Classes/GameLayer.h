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

	bool isCollisionWithBorder();	//�Ƿ�����ұ�Ե��ײ

	bool isCollisionWithTopBorder(Bubble *pBubble);	//�Ƿ�Ͷ����Ե��ײ��
	bool isCollisionWithBubble(Point pos1, float radius1, Point pos2, float radius2);	//�Ƿ���Ϸ�������ײ
	bool isCollision();	//�Ƿ���ײ���������Ƿ���Ϸ����е�����ײ�Ͷ����Ե��ײ�� �����������ұ�Ե��ײ

	void adjustBubblePosition();

	//������Ҫ�������ļ���
	ROWCOL_LIST findClearBubble(Bubble *pReadyBubble);
	//�ҵ�ͬ�����򣬲������ҵ���ͬ������ļ���
	ROWCOL_LIST findSameBubble(Bubble *pReadyBubble);
	//���ҽ���ɫ������Ӧ��Ҫ��������ļ���
	ROWCOL_LIST findGoldenBubble(Bubble *pReadyBubble);
	ROWCOL_LIST findSliveryBubble(Bubble* pReadyBubble);

	//���ݵ�����������λ�ú���ɫ���ͣ� ������Ӧ�Ĵ����磺����ɫ�������ݵı�ը����������
	void execClearBubble(Bubble* pReadyBubble);

	//�����ļ���
	void clearBubble(const ROWCOL_LIST &bubbleList);

	//���һ����ı��ֶ���
	void removeBubbleAction(Bubble* pBubble);
	void callbackRemoveBubble(Node *obj);

	ROWCOL_LIST checkFallBubble();
	//ִ�п��Ե��������
	void FallBubble(const ROWCOL_LIST &fallBubbleList);
	//��������
	void downBubbleAction(Bubble *pBubble);

	//��wait״̬���򻻳�ready״̬
	void changeWaitToReady();

	void setEnable();
	void setDisableEnable();

	inline bool hasBall(int row, int col)
	{
		return m_board[row][col] != NULL;
	}

private:
	Bubble* m_board[MAX_ROWS][MAX_COLS];		//������������ܷŵ�����

	Bubble* m_wait[MAX_WAIT_BUBBLE];			//���ڵȴ���������ݶ���

	Bubble* m_curReady;							//��ǰ��Ҫ���������

	BUBBLE_LIST m_listBubble;		//��ǰͼ�����е���

	double m_dRadian;						//��ΧΪ30��Ϊ150;Ĭ��Ϊ90�ȣ� ��ֱ����
	int m_nRotation;						//�������Ƕȸı䷽��Ҳ����ķ����Ƕ�

	int m_nWidth;			//��Ϸ����Ŀ�Ⱥ͸߶�
	int m_nHeight;

	int m_nScore;			//��Ϸ���õ��ķ���

	int m_nGoldenBubbleCount;
	int m_nSliveryBubbleCount;

	GameState m_state;

	Point m_real;
};
#endif