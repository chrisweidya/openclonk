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
// Startup screen for non-parameterized engine start: Player selection dialog
// Also contains player creation, editing and crew management

#include <C4Include.h>

#include <utility>

#include <Questionnaire.h>

#include <C4StartupMainDlg.h>
#include <C4Random.h>
#include <C4Game.h>
#include <C4Language.h>
#include <C4FileSelDlg.h>
#include <C4Log.h>
#include <C4GraphicsResource.h>
#include <C4RankSystem.h>
#include "gui/C4MouseControl.h"
#include <cctype>
#include <algorithm>
#include <string.h>

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
	
//	questionWindow->SetToolTip(LoadResStr("YEE_INSTRUCTIONS"));
//	questionWindow->SetDecoration(true, &C4Startup::Get()->Graphics.sfctBookScroll, true);
//	questionWindow->UpdateElementPositions();
//	questionWindow->SetSelectionChangeCallbackFn(new C4GUI::CallbackHandler<Questionnaire>(this, &Questionnaire::OnSelChange));
//	questionWindow->SetSelectionDblClickFn(new C4GUI::CallbackHandler<Questionnaire>(this, &Questionnaire::OnSelDblClick));
//	AddElement(pSelectionInfo = new C4GUI::TextWindow(rcInfoWindow, 0, 0, 0, 100, 4096, "  ", false, NULL, 0, true));
//	pSelectionInfo->SetDecoration(true, true, &C4Startup::Get()->Graphics.sfctBookScroll, true);
//	pSelectionInfo->UpdateHeight();
	/*
	// bottom line buttons - positioning done in UpdateBottomButtons by UpdatePlayerList
	C4Rect rcDefault(0, 0, 10, 10);
	AddElement(btnBack = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("IDS_BTN_BACK"), rcDefault, &Questionnaire::OnBackBtn));
	AddElement(btnNew = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("IDS_BTN_NEW"), rcDefault, &Questionnaire::OnNewBtn));
	btnNew->SetToolTip(LoadResStr("IDS_DLGTIP_NEWPLAYER"));
	AddElement(btnActivatePlr = new C4GUI::CallbackButton<Questionnaire>(NULL, rcDefault, &Questionnaire::OnActivateBtn));
	AddElement(btnDelete = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("IDS_BTN_DELETE"), rcDefault, &Questionnaire::OnDelBtn));
	AddElement(btnProperties = new C4GUI::CallbackButton<Questionnaire>(NULL, rcDefault, &Questionnaire::OnPropertyBtn));
	AddElement(btnCrew = new C4GUI::CallbackButton<Questionnaire>(LoadResStr("IDS_SELECT_CREW"), rcDefault, &Questionnaire::OnCrewBtn));
	btnCrew->SetToolTip(LoadResStr("IDS_DLGTIP_PLAYERCREW"));
	*/
	// refill listboxes
	// Just safety incase listbox was empty, in which case no selection change callback will have been done:
	// Update current listbox selection to that of no selected item
//	if (!questionWindow->GetFirst()) UpdateSelection();

	// initial focus on player list
	SetFocus(questionWindow, false);

	// key bindings
	C4CustomKey::CodeList keys;
	keys.push_back(C4KeyCodeEx(K_BACK));
	keys.push_back(C4KeyCodeEx(K_LEFT));
	keys.push_back(C4KeyCodeEx(K_ESCAPE));
	if (Config.Controls.GamepadGuiControl)
	{
		keys.push_back(C4KeyCodeEx(KEY_Gamepad(0, KEY_JOY_AnyHighButton)));
	}
	/*
	pKeyBack = new C4KeyBinding(keys, "StartupPlrSelBack", KEYSCOPE_Gui,
		new C4GUI::DlgKeyCB<Questionnaire>(*this, &Questionnaire::KeyBack), C4CustomKey::PRIO_CtrlOverride);
	pKeyProperties = new C4KeyBinding(C4KeyCodeEx(K_F2), "StartupPlrSelProp", KEYSCOPE_Gui,
		new C4GUI::DlgKeyCB<Questionnaire>(*this, &Questionnaire::KeyProperties), C4CustomKey::PRIO_CtrlOverride);
	pKeyCrew = new C4KeyBinding(C4KeyCodeEx(K_RIGHT), "StartupPlrSelCrew", KEYSCOPE_Gui,
		new C4GUI::ControlKeyDlgCB<Questionnaire>(pPlrListBox, *this, &Questionnaire::KeyCrew), C4CustomKey::PRIO_CtrlOverride);
	pKeyDelete = new C4KeyBinding(C4KeyCodeEx(K_DELETE), "StartupPlrSelDelete", KEYSCOPE_Gui,
		new C4GUI::DlgKeyCB<Questionnaire>(*this, &Questionnaire::KeyDelete), C4CustomKey::PRIO_CtrlOverride);
	pKeyNew = new C4KeyBinding(C4KeyCodeEx(K_INSERT), "StartupPlrSelNew", KEYSCOPE_Gui,
		new C4GUI::DlgKeyCB<Questionnaire>(*this, &Questionnaire::KeyNew), C4CustomKey::PRIO_CtrlOverride);
		*/
}

void Questionnaire::DoBack()
{
	// back 2 main, restart quiz
	currQs = 0;
	C4Startup::Get()->SwitchDialog(C4Startup::SDID_Back);
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
//	switch (eMode)
//	{
//	case PSDM_Player:
//	{
		// update some buttons for player mode
//		btnProperties->SetText(LoadResStr("IDS_BTN_PROPERTIES"));
//		btnProperties->SetToolTip(LoadResStr("IDS_DLGTIP_PLAYERPROPERTIES"));
//		btnNew->SetVisibility(true);
//		btnCrew->SetVisibility(true);
//		btnDelete->SetToolTip(LoadResStr("IDS_DLGTIP_PLAYERDELETE"));
		btnBack->SetToolTip(LoadResStr("IDS_DLGTIP_BACKMAIN"));
		btnBack->SetBounds(caBottomButtons.GetGridCell(0, 6, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnVeryUnimpt->SetBounds(caBottomButtons.GetGridCell(0, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnUnimpt->SetBounds(caBottomButtons.GetGridCell(1, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnImpt->SetBounds(caBottomButtons.GetGridCell(2, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnVeryImpt->SetBounds(caBottomButtons.GetGridCell(3, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));

//	}
//	break;
		/*
	case PSDM_Crew:
	{
		// update some buttons for player mode
		btnProperties->SetText(LoadResStr("IDS_BTN_RENAME"));
		btnProperties->SetToolTip(LoadResStr("IDS_DESC_CREWRENAME"));
		btnNew->SetVisibility(false);
		btnCrew->SetVisibility(false);
		btnDelete->SetToolTip(LoadResStr("IDS_MSG_DELETECLONK_DESC"));
		btnBack->SetToolTip(LoadResStr("IDS_MSG_BACKTOPLAYERDLG"));
		btnBack->SetBounds(caBottomButtons.GetGridCell(0, 4, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnActivatePlr->SetBounds(caBottomButtons.GetGridCell(1, 4, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnDelete->SetBounds(caBottomButtons.GetGridCell(2, 4, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
		btnProperties->SetBounds(caBottomButtons.GetGridCell(3, 4, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	}
	break;
	};*/
}

Questionnaire::~Questionnaire()
{
//	delete pKeyDelete;
//	delete pKeyCrew;
//	delete pKeyProperties;
//	delete pKeyBack;
//	delete pKeyNew;
}
