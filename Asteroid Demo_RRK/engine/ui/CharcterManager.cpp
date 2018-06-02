#include "CharcterManager.h"

namespace GUI
{

	CharacterManager::CharacterManager(void)
	{
		m_CharactersVec.clear();
	}

	CharacterManager::~CharacterManager(void)
	{
		m_CharactersVec.clear();
	}


	void CharacterManager::InitializeCharacters()
	{
		Character temp;
		
		temp.Clear();
		temp.SetCharacter('A');
		temp.AddPoint(2, 2);
		temp.AddPoint(8, 14);
		temp.AddPoint(14, 2);
		temp.AddPoint(11, 8);
		temp.AddPoint(5, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('B');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 10);
		temp.AddPoint(12, 10);
		temp.AddPoint(2, 10);
		temp.AddPoint(2, 14);
		temp.AddPoint(12, 14);
		temp.AddPoint(14, 12);
		temp.AddPoint(12, 10);
		temp.AddPoint(14, 6);
		temp.AddPoint(12, 2);
		temp.AddPoint(2, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('C');
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);


		temp.Clear();
		temp.SetCharacter('D');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(12, 14);
		temp.AddPoint(14, 12);
		temp.AddPoint(14, 4);
		temp.AddPoint(12, 2);
		temp.AddPoint(2, 2);
		m_CharactersVec.push_back(temp);


		temp.Clear();
		temp.SetCharacter('E');
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 9);
		temp.AddPoint(10, 9);
		temp.AddPoint(2, 9);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('F');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 10);
		temp.AddPoint(10, 10);
		temp.AddPoint(2, 10);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('G');
		temp.AddPoint(9, 7);
		temp.AddPoint(14, 7);
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('H');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 8);
		temp.AddPoint(14, 8);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('I');
		temp.AddPoint(4, 2);
		temp.AddPoint(12, 2);
		temp.AddPoint(8, 2);
		temp.AddPoint(8, 14);
		temp.AddPoint(12, 14);
		temp.AddPoint(4, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('J');
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		temp.AddPoint(4, 2);
		temp.AddPoint(2, 4);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('K');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 8);
		temp.AddPoint(14, 2);	
		temp.AddPoint(2, 8);
		temp.AddPoint(14, 14);
		temp.AddPoint(2, 8);
		temp.AddPoint(2, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('L');
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('M');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(8, 9);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('N');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('O');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('P');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 8);
		temp.AddPoint(2, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('Q');
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		temp.AddPoint(11, 2);
		temp.AddPoint(11, 5);
		temp.AddPoint(14, 5);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('R');
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 10);
		temp.AddPoint(2, 10);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('S');
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 7);
		temp.AddPoint(2, 7);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('T');
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(8, 14);
		temp.AddPoint(8, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('U');
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('V');
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 6);
		temp.AddPoint(8, 2);
		temp.AddPoint(14, 6);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('W');
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 2);
		temp.AddPoint(8, 8);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('X');
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 14);
		temp.AddPoint(8, 8);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('Y');
		temp.AddPoint(2, 14);
		temp.AddPoint(8, 8);
		temp.AddPoint(14, 14);
		temp.AddPoint(8, 8);
		temp.AddPoint(8, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('Z');
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);


		temp.Clear();
		temp.SetCharacter('0');
		temp.AddPoint(4, 2);
		temp.AddPoint(2, 4);
		temp.AddPoint(2, 12);
		temp.AddPoint(4, 14);
		temp.AddPoint(12, 14);
		temp.AddPoint(14, 12);
		temp.AddPoint(14, 4);
		temp.AddPoint(12, 2);
		temp.AddPoint(4, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('1');
		temp.AddPoint(6, 12);
		temp.AddPoint(8, 14);
		temp.AddPoint(8, 2);
		temp.AddPoint(5, 2);
		temp.AddPoint(11, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('2');
		temp.AddPoint(2, 14);
		temp.AddPoint(12, 14);
		temp.AddPoint(14, 12);
		temp.AddPoint(14, 10);
		temp.AddPoint(2, 10);
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('3');
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(9, 8);
		temp.AddPoint(14, 2);
		temp.AddPoint(2, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('4');
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 9);
		temp.AddPoint(14, 9);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('5');
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 7);
		temp.AddPoint(12, 9);		
		temp.AddPoint(2, 9);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('6');
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 8);
		temp.AddPoint(2, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('7');
		temp.AddPoint(2, 12);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('8');
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 14);
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 2);
		temp.AddPoint(2, 10);
		temp.AddPoint(14, 10);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('9');
		temp.AddPoint(14, 2);
		temp.AddPoint(14, 14);
		temp.AddPoint(2, 14);
		temp.AddPoint(2, 10);
		temp.AddPoint(14, 10);
		m_CharactersVec.push_back(temp);


		temp.Clear();
		temp.SetCharacter(' ');
		m_CharactersVec.push_back(temp);

		//Special Characters: arrow1(<) arrow2(>) arrow3(-) arrow4(=) brackets() brick(_) slash(/) 
		temp.Clear();
		temp.SetCharacter('<');
		temp.AddPoint(2, 8);
		temp.AddPoint(8, 14);
		temp.AddPoint(8, 10);
		temp.AddPoint(14, 10);
		temp.AddPoint(14, 6);
		temp.AddPoint(8, 6);
		temp.AddPoint(8, 2);
		temp.AddPoint(2, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('>');
		temp.AddPoint(14, 8);
		temp.AddPoint(8, 14);
		temp.AddPoint(8, 10);
		temp.AddPoint(2, 10);
		temp.AddPoint(2, 6);
		temp.AddPoint(8, 6);
		temp.AddPoint(8, 2);
		temp.AddPoint(14, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('-');
		temp.AddPoint(2, 8);
		temp.AddPoint(8, 14);
		temp.AddPoint(14, 8);
		temp.AddPoint(10, 8);
		temp.AddPoint(10, 2);
		temp.AddPoint(6, 2);
		temp.AddPoint(6, 8);
		temp.AddPoint(2, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('=');
		temp.AddPoint(2, 8);
		temp.AddPoint(8, 2);
		temp.AddPoint(14, 8);
		temp.AddPoint(10, 8);
		temp.AddPoint(10, 14);
		temp.AddPoint(6, 14);
		temp.AddPoint(6, 8);
		temp.AddPoint(2, 8);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('_');
		temp.AddPoint(4, 6);
		temp.AddPoint(4, 10);
		temp.AddPoint(12, 10);
		temp.AddPoint(12, 6);
		temp.AddPoint(4, 6);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('/');
		temp.AddPoint(2, 2);
		temp.AddPoint(14, 14);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('(');
		temp.AddPoint(8, 14);
		temp.AddPoint(7, 12);
		temp.AddPoint(6, 8);
		temp.AddPoint(7, 4);
		temp.AddPoint(8, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter(')');
		temp.AddPoint(8, 14);
		temp.AddPoint(9, 12);
		temp.AddPoint(10, 8);
		temp.AddPoint(9, 4);
		temp.AddPoint(8, 2);
		m_CharactersVec.push_back(temp);

		temp.Clear();
		temp.SetCharacter('?');
		temp.AddPoint(2, 8);
		temp.AddPoint(2, 14);
		temp.AddPoint(14, 14);
		temp.AddPoint(14, 8);
		temp.AddPoint(8, 8);
		temp.AddPoint(8, 2);
		m_CharactersVec.push_back(temp);
	}

	Character* CharacterManager::GetCharacterPointer(char a)
	{
		Character* pReturn = 0;
		m_iter = m_CharactersVec.begin();
		for (;m_iter!=m_CharactersVec.end();m_iter++)
		{
			if (m_iter->GetCharacter() == toupper(a))
			{
				pReturn = &(*m_iter);
				break;
			}
		}

		return pReturn;
	}
}