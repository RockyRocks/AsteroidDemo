#pragma once

#include "GUI_Page.h"

#include "..\..\common\utils\Singleton.h"
//Notice: Please see MainGameState::Start() for example!!!!!!!!! Cheers!!!!!!
//Special Characters: arrow1(<) arrow2(>) arrow3(-) arrow4(=) brackets() brick(_) slash(/) 
class EventManager;
namespace GUI
{
	using namespace std;
	class GUISystem : public Singleton<GUISystem>
	{

	public:
		typedef std::vector<GUI_Page> PageVec;
		typedef PageVec::iterator PageVecIter;

	public:
		GUISystem();
		~GUISystem(void);

		bool InitializeGUI();
		bool DestroyGUI();

		GUI_Page* AddPage(const string& name);
		void RemovePage(const string& name);
		GUI_Page* GetPage(const string& name);
		GUI_Page* GetActivePage();
		//change active page
		bool SelectPage(const string& pagename);

		void RenderPage();
		

	private:

		PageVec m_pageVec;

		GUI_Page* m_activePage;

	};

	//inline GUISystem& GetGUISystem()
	//{
	//	static GUISystem guisystem;
	//	return guisystem;
	//}
}
