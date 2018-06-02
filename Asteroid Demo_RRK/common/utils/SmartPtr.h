#ifndef __SMARTPTR_H
#define __SMARTPTR_H

#include <iostream>
/*************************
A very simple reference-counted smart pointer. i should *NOT* use this with derived types since
I haven't been able to figure this out yet :( .
*/
/*
Usage:
	SmartPtr<Foo> m_pFoo;
	m_pFoo->Foo();

No need to delete :)
*/

namespace Utils
{

class RefCount
{
public:
	void AddRef()
	{
		count++;
	}

	int Release()
	{
		return --count;
	}

private:
	int count;
};

template<typename T> class SmartPtr
{
public:
	SmartPtr() 
		: m_pData(0), m_pRefCount(0)
	{
		m_pRefCount = new RefCount();
		m_pRefCount->AddRef();
	}

	SmartPtr(T* pData)
		: m_pData(pData), m_pRefCount(0)
	{
		m_pRefCount = new RefCount();
		m_pRefCount->AddRef();
	}

	// Copy smart pointers, increase ref count
	SmartPtr(const SmartPtr<T>& sp)
		: m_pData(sp.m_pData), m_pRefCount(sp.m_pRefCount)
	{
		m_pRefCount->AddRef();
	}

	~SmartPtr()
	{
		// Decrement the counter and delete if the count is 0
		if(m_pRefCount->Release() == 0)
		{
			std::cout << "Destroying pointer " << std::endl;
			delete m_pData;
			delete m_pRefCount;
		}
	}

	// Pointer stuff
	// de-reference operator
	T& operator*()
	{
		return *m_pData;
	}

	T* operator->()
	{
		return m_pData;
	}

	// Handle assignment
	SmartPtr<T>& operator=(const SmartPtr<T>& rhs)
	{
		// Avoid self-assignment
		if(this != &rhs)
		{
			// Decrement the counter and delete if the count is 0
			if(m_pRefCount->Release() == 0)
			{
				delete m_pData;
				delete m_pRefCount;
			}

			m_pData = rhs.m_pData;
			m_pRefCount = rhs.m_pRefCount;
			m_pRefCount->AddRef();
		}

		return *this;
	}

private:
	T* m_pData;
	RefCount* m_pRefCount;
};

};

#endif