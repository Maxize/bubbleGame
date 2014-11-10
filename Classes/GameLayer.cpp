#include "GameLayer.h"
#include "Utility.h"

#include <algorithm>

GameLayer::GameLayer() :
m_state(GS_START),
m_nGoldenBubbleCount(0),
m_nSliveryBubbleCount(0),
m_nScore(0)
{
	CCLOG("-------------  GameLayer is ctor!");
}

GameLayer::~GameLayer()
{
	//clear();
}

bool GameLayer::init()
{
	srand(time(NULL));

	//加载背景
	Sprite *background = Sprite::create("background1.jpg");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background);

	initScheduler();
	initBoard();

	initReadyBubble();
	initWaitBubble();

	this->setEnable();
	return true;
}

bool GameLayer::initScheduler()
{
	//this->schedule(schedule_selector(GameLayer::loop), 1.0f);
	//this->scheduleUpdate();
	return true;
}

//初始化泡泡队列，
bool GameLayer::initBoard()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS - row % 2; col++)
		{
			//初始化前INIT_LINE行， 其他行为NULL
			if (row >= INIT_LINE)
			{
				m_board[row][col] = NULL;
				continue;
			}

			Bubble* pBubble = randomBubble();
			if (pBubble == NULL)
			{
				CC_BREAK_IF(!pBubble);
			}

			// 
			Point point = getPosByRowAndCol(row, col);
			//pBubble->setPosition(point.x, point.y);
			//pBubble->convertToWorldSpace(pBubble->getPosition());
			pBubble->setPosition(100, 200);
			//CCLOG(" point.x = %f, point.y = %f", point.x, point.y);

			this->addChild(pBubble);

			m_board[row][col] = pBubble;
			m_board[row][col]->setRowColIndex(row, col);
			m_listBubble.push_back(pBubble);

		}
	}
	return true;
}

//初如化泡泡发射器
bool GameLayer::initReadyBubble()
{
	m_curReady = randomBubble();

	Size size = Director::getInstance()->getWinSize();
	m_curReady->setPosition(Point(size.width / 2, size.height / 10));
	CCLOG("   curReady   point x = %f, point y = %f", m_curReady->getPosition().x, m_curReady->getPosition().y);
	this->addChild(m_curReady);
	return true;
}

bool GameLayer::initWaitBubble()
{
	for (int i = 0; i < MAX_WAIT_BUBBLE; i++)
	{
		Bubble *pBubble = randomBubble();
		Size size = Director::getInstance()->getWinSize();
		pBubble->setPosition(Point(size.width / 2 + (i + 1) * BUBBLE_RADIUS * 2, size.height / 20));
		m_wait[i] = pBubble;
		this->addChild(pBubble);

	}
	return true;

}
Bubble* GameLayer::randomBubble()
{
	BUBBLE_COLOR color = static_cast<BUBBLE_COLOR>(rand() % (COLOR_COUNT/* - 2*/));
	Bubble *pBubble = Bubble::create(g_bubbleName[color].c_str());
	if (pBubble)
	{
		pBubble->setBubbleColor(color);
	}
	else
	{
		CC_SAFE_DELETE(pBubble);
	}
	return pBubble;

}

Bubble* GameLayer::createBubble(BUBBLE_COLOR color)
{
	Bubble *pBubble = Bubble::create(g_bubbleName[color].c_str());
	if (pBubble)
	{
		pBubble->setBubbleColor(color);
	}
	else
	{
		CC_SAFE_DELETE(pBubble);
	}
	return pBubble;

}

void GameLayer::clear()
{
	for (int nRow = 0; nRow < MAX_ROWS; nRow++)
	{
		for (int nCol = 0; nCol < MAX_COLS - nRow % 2; nCol++)
		{
			CC_SAFE_DELETE(m_board[nRow][nCol]);
		}
	}

	m_listBubble.clear();
}

bool GameLayer::isCollisionWithBorder()	//是否和边缘碰撞
{
	Size size = Director::getInstance()->getWinSize();
	Point pos = m_curReady->getPosition();

	if (pos.x < BUBBLE_RADIUS || pos.x > size.width - BUBBLE_RADIUS)
	{
		return true;
	}

	return false;
}

bool GameLayer::isCollisionWithTopBorder(Bubble *pBubble)
{
	if (pBubble == NULL)
	{
		return false;
	}

	Point pos = pBubble->getPosition();
	Size size = Director::getInstance()->getWinSize();
	if (pos.y > size.height - BUBBLE_RADIUS)
	{
		return true;
	}

	return false;

}

bool GameLayer::isCollisionWithBubble(Point pos1, float radius1, Point pos2, float radius2)	//是否和上方的球碰撞
{
	return pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) < pow(radius1 + radius2, 2);	//判断两圆是否相交, 公式：（x1-x2)^2 + (y1-y2)^2 < (r1 + r2)^2
}

bool GameLayer::isCollision()
{
	bool bRet = false;

	Size size = Director::getInstance()->getWinSize();
	if (m_curReady->getPosition().y > size.height - BUBBLE_RADIUS)
	{
		bRet = true;
		return bRet;
	}

	for (BUBBLE_LIST::reverse_iterator iterBubble = m_listBubble.rbegin(); iterBubble != m_listBubble.rend(); ++iterBubble)
	{
		Bubble *pBubble = *iterBubble;
		if (pBubble && isCollisionWithBubble(pBubble->getPosition(), BUBBLE_RADIUS, m_curReady->getPosition(), BUBBLE_RADIUS))
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;

}

void GameLayer::setEnable()
{
	//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLayer::setDisableEnable()
{
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	//Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
}

bool GameLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void GameLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void GameLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	m_state = GS_FLY;

	Point pos = pTouch->getLocation();
	pos.subtract(m_curReady->getPosition());
	pos.normalize();
	m_real = pos;

	setDisableEnable();
	this->scheduleUpdate();
}

void GameLayer::loop(float dt)
{

}

void GameLayer::update(float delta)
{
	//CCLOG("GameLayer is update all the time! ---------------");

	if (isCollisionWithBorder())
	{
		m_real.x = -m_real.x;
	}

	Point pos = m_curReady->getPosition();
	m_curReady->setPosition(Vec2(pos.x + m_real.x * BUBBLE_SPEED, pos.y + m_real.y * BUBBLE_SPEED));

	if (isCollision())	//如果和球或者上边缘碰撞了， 做相应的处理
	{
		m_real = Vec2::ZERO;
		adjustBubblePosition();

		//根据同样的球数量作出相应的清理处理
		execClearBubble(m_curReady);

		//清除球之后，掉落处于悬挂状态的球
		ROWCOL_LIST fallList = checkFallBubble();
		FallBubble(fallList);

		this->unscheduleUpdate();
		changeWaitToReady();
		setEnable();
	}

}

void GameLayer::adjustBubblePosition()
{
	Point curPos = m_curReady->getPosition();

	RowCol rowcol_index = GetRowColByPos(curPos.x, curPos.y);

	Point adjustPos = getPosByRowAndCol(rowcol_index.m_nRow, rowcol_index.m_nCol);
	m_curReady->setPosition(adjustPos);
	m_curReady->setRowColIndex(rowcol_index.m_nRow, rowcol_index.m_nCol);

	m_board[rowcol_index.m_nRow][rowcol_index.m_nCol] = m_curReady;
	m_listBubble.push_back(m_curReady);
}

//将wait状态的球换成ready状态
void GameLayer::changeWaitToReady()
{
	m_curReady = m_wait[0];
	m_curReady->setPosition(READY_BUBBLE_POS);

	Size size = Director::getInstance()->getWinSize();

	for (int index = 0; index < MAX_WAIT_BUBBLE - 1; index++)
	{
		m_wait[index] = m_wait[index + 1];
		m_wait[index]->setPosition(Point(size.width / 2 + (index + 1) * BUBBLE_RADIUS * 2, size.height / 20));
	}

	m_wait[MAX_WAIT_BUBBLE - 1] = randomBubble();
	m_wait[MAX_WAIT_BUBBLE - 1]->setPosition(Point(size.width / 2 + MAX_WAIT_BUBBLE * BUBBLE_RADIUS * 2, size.height / 20));

	this->addChild(m_wait[MAX_WAIT_BUBBLE - 1]);
}

ROWCOL_LIST GameLayer::findClearBubble(Bubble *pReadyBubble)
{
	ROWCOL_LIST clearRowCollist;
	if (pReadyBubble == NULL)
	{
		return clearRowCollist;
	}

	if (pReadyBubble->getBubbleColor() == BUBBLE_GOLDEN)
	{
		clearRowCollist = findGoldenBubble(pReadyBubble);
	}
	else if (pReadyBubble->getBubbleColor() == BUBBLE_SILVERY)
	{
		clearRowCollist = findSliveryBubble(pReadyBubble);
	}
	else if (pReadyBubble->getBubbleColor() == COLOR_COUNT)
	{
		return clearRowCollist;
	}
	else
	{
		clearRowCollist = findSameBubble(pReadyBubble);
		if (clearRowCollist.size() < REMOVE_COUNT)
		{
			clearRowCollist.clear();
		}
	}

	return clearRowCollist;
}

ROWCOL_LIST GameLayer::findSameBubble(Bubble *pReadyBubble)
{
	ROWCOL_LIST samelist;
	BUBBLE_COLOR nColor = pReadyBubble->getBubbleColor();
	int nRow = pReadyBubble->getRowIndex();
	int nCol = pReadyBubble->getColumnIndex();
	samelist.push_back(RowCol(nRow, nCol));

	ROWCOL_LIST::iterator itCur = samelist.begin();

	//循环查找同样的球
	do
	{
		std::vector<RowCol> vecRowCol;

		GetAround(itCur->m_nRow, itCur->m_nCol, vecRowCol);

		for (size_t i = 0; i < vecRowCol.size(); i++)
		{
			Bubble* pCurBubble = m_board[vecRowCol[i].m_nRow][vecRowCol[i].m_nCol];
			if (pCurBubble && pCurBubble->getBubbleColor() == nColor)
			{
				RowCol rc(vecRowCol[i].m_nRow, vecRowCol[i].m_nCol);
				ROWCOL_LIST::iterator itFind = std::find(samelist.begin(), samelist.end(), rc);
				//查找是否已经在列表中
				if (itFind == samelist.end())
				{
					samelist.push_back(vecRowCol[i]);
				}
			}
		}
		itCur++;
	} while (itCur != samelist.end());

	return samelist;
}

//查找金色泡泡消除的球集合
ROWCOL_LIST GameLayer::findGoldenBubble(Bubble *pReadyBubble)
{
	int nRow = pReadyBubble->getRowIndex();
	int nCol = pReadyBubble->getColumnIndex();

	ROWCOL_LIST clearGoldenList;
	GetGoldenLine(nRow, nCol, clearGoldenList);

	return clearGoldenList;
}

//查找银色泡泡消除的球集合
ROWCOL_LIST GameLayer::findSliveryBubble(Bubble* pReadyBubble)
{
	int nRow = pReadyBubble->getRowIndex();
	int nCol = pReadyBubble->getColumnIndex();

	ROWCOL_LIST clearSliveryList;
	GetSliveryLine(nRow, nCol, clearSliveryList);

	return clearSliveryList;

}

/************************************************************************/
/* params: 发射后已经调整好位置的球
** NOTE  : 这是一个相当重要的函数，游戏的核心功能都在这个执行清理泡泡函数中，主要执行以下功能
1、如果消除泡泡数量达到GOLDEN_COUNT个，就执行金色泡泡的效果
2、同理，达到SLIVERY_COUNT个， 就执行银色泡泡效果
3、达到3个，小于SLIVERY_COUNT个，消除同样的球
4、小于3个，什么都不做
*/
/************************************************************************/
void GameLayer::execClearBubble(Bubble* pReadyBubble)
{
	//要执行清除球， 需要先找到需要清理的球
	ROWCOL_LIST clearBubbleList = findClearBubble(pReadyBubble);
	clearBubble(clearBubbleList);
}

//消除bubbleList里所有的球
void GameLayer::clearBubble(const ROWCOL_LIST &bubbleList)
{
	int nRow, nCol;
	for (ROWCOL_LIST::const_iterator iterBubble = bubbleList.begin();
		iterBubble != bubbleList.end();
		iterBubble++)
	{
		nRow = iterBubble->m_nRow;
		nCol = iterBubble->m_nCol;

		Bubble *obj = m_board[nRow][nCol];
		if (obj)
		{
			removeBubbleAction(obj);
			m_board[nRow][nCol] = NULL;
		}

		BUBBLE_LIST::iterator itFind = std::find(m_listBubble.begin(), m_listBubble.end(), obj);
		if (itFind != m_listBubble.end())
		{
			m_listBubble.erase(itFind);
		}

	}
}

void GameLayer::removeBubbleAction(Bubble* pBubble)
{
	pBubble->runAction(
		Sequence::create(
		DelayTime::create(0.2f),
		FadeOut::create(0.5f),
		CallFuncN::create(this, callfuncN_selector(GameLayer::callbackRemoveBubble)),
		NULL
		)
		);
}

void GameLayer::callbackRemoveBubble(Node *obj)
{
	if (obj != NULL)
	{
		this->removeChild(obj, true);
		obj->autorelease();
	}
}

ROWCOL_LIST GameLayer::checkFallBubble()
{
	ROWCOL_LIST LinkBubbleList;	//所有连接在一起的球

	for (int i = 0; i < MAX_COLS; i++)
	{
		if (m_board[0][i] != NULL)
		{
			LinkBubbleList.push_back(RowCol(0, i));
		}
	}
	if (LinkBubbleList.empty())
	{
		return LinkBubbleList;
	}

	//从上到下查找所有相连的球，则剩下没有找到的就是不相连的
	ROWCOL_LIST::iterator itCur = LinkBubbleList.begin();
	do
	{
		std::vector<RowCol> vecRowCol;
		GetAround(itCur->m_nRow, itCur->m_nCol, vecRowCol);

		for (size_t i = 0; i < vecRowCol.size(); i++)
		{
			Bubble *pBubble = m_board[vecRowCol[i].m_nRow][vecRowCol[i].m_nCol];
			if (pBubble)
			{
				RowCol pos(vecRowCol[i].m_nRow, vecRowCol[i].m_nCol);
				ROWCOL_LIST::iterator itFind = std::find(LinkBubbleList.begin(), LinkBubbleList.end(), pos);

				//查找是否已经在列表中
				if (itFind == LinkBubbleList.end())
				{
					LinkBubbleList.push_back(vecRowCol[i]);
				}
			}
		}
		itCur++;
	} while (itCur != LinkBubbleList.end());

	ROWCOL_LIST NoLinkBubblelist;	//找出剩下的所有没有连接的球，就是要下落的球
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS - i % 2; j++)
		{
			if (m_board[i][j] != NULL)
			{
				RowCol findRowCol(i, j);
				ROWCOL_LIST::iterator itFind = std::find(LinkBubbleList.begin(), LinkBubbleList.end(), findRowCol);
				if (itFind == LinkBubbleList.end())
				{
					NoLinkBubblelist.push_back(findRowCol);
				}
			}
		}
	}

	return NoLinkBubblelist;
}

//执行可以掉落的泡泡
void GameLayer::FallBubble(const ROWCOL_LIST &fallBubbleList)
{
	for (ROWCOL_LIST::const_iterator iter = fallBubbleList.begin(); iter != fallBubbleList.end(); iter++)
	{
		Bubble *pBubble = m_board[iter->m_nRow][iter->m_nCol];
		if (pBubble != NULL)
		{
			downBubbleAction(pBubble);

			BUBBLE_LIST::iterator iterBubble = std::find(m_listBubble.begin(), m_listBubble.end(), pBubble);
			if (iterBubble != m_listBubble.end())
			{
				m_listBubble.erase(iterBubble);
				m_board[iter->m_nRow][iter->m_nCol] = NULL;
			}
		}
	}

}

//掉落泡泡
void GameLayer::downBubbleAction(Bubble *pBubble)
{
	float offY = -100;

	Point pos = pBubble->getPosition();
	pBubble->runAction(
		Sequence::create(
		MoveTo::create((pos.y - offY) / 600.0, Vec2(pos.x, offY)),
		CallFuncN::create(this, callfuncN_selector(GameLayer::callbackRemoveBubble)),
		NULL
		)
		);
}