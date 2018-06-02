#pragma once

#include "PreRequisite.h"

namespace GUI
{
	class Character
	{
	public:
		struct Point
		{
			Point(char x,char y):m_x(x),m_y(y)
			{
			}
			char m_x;
			char m_y;
		};

		typedef vector<Point> PointsVec;
		typedef PointsVec::iterator PointsVecIter;

		Character(void);
		~Character(void);

		void AddPoint(char x,char y);
		void Clear();

		void SetCharacter(char a);
		char GetCharacter()const;
		PointsVec& GetPointsVec() ;

	private:

		char m_character;

		PointsVec m_pointsVec;


	};
}
