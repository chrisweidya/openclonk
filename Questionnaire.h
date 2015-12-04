/*
* OpenClonk, http://www.openclonk.org
*
* Copyright (c) 2005-2009, RedWolf Design GmbH, http://www.clonk.de/
* Copyright (c) 2009-2013, The OpenClonk Team and contributors
*
* Distributed under the terms of the ISC license; see accompanying file
* "COPYING" for details.
*
* "Clonk" is a registered trademark of Matthes Bender, used with permission.
* See accompanying file "TRADEMARK" for details.
*
* To redistribute this file separately, substitute the full license texts
* for the above references.
*/

#ifndef INC_Questionnaire
#define INC_Questionnaire

#include "C4Startup.h"

#include <string>

// startup dialog: Player selection
class Questionnaire : public C4StartupDlg
{
private:
	enum { IconLabelSpacing = 2 }; // space between an icon and its text

public:
	Questionnaire(); // ctor
	~Questionnaire(); // dtor

private:
	class C4GUI::TextWindow *questionWindow;
	C4GUI::TextWindow *instructionsWindow;

private:
	C4Rect rcBottomButtons; int32_t iBottomButtonWidth;
	class C4GUI::Button *btnActivatePlr, *btnCrew, *btnProperties, *btnDelete, *btnBack, *btnNext,
		*btnVeryUnimpt, *btnUnimpt, *btnImpt, *btnVeryImpt;

	int currQs = 0;

	enum { VERY_UNIMPORTANT = 1, UNIMPORTANT = 2, IMPORTANT = 3, VERY_IMPORTANT = 4 };

	void UpdateBottomButtons(); // update command button texts and positions
	void UpdateSelection();
	void OnSelChange(class C4GUI::Element *pEl) { UpdateSelection(); }
	int ModifyProfile();

protected:

	virtual bool OnEnter() { return false; } // Enter ignored
	//	virtual bool OnEscape() { DoBack(); return true; }

	void OnBackBtn(C4GUI::Control *btn) { DoBack(); }
	void OnNextBtn(C4GUI::Control *btn) { DoNext(currQs); }
	void OnVeryUnimptBtn(C4GUI::Control *btn) { DoNext(VERY_UNIMPORTANT); };
	void OnUnimptBtn(C4GUI::Control *btn) { DoNext(UNIMPORTANT); };
	void OnImptBtn(C4GUI::Control *btn) { DoNext(IMPORTANT); };
	void OnVeryImptBtn(C4GUI::Control *btn) { DoNext(VERY_IMPORTANT); };

	bool KeyBack() { DoBack(); return true; }
	void DoBack(); // back to main menu or previous question
	void DoNext();
	void DoNext(int feedback);
	void ShowQuestion(int index);

public:

};


#endif // INC_C4StartupPlrSelDlg
