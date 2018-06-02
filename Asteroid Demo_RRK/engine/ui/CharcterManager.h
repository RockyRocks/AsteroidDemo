#pragma once

#include "PreRequisite.h"
#include "Character.h"

namespace GUI
{
	class CharacterManager
	{
	public:



		typedef vector<Character> CharactersVec;
		typedef CharactersVec::iterator CharactersVecIter;

		CharacterManager(void);
		~CharacterManager(void);

		void InitializeCharacters();

		Character* GetCharacterPointer(char a) ;


	private:
		CharactersVec m_CharactersVec;
		CharactersVecIter m_iter;


	};

	inline CharacterManager& GetCharacterManager()
	{
		static CharacterManager m_singleton;
		return m_singleton;
	}
}