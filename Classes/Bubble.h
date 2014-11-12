/************************************************************************/
/* 
** Date  : 2013/9/20

** author: Bright Moon

** blog :
** CSDN: http://blog.csdn.net/chenhaobright
** github: https://github.com/chenhaobright

** Note	 : ��Ϸ�У����������ϣ�����һЩ������Ա�ͺ���
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

	//BUBBLE_COLOR randomColor();		//�������һ����ɫ
	
private:
	char* getImage(int color);

private:
	//��������λ�õ��к���
	int m_nRowIndex;
	int m_nColIndex;

	int m_color;
};
#endif	//_BUBBLE_H_