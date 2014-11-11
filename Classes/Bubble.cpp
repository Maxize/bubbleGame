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

Bubble* Bubble::create(const std::string &spritefilename)
{
	Bubble *bubble = new Bubble();
	if (bubble && bubble->initWithFile(spritefilename))
	{
		auto shaderState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
		bubble->setGLProgramState(shaderState);
		bubble->autorelease();
		return bubble;
	}

	CC_SAFE_DELETE(bubble);
	return nullptr;
}

void Bubble::setBubbleColor(BUBBLE_COLOR color)
{
	m_color = color;
}

BUBBLE_COLOR Bubble::getBubbleColor()
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

BUBBLE_COLOR Bubble::randomColor()
{
	m_color= static_cast<BUBBLE_COLOR>(rand() % COLOR_COUNT);
	return m_color;
}