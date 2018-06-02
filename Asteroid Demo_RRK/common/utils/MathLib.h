#ifndef __MATHLIB_H
#define __MATHLIB_H

#include <cmath>
#include <iostream>
#include <algorithm>

/* Math library with Vector2f, Vector3f and Matrix44f classes */
namespace MathLib
{
	static const float PI = 3.1415926535f;

	// Some useful functions
	static float randFloat()
	{
		return (float)rand() / ((float)RAND_MAX + 1);
	}
	static float degToRad(float angle)
	{
		return ((angle*PI) / 180.0f);
	}
	static float radToDeg(float angle)
	{
		return ((angle*180.0f) / PI);
	}
	static float round( float no )    
	{
		int x, temp;
		float y;
		temp = x = (int)no ; 
		y = no -  x ; 
		y*=100 ;
		x = (int)y;
		y-= x;  
		if( y >= 0.5 )
			x++;
		return (float)(temp + x/100);
	}
	// Vector2f class
	class Vector2f
	{
		friend Vector2f operator*(float scalar, const Vector2f &v);
		friend Vector2f operator*(const Vector2f &lhs, const Vector2f &rhs);
		friend Vector2f operator-(const Vector2f &v);

	public:
		float x, y;
	public:
		Vector2f();
		Vector2f(float nx, float ny);
		Vector2f operator*(float scalar) const;
		Vector2f operator/(float scalar) const;
		Vector2f operator+(const Vector2f &rhs) const;
		Vector2f operator-(const Vector2f &rhs) const; // no cross product in 2d
		
		const Vector2f &operator*=(float scalar);
		const Vector2f &operator/=(float scalar);
		const Vector2f &operator+=(const Vector2f &rhs);
		const Vector2f &operator-=(const Vector2f &rhs);

		const Vector2f& getVector();
		void setVector(Vector2f&);
		
		float length() const;
		void normalise();
		float dot(const Vector2f &rhs) const;
	};
	// ****** Vector implementation
	inline std::ostream &operator<<(std::ostream &output, const Vector2f &v)
	{
		std::cout << '(' << v.x << ", " << v.y << ')';
		return output;
	}
	inline Vector2f operator*(float scalar, const Vector2f &v) {
		return v * scalar;
	}
	inline Vector2f operator*(const Vector2f &rhs, const Vector2f &lhs) {
		return Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
	}
	inline Vector2f operator-(const Vector2f &v) {
		return Vector2f(-v.x, -v.y);
	}
	inline Vector2f::Vector2f() : x(0), y(0) {}

	inline Vector2f::Vector2f(float nx, float ny) : x(nx), y(ny) {}
	
	inline Vector2f Vector2f::operator*(float scalar) const 
	{
		return Vector2f(x * scalar, y * scalar);
	}
	inline Vector2f Vector2f::operator/(float scalar) const 
	{
		// check if the scalar is zero
		return Vector2f(x / scalar, y / scalar);
	}
	inline Vector2f Vector2f::operator+(const Vector2f &rhs) const 
	{
		return Vector2f(x + rhs.x, y + rhs.y);
	}
	inline Vector2f Vector2f::operator-(const Vector2f &rhs) const 
	{
		return Vector2f(x - rhs.x, y - rhs.y);
	}
	inline const Vector2f &Vector2f::operator*=(float scalar) 
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	inline const Vector2f &Vector2f::operator/=(float scalar) 
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
	inline const Vector2f &Vector2f::operator+=(const Vector2f &rhs) 
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	inline const Vector2f &Vector2f::operator-=(const Vector2f &rhs) 
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	inline const Vector2f& Vector2f::getVector()
	{
		return *this;
	}
	inline void Vector2f::setVector(Vector2f &inVec)
	{
		x = inVec.x;
		y = inVec.y;
	}
	inline float Vector2f::length() const 
	{
		return sqrt(x*x + y*y);
	}
	inline void Vector2f::normalise() 
	{
		if(length() < 0)
			std::cout << "Error, dividing by 0. Cannot normalise vector" << std::endl;
		else
		{
			float m = 1.0f/length(); // check if length is 0
			x *= m;
			y *= m;
		}
	}
	inline float Vector2f::dot(const Vector2f &rhs) const 
	{
		return x * rhs.x + y * rhs.y;
	}
	// ******* end vector implementation


	// Vector3f class
	class Vector3f 
	{
		friend Vector3f operator*(float scalar, const Vector3f &v);
		friend Vector3f operator-(const Vector3f &v);

	public:
		float x, y, z;
	public:

		Vector3f();
		Vector3f(float nx, float ny, float nz);	
		
		Vector3f operator*(float scalar) const;
		Vector3f operator/(float scalar) const;
		Vector3f operator+(const Vector3f &rhs) const;
		Vector3f operator-(const Vector3f &rhs) const;
		Vector3f operator^(const Vector3f &rhs) const;
		
		const Vector3f &operator*=(float scalar);
		const Vector3f &operator/=(float scalar);
		const Vector3f &operator+=(const Vector3f &rhs);
		const Vector3f &operator-=(const Vector3f &rhs);
		
		float length() const;
		void normalise();
		float dot(const Vector3f &rhs) const;
	};
	// **** Vector3f implementation
	inline Vector3f operator*(float scalar, const Vector3f &v)
	{
		return v * scalar;
	}
	inline Vector3f operator-(const Vector3f &v)
	{
		return Vector3f(-v.x, -v.y, -v.z);
	}

	inline std::ostream &operator<<(std::ostream &output, const Vector3f &v)
	{
		std::cout << '(' << v.x << ", " << v.y << ", " << v.z << ')';
		return output;
	}

	inline Vector3f::Vector3f() : x(0), y(0), z(0) { }

	inline Vector3f::Vector3f(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

	inline Vector3f Vector3f::operator*(float scalar) const 
	{
		return Vector3f(x * scalar, y * scalar, z * scalar);
	}
	inline Vector3f Vector3f::operator/(float scalar) const 
	{
		return Vector3f(x / scalar, y / scalar, z / scalar);
	}
	inline Vector3f Vector3f::operator+(const Vector3f &rhs) const 
	{
		return Vector3f(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	inline Vector3f Vector3f::operator-(const Vector3f &rhs) const 
	{
		return Vector3f(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	inline Vector3f Vector3f::operator^(const Vector3f &rhs) const // cross product
	{
		return Vector3f((y * rhs.z) - (z * rhs.y),
						(z * rhs.x) - (x * rhs.z),
						(x * rhs.y) - (y * rhs.x));
	}
	inline const Vector3f &Vector3f::operator*=(float scalar) 
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	inline const Vector3f &Vector3f::operator/=(float scalar) 
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	inline const Vector3f &Vector3f::operator+=(const Vector3f &rhs) 
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	inline const Vector3f &Vector3f::operator-=(const Vector3f &rhs) 
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	inline float Vector3f::length() const 
	{
		return sqrt(x*x + y*y + z*z);
	}
	inline void Vector3f::normalise() 
	{
		float m = 1.0f/length();
		x *= m;
		y *= m;
		z *= m;
	}
	inline float Vector3f::dot(const Vector3f &rhs) const 
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	// ***** end implementation

	// Matrix44f class
	class Matrix44f
	{
		// Multiplies a vector by a matrix. Returns the new vector.
		friend Vector3f operator*(const Vector3f &lhs, const Matrix44f &rhs);
		friend Vector2f operator*(const Vector2f &lhs, const Matrix44f &rhs);
		friend Matrix44f operator*(float scalar, const Matrix44f &rhs);

	public:
		static const Matrix44f IDENTITY;

		Matrix44f();
		Matrix44f(float m[16]);
		Matrix44f(float m11, float m12, float m13, float m14,
				float m21, float m22, float m23, float m24,
				float m31, float m32, float m33, float m34,
				float m41, float m42, float m43, float m44);

		~Matrix44f();

		void assign(float m[16]);
		void assign(float m11, float m12, float m13, float m14,
				float m21, float m22, float m23, float m24,
				float m31, float m32, float m33, float m34,
				float m41, float m42, float m43, float m44);

		float *operator[](int row);
		const float *operator[](int row) const;

		float get(int row, int column) const;

		// Operators
		Matrix44f operator+(const Matrix44f &rhs) const;
		Matrix44f operator-(const Matrix44f &rhs) const;
		Matrix44f operator*(const Matrix44f &rhs) const;
		Matrix44f operator*(float scalar) const;
		Matrix44f operator/(float scalar) const;

		Matrix44f &operator+=(const Matrix44f &rhs);
		Matrix44f &operator-=(const Matrix44f &rhs);
		Matrix44f &operator*=(const Matrix44f &rhs);
		Matrix44f &operator*=(float scalar);
		Matrix44f &operator/=(float scalar);

		// *** Mtx functions ***
		// Zero's this mtx
		void zero();
		// Changes this mtx44f into an identity mtx
		void identity();
		// Changes this mtx44f into it's transpose
		void transpose();

		// Transposes the first 3 rows/columns (top left) in the matrix
		/// and returns a new mtx44f
		Matrix44f transposeM1();

		void rotate(const Vector3f &axis, const float angle);

		private:
			float mtx[4][4];
		};

	// ****** Matrix44f inline implementation
	inline Matrix44f::~Matrix44f() {}
	inline Matrix44f::Matrix44f() { zero(); }

	inline Matrix44f::Matrix44f(float m[16]) { assign(m); }

	inline Matrix44f::Matrix44f(float m11, float m12, float m13, float m14,
								float m21, float m22, float m23, float m24,
								float m31, float m32, float m33, float m34,
								float m41, float m42, float m43, float m44)
	{
		assign(m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44);
	}

	inline void Matrix44f::assign(float m[16])
	{
		mtx[0][0] = m[0],  mtx[0][1] = m[1],  mtx[0][2] = m[2],  mtx[0][3] = m[3];
		mtx[1][0] = m[4],  mtx[1][1] = m[5],  mtx[1][2] = m[6],  mtx[1][3] = m[7];
		mtx[2][0] = m[8],  mtx[2][1] = m[9],  mtx[2][2] = m[10], mtx[2][3] = m[11];
		mtx[3][0] = m[12], mtx[3][1] = m[13], mtx[3][2] = m[14], mtx[3][3] = m[15];
	}

	inline void Matrix44f::assign(float m11, float m12, float m13, float m14,
								  float m21, float m22, float m23, float m24,
								  float m31, float m32, float m33, float m34,
								  float m41, float m42, float m43, float m44)
	{
		mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13, mtx[0][3] = m14;
		mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23, mtx[1][3] = m24;
		mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33, mtx[2][3] = m34;
		mtx[3][0] = m41, mtx[3][1] = m42, mtx[3][2] = m43, mtx[3][3] = m44;
	}

	inline Vector3f operator*(const Vector3f &lhs, const Matrix44f &rhs)
	{
		return Vector3f((lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[0][1]) + (lhs.z * rhs.mtx[0][2]),
					   (lhs.x * rhs.mtx[1][0]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[1][2]),
					   (lhs.x * rhs.mtx[2][0]) + (lhs.y * rhs.mtx[2][1]) + (lhs.z * rhs.mtx[2][2]));
	}

	inline Vector2f operator*(const Vector2f &lhs, const Matrix44f &rhs)
	{
		return Vector2f((lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[0][1]) + (1.f * rhs.mtx[0][2]),
						(lhs.x * rhs.mtx[1][0]) + (lhs.y * rhs.mtx[1][1]) + (1.f * rhs.mtx[1][2]));
	}
	inline Matrix44f operator*(float scalar, const Matrix44f &rhs)
	{
		return rhs * scalar;
	}
	inline float *Matrix44f::operator[](int row)
	{
		return mtx[row];
	}
	inline const float *Matrix44f::operator[](int row) const
	{
		return mtx[row];
	}
	inline float Matrix44f::get(int row, int column) const
	{
		return mtx[row][column];
	}
	inline Matrix44f Matrix44f::operator+(const Matrix44f &rhs) const
	{
		Matrix44f tmp(*this);
		tmp += rhs;

		return tmp;
	}
	inline Matrix44f Matrix44f::operator-(const Matrix44f &rhs) const
	{
		Matrix44f tmp(*this);
		tmp -= rhs;

		return tmp;
	}
	inline Matrix44f Matrix44f::operator*(const Matrix44f &rhs) const
	{
		Matrix44f tmp(*this);
		tmp *= rhs;

		return tmp;
	}
	inline Matrix44f Matrix44f::operator*(float scalar) const
	{
		Matrix44f tmp(*this);
		tmp *= scalar;

		return tmp;
	}
	inline Matrix44f Matrix44f::operator/(float scalar) const
	{
		Matrix44f tmp(*this);
		tmp /= scalar;

		return tmp;
	}
	inline void Matrix44f::zero()
	{
		mtx[0][0] = 0.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f, mtx[0][3] = 0.0f;
		mtx[1][0] = 0.0f, mtx[1][1] = 0.0f, mtx[1][2] = 0.0f, mtx[1][3] = 0.0f;
		mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 0.0f, mtx[2][3] = 0.0f;
		mtx[3][0] = 0.0f, mtx[3][1] = 0.0f, mtx[3][2] = 0.0f, mtx[3][3] = 0.0f;
	}
	inline void Matrix44f::identity()
	{
		mtx[0][0] = 1.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f, mtx[0][3] = 0.0f;
		mtx[1][0] = 0.0f, mtx[1][1] = 1.0f, mtx[1][2] = 0.0f, mtx[1][3] = 0.0f;
		mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 1.0f, mtx[2][3] = 0.0f;
		mtx[3][0] = 0.0f, mtx[3][1] = 0.0f, mtx[3][2] = 0.0f, mtx[3][3] = 1.0f;
	}
	inline void Matrix44f::transpose()
	{	
		std::swap(mtx[1][0], mtx[0][1]);
		std::swap(mtx[2][0], mtx[0][2]);
		std::swap(mtx[3][0], mtx[0][3]);
		std::swap(mtx[2][1], mtx[1][2]);
		std::swap(mtx[3][1], mtx[1][3]);
		std::swap(mtx[3][2], mtx[2][3]);
	}
	inline std::ostream &operator<<(std::ostream &output, const Matrix44f &m)
	{
		std::cout << "|m11=" << m[0][0] << "|m12=" << m[0][1] << "|m13=" << m[0][2] << "|m14=" << m[0][3] << "|" << std::endl;
		std::cout << "|m21=" << m[0][0] << "|m22=" << m[0][1] << "|m23=" << m[0][2] << "|m24=" << m[0][3] << "|" << std::endl;
		std::cout << "|m31=" << m[0][0] << "|m32=" << m[0][1] << "|m33=" << m[0][2] << "|m34=" << m[0][3] << "|" << std::endl;
		std::cout << "|m41=" << m[0][0] << "|m42=" << m[0][1] << "|m43=" << m[0][2] << "|m44=" << m[0][3] << "|" << std::endl;

		return output;
	}
	//******* Matrix44f partial implementation end
};

#endif