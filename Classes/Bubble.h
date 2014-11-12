/************************************************************************/
/* 
** Date  : 2013/9/20

** author: Bright Moon

** blog :
** CSDN: http://blog.csdn.net/chenhaobright
** github: https://github.com/chenhaobright

** Note	 : 游戏中，泡泡类的组合，包含一些基本成员和函数
*/
/************************************************************************/


#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include "cocos2d.h"

#include "BubbleConstant.h"

using namespace cocos2d;

class Bubble : public Sprite
{
public:
	Bubble();
	~Bubble();

public:
	static Bubble* create(int color);

public:
	void setBubbleColor(int Color);
	int getBubbleColor();

	void setRowIndex(int row);
	int getRowIndex();

	void setColumnIndex(int col);
	int getColumnIndex();

	void setRowColIndex(int row, int col)
	{
		m_nRowIndex = row;
		m_nColIndex = col;
	}

	//BUBBLE_COLOR randomColor();		//随机生成一种颜色
	
private:
	char* getImage(int color);

private:
	//泡泡所有位置的行和列
	int m_nRowIndex;
	int m_nColIndex;

	int m_color;
};
#endif	//_BUBBLE_H_