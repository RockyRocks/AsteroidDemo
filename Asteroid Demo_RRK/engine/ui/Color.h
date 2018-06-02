/*
----------------------------------------------------
------------R Rakesh Kumar------------
------------MSc Games Programming-------------------
------------The Department of Computer Science------
------------The University of Hull------------------
------------2009-2011 England-----------------------
----------------------------------------------------
*/
#pragma once

#include <assert.h>

namespace GUI
{
	class Color
	{
	public:
		Color(void):m_r(0),m_g(0),m_b(0),m_a(0)
		{
		}
		Color(float r,float g, float b, float a):m_r(r),m_g(g),m_b(b),m_a(a)
		{
		}

		Color(const Color& col):m_r(col.m_r),m_g(col.m_g),m_b(col.m_b),m_a(col.m_a)
		{

		}

		Color& operator = (const Color& col)
		{
			m_r = col.m_r;
			m_g = col.m_g;
			m_b = col.m_b;
			m_a = col.m_a;
			return *this;
		}

		~Color(void)
		{
		}

		//clamp value to [0-1]
		Color& Clamp()
		{
			if (m_r < 0)
				m_r = 0;
			else if (m_r > 1)
				m_r = 1;

			if (m_g < 0)
				m_g = 0;
			else if (m_g > 1)
				m_g = 1;

			if (m_b < 0)
				m_b = 0;
			else if (m_b > 1)
				m_b = 1;

			if (m_a < 0)
				m_a = 0;
			else if (m_a > 1)
				m_a = 1;

			return *this;
		}

		//comparable operations
		bool operator == (const Color& col) const
		{
			return (m_r==col.m_r && m_g==col.m_g && m_b==col.m_b && m_a==col.m_a);
		}

		bool operator != (const Color& col) const
		{
			return (m_r!=col.m_r || m_g!=col.m_g || m_b!=col.m_b || m_a!=col.m_a);
		}

		//arithmetic operations
		Color operator + (const Color& col) const
		{
			return Color(m_r+col.m_r,m_g+col.m_g,m_b+col.m_b,m_a+col.m_a);
		}

		Color operator + (float scalar) const
		{
			return Color(m_r+scalar,m_g+scalar,m_b+scalar,m_a+scalar);
		}


		Color operator - (const Color& col) const
		{
			return Color(m_r-col.m_r,m_g-col.m_g,m_b-col.m_b,m_a-col.m_a);
		}

		Color operator - (float scalar) const
		{
			return Color(m_r-scalar,m_g-scalar,m_b-scalar,m_a-scalar);
		}

		Color operator * (float scalar) const
		{
			return Color(m_r*scalar,m_g*scalar,m_b*scalar,m_a*scalar);
		}

		Color operator / (float scalar) const
		{
			assert(scalar!=0.0f);

			float temp = 1.0f/scalar;
			return Color(m_r*temp,m_g*temp,m_b*temp,m_a*temp);
		}

		//arithmetic updates
		Color& operator += (const Color& col)
		{
			m_r+=col.m_r;
			m_g+=col.m_g;
			m_b+=col.m_b;
			m_a+=col.m_a;
			return *this;
		}

		Color& operator +=(float scalar)
		{
			m_r+=scalar;
			m_g+=scalar;
			m_b+=scalar;
			m_a+=scalar;
			return *this;
		}

		Color& operator -= (const Color& col)
		{
			m_r-=col.m_r;
			m_g-=col.m_g;
			m_b-=col.m_b;
			m_a-=col.m_a;
			return *this;
		}

		Color& operator -=(float scalar)
		{
			m_r-=scalar;
			m_g-=scalar;
			m_b-=scalar;
			m_a-=scalar;
			return *this;
		}

		Color& operator *=(float scalar)
		{
			m_r*=scalar;
			m_g*=scalar;
			m_b*=scalar;
			m_a*=scalar;
			return *this;
		}

		Color& operator /=(float scalar)
		{
			assert(scalar!=0.0f);

			float temp = 1.0f/scalar;
			m_r*=temp;
			m_g*=temp;
			m_b*=temp;
			m_a*=temp;
			return *this;
		}


		float* ptr()
		{
			return &m_r;
		}

		const float* ptr() const 
		{
			return &m_r;
		}

		



	public:
		float m_r,m_g,m_b,m_a;
	public:
		static const Color WHITE;
		static const Color BLACK;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color PINK;
		static const Color LIGHTBLUE;
		static const Color YELLOW;
	};
}
