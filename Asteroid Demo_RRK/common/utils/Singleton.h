#ifndef __SINGLETON_H
#define __SINGLETON_H

#include <assert.h>
/* Templated Singleton class to use if you want your class to be a singleton.
Example usage:

class MySingleton : Singleton<MySingleton>
{
	friend Singleton<MySingleton>;

	private:
		MySingleton();
		~MySingleton();

	...
	...
	...
}

Accessing the singleton now becomes:
MySingleton::Instance();
*/
template <typename T> 
class Singleton
{
public:
    
    static T* GetInstance()
    {
        if (m_instance == NULL) 
			m_instance = new T;
        
        assert(m_instance != NULL);

        return m_instance;
    };

    static void DestroyInstance()
    {
        delete m_instance;
        m_instance = NULL;
    };

protected:

    // shield the constructor and destructor to prevent outside sources
    // from creating or destroying a Singleton instance.

    // Default constructor.
    Singleton() { };


    // Destructor.
    virtual ~Singleton() { };

private:

    // Copy constructor.
    Singleton(const Singleton& source) { };

	// Singleton class instance
    static T* m_instance;
};

// Initialize the static instance
template <typename T> T* Singleton<T>::m_instance = NULL;


#endif