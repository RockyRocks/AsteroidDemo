#include "Character.h"

namespace GUI
{
	Character::Character(void)
	{
		m_pointsVec.clear();
	}

	Character::~Character(void)
	{
		m_pointsVec.clear();
	}

	void Character::AddPoint(char x,char y)
	{
		m_pointsVec.push_back(Point(x,y));
	}
	void Character::Clear()
	{
		m_pointsVec.clear();
	}

	void Character::SetCharacter(char a)
	{
		m_character = a;
	}
	char Character::GetCharacter()const
	{	
		return m_character;
	}

	Character::PointsVec& Character::GetPointsVec() 
	{
		return m_pointsVec;
	}
}