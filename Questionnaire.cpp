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
#include <C4Include.h>
#include <Questionnaire.h>
#include <PlayerProfile.h>

#include <C4Application.h>
#include <C4GameOptions.h>
#include <C4Network2Dialogs.h>
#include <C4StartupMainDlg.h>
#include <C4StartupNetDlg.h>
#include <C4ComponentHost.h>
#include <C4Components.h>
#include <C4RTF.h>
#include <C4Log.h>
#include <C4Game.h>
#include <C4GameDialogs.h>
#include <C4Language.h>
#include <C4FileSelDlg.h>
#include <C4MouseControl.h>
#include <C4GraphicsResource.h>
#include <set>

// font clrs
const uint32_t ClrPlayerItem = 0xffffffff;

// Arbitrary cut-off value for player color value. This avoids pitch black
// colors which look ugly. Note that this limit is only applied in the UI,
// it's still possible to edit the Player.txt by hand.
const uint32_t PlayerColorValueLowBound = 64;

const uint32_t NUM_QUESTIONS = 12;

// ------------------------------------------------
// --- Questionnaire

Questionnaire::Questionnaire() : C4StartupDlg("Questionnaire")
{
	// ctor
	UpdateSize(); // for clientrect

	// screen calculations
	int iButtonHeight = C4GUI_ButtonHgt;
	int iButtonXSpacing = (GetClientRect().Wdt > 700) ? GetClientRect().Wdt / 58 : 2;
	int iButtonCount = 6;
	C4GUI::ComponentAligner caMain(GetClientRect(), 0, 0, true);
	C4GUI::ComponentAligner caButtonArea(GetClientRect(), 0, 0);
	//rcBottomButtons = caButtonArea.GetAll();	
	iBottomButtonWidth = (caButtonArea.GetWidth() - iButtonXSpacing * (iButtonCount - 1)) / iButtonCount;
	C4Rect rcMain = caMain.GetAll();
	C4Rect rcInstructionsWindow = C4Rect(rcMain.Wdt / 8, rcMain.Hgt / 11, rcMain.Wdt * 11 / 16, rcMain.Hgt * 1 / 16);
	C4Rect rcQuestionWindow = C4Rect(rcMain.Wdt / 8, rcMain.Hgt / 6, rcMain.Wdt * 11 / 16, rcMain.Hgt * 1 / 8);
	rcBottomButtons = C4Rect(rcMain.Wdt / 8, rcQuestionWindow.GetBottom(), rcMain.Wdt * 11 / 16, rcMain.Hgt * 2 / 8);
	C4Rect rcInfoWindow = C4Rect(rcMain.Wdt * 9 / 16, rcMain.Hgt / 8, rcMain.Wdt * 5 / 16, rcMain.Hgt * 6 / 8);
	AddElement(instructionsWindow = new C4GUI::TextWindow(rcInstructionsWindow, 0, 0, 0, 100, 4096, "  ", false, NULL, 0, true));
	AddElement(questionWindow = new C4GUI::TextWindow(rcQuestionWindow, 0, 0, 0, 100, 4096, "  ", false, NULL, 0, true));
	questionWindow->SetDecoration(true, true, &C4Startup::Get()->Graphics.sfctBookScroll, true);
	instructionsWindow->SetDecoration(true, true, &C4Startup::Get()->Graphics.sfctBookScroll, true);
	questionWindow->UpdateHeight();
	instructionsWindow->UpdateHeight();
	instructionsWindow->AddTextLine(FormatString(LoadResStr("YEE_INSTRUCTIONS")).getData(), &C4Startup::Get()->Graphics.BookFont, ClrPlayerItem, false, false);
	DoNext(currQs);

	C4Rect rcDefault(0, 0, 10, 10);
	AddElement(btnBack = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("IDS_BTN_BACK_MENU"), rcDefault, &Questionnaire::OnBackBtn));
	//	AddElement(btnNext = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("IDS_BTN_NEXT"), rcDefault, &Questionnaire::OnNextBtn));
	AddElement(btnVeryUnimpt = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("YEE_VERY_UNIMPORTANT"), rcDefault, &Questionnaire::OnVeryUnimptBtn));
	AddElement(btnUnimpt = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("YEE_UNIMPORTANT"), rcDefault, &Questionnaire::OnUnimptBtn));
	AddElement(btnImpt = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("YEE_IMPORTANT"), rcDefault, &Questionnaire::OnImptBtn));
	AddElement(btnVeryImpt = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("YEE_VERY_IMPORTANT"), rcDefault, &Questionnaire::OnVeryImptBtn));
	UpdateBottomButtons();

	ModifyProfile();

}

void Questionnaire::DoBack()
{
	// back 2 main, restart quiz
	currQs = 0;
	C4Startup::Get()->SwitchDialog(C4Startup::SDID_Back);
}

int Questionnaire::ModifyProfile()
{
	PlayerProfile *profile = PlayerProfile::getSingleProfile();
	if (!profile)
		return -1;
	
	
	return 1;
}


void Questionnaire::DoNext()
{
	ShowQuestion(++currQs);
}

void Questionnaire::DoNext(int feedback)
{
	ShowQuestion(++currQs);
}

void Questionnaire::ShowQuestion(int index) {
	questionWindow->ClearText(true);
	if (index > 0 && index <= NUM_QUESTIONS)
	{
		char displayStr[20] = "YEE_QUESTION";
		char number[5];
		itoa(index, number, 10);
		strcat(displayStr, number);
		questionWindow->AddTextLine(FormatString(LoadResStr(displayStr)).getData(), &C4Startup::Get()->Graphics.BookFont, ClrPlayerItem, false, false);
	}
	else if (index > 12) {
		questionWindow->AddTextLine(FormatString(LoadResStr("YEE_THANKS")).getData(), &C4Startup::Get()->Graphics.BookFont, ClrPlayerItem, false, false);
		btnVeryUnimpt->SetVisibility(false);
		btnUnimpt->SetVisibility(false);
		btnImpt->SetVisibility(false);
		btnVeryImpt->SetVisibility(false);
		currQs = 0;
	}

}

void Questionnaire::UpdateBottomButtons()
{
	// bottom line buttons depend on list mode
	C4GUI::ComponentAligner caBottomButtons(rcBottomButtons, 0, 0);

	btnBack->SetToolTip(LoadResStr("IDS_DLGTIP_BACKMAIN"));
	btnBack->SetBounds(caBottomButtons.GetGridCell(0, 6, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnVeryUnimpt->SetBounds(caBottomButtons.GetGridCell(0, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnUnimpt->SetBounds(caBottomButtons.GetGridCell(1, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnImpt->SetBounds(caBottomButtons.GetGridCell(2, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnVeryImpt->SetBounds(caBottomButtons.GetGridCell(3, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));

}

Questionnaire::~Questionnaire()
{
}
