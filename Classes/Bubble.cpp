#include "Bubble.h"

Bubble::Bubble()
{
	m_color = COLOR_COUNT;
	m_nRowIndex = -1;
	m_nColIndex = -1;

}

Bubble::~Bubble()
{
}

Bubble* Bubble::create(int color)
{
	Bubble* bubble = new Bubble();
	if (bubble && bubble->initWithFile(bubble->getImage(color)))
	{
		/*auto shaderState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
		bubble->setGLProgramState(shaderState);*/
		bubble->setBubbleColor(color);
		bubble->autorelease();
		return bubble;
	}

	CC_SAFE_DELETE(bubble);
	return nullptr;
}

void Bubble::setBubbleColor(int color)
{
	m_color = color;
}

int Bubble::getBubbleColor()
{
	return m_color;
}

void Bubble::setRowIndex(int row)
{
	m_nRowIndex = row;
}

int Bubble::getRowIndex()
{
	return m_nRowIndex;
}

void Bubble::setColumnIndex(int col)
{
	m_nColIndex = col;
}

int Bubble::getColumnIndex()
{
	return m_nColIndex;
}

//BUBBLE_COLOR Bubble::randomColor()
//{
//	m_color= static_cast<BUBBLE_COLOR>(rand() % COLOR_COUNT);
//	return m_color;
//}

char* Bubble::getImage(int color){
	switch (color){
	case BUBBLE_COLOR::BUBBLE_YELLOW:
		return "bubble_0.png";
	case BUBBLE_COLOR::BUBBLE_PURPLE:
		return "bubble_1.png";
	case BUBBLE_COLOR::BUBBLE_BULE:
		return "bubble_2.png";
	case BUBBLE_COLOR::BUBBLE_RED:
		return "bubble_3.png";
	case BUBBLE_COLOR::BUBBLE_GREEN:
		return "bubble_4.png";
	case BUBBLE_COLOR::BUBBLE_BLACK:
		return "bubble_5.png";
	case BUBBLE_COLOR::BUBBLE_SILVERY:
		return "bubble_6.png";
	case BUBBLE_COLOR::BUBBLE_GOLDEN:
		return "bubble_7.png";
	}
}

