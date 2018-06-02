#ifndef __HASHEDSTRING_H
#define __HASHEDSTRING_H

#include <string>

/* Encapsulates both the string and it's hashed value */
class HashedString
{
public:
	HashedString() {}

	explicit HashedString(const char * const pIdentStr)
		: m_Ident(hash_name(pIdentStr)), m_IdentStr(pIdentStr)
	{}

	unsigned long getHashValue() const
	{
		return reinterpret_cast<unsigned long>(m_Ident);
	}

	const std::string & getStr() const { return m_IdentStr; }

	bool operator< (HashedString const &rhs) const
	{
		bool r = (getHashValue() < rhs.getHashValue());
		return r;
	}

	bool operator== (HashedString const &rhs) const
	{
		bool r = (getHashValue() == rhs.getHashValue());
		return r;
	}

	static void * hash_name(char const * pIdentStr);

private:
	void * m_Ident;
	std::string m_IdentStr;
};

#endif
