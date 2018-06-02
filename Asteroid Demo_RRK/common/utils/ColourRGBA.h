#ifndef __COLOURRGBA_H
#define __COLOURRGBA_H

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#else
	typedef unsigned long DWORD
#endif

// Clamps colour in the range 0.0 - 1.0
inline void ColourClamp(float &x) { if(x<0.0f) x=0.0f; if(x>1.0f) x=1.0f; }

/* Colour class. Note that the HWColour methods pack the floats in a DWORD which
could be useful for the PSP/GC consoles */
/* The RGBA stored is 8-bits for each channel, so R8G8B8A8 format */
class ColourRGBA
{
public:
	float		r,g,b,a;

	ColourRGBA(float _r, float _g, float _b, float _a) 
	{
		r=_r; g=_g; b=_b; a=_a; 
	}
	ColourRGBA(DWORD col) 
	{ 
		setHWColour(col); 
	}
	ColourRGBA() 
	{ 
		r=g=b=a=0; 
	}

	ColourRGBA operator-  (const ColourRGBA &c) const 
	{ 
		return ColourRGBA(r-c.r, g-c.g, b-c.b, a-c.a); 
	}
	ColourRGBA operator+  (const ColourRGBA &c) const 
	{ 
		return ColourRGBA(r+c.r, g+c.g, b+c.b, a+c.a); 
	}
	ColourRGBA operator*  (const ColourRGBA &c) const 
	{
		return ColourRGBA(r*c.r, g*c.g, b*c.b, a*c.a); 
	}
	ColourRGBA& operator-= (const ColourRGBA &c)		
	{ 
		r-=c.r; g-=c.g; b-=c.b; a-=c.a; return *this;   
	}
	ColourRGBA& operator+= (const ColourRGBA &c)		
	{
		r+=c.r; g+=c.g; b+=c.b; a+=c.a; return *this;   
	}
	bool operator== (const ColourRGBA &c) const 
	{
		return (r==c.r && g==c.g && b==c.b && a==c.a);  
	}
	bool operator!= (const ColourRGBA &c) const 
	{ 
		return (r!=c.r || g!=c.g || b!=c.b || a!=c.a);  
	}

	ColourRGBA operator/  (const float scalar) const 
	{
		return ColourRGBA(r/scalar, g/scalar, b/scalar, a/scalar); 
	}
	ColourRGBA	operator*  (const float scalar) const 
	{ 
		return ColourRGBA(r*scalar, g*scalar, b*scalar, a*scalar);
	}
	ColourRGBA&	operator*= (const float scalar)		 
	{
		r*=scalar; g*=scalar; b*=scalar; a*=scalar; return *this;   
	}

	void clamp() 
	{ 
		ColourClamp(r); ColourClamp(g); ColourClamp(b); ColourClamp(a); 
	}

	void setHWColour(DWORD col) 
	{	
		a = (col>>24)/255.0f; r = ((col>>16) & 0xFF)/255.0f; g = ((col>>8) & 0xFF)/255.0f; b = (col & 0xFF)/255.0f;	
	}
	DWORD getHWColour() const
	{
		return (DWORD(a*255.0f)<<24) + (DWORD(r*255.0f)<<16) + (DWORD(g*255.0f)<<8) + DWORD(b*255.0f);	
	}
};

#endif