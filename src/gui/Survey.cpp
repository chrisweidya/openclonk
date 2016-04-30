//Created by Chris
//Player survey handling
#include <C4Include.h>
#include <Survey.h>
#include <PlayerProfile.h>
#include <C4PlayerList.h>
#include <C4Player.h>

// font clrs
const uint32_t ClrPlayerItem = 0xffffffff;

const uint32_t PlayerColorValueLowBound = 64;

const uint32_t FEEDBACKBUFFER = 200;
const uint32_t NUM_QUESTIONS = 5;

// ------------------------------------------------
// --- Survey

//Creates survey window, buttons
Survey::Survey() : C4StartupDlg("Survey")
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
	C4Rect rcInstructionsWindow = C4Rect(rcMain.Wdt / 8, rcMain.Hgt / 11, rcMain.Wdt * 11 / 16, rcMain.Hgt * 1 / 12);
	C4Rect rcQuestionWindow = C4Rect(rcMain.Wdt / 8, rcMain.Hgt / 5, rcMain.Wdt * 11 / 16, rcMain.Hgt * 1 / 8);
	rcBottomButtons = C4Rect(rcMain.Wdt / 8, rcQuestionWindow.GetBottom(), rcMain.Wdt * 11 / 16, rcMain.Hgt * 2 / 8);
	C4Rect rcFeedback = C4Rect(rcMain.Wdt / 6, rcQuestionWindow.GetBottom()+5, rcMain.Wdt * 10 / 16, rcMain.Hgt * 1 / 16);
	feedbackQs = new C4GUI::Edit(rcFeedback);
	feedbackQs->SetFont(&C4Startup::Get()->Graphics.BookFont);
	feedbackQs->InsertText("Write feedback here", false);
	feedbackQs->SetMaxText(FEEDBACKBUFFER);
	feedbackQs->DoNothing = true;
	feedbackQs->SetVisibility(false);
	AddElement(feedbackQs);

	AddElement(instructionsWindow = new C4GUI::TextWindow(rcInstructionsWindow, 0, 0, 0, 100, 4096, "  ", false, NULL, 0, true));
	AddElement(questionWindow = new C4GUI::TextWindow(rcQuestionWindow, 0, 0, 0, 100, 4096, "  ", false, NULL, 0, true));
	questionWindow->SetDecoration(true, true, &C4Startup::Get()->Graphics.sfctBookScroll, true);
	instructionsWindow->SetDecoration(true, true, &C4Startup::Get()->Graphics.sfctBookScroll, true);
	questionWindow->UpdateHeight();
	instructionsWindow->UpdateHeight();
	instructionsWindow->AddTextLine(FormatString(LoadResStr("SURVEY_INSTRUCTIONS")).getData(), &C4Startup::Get()->Graphics.BookFont, ClrPlayerItem, false, false);
	DoNext();

	C4Rect rcDefault(0, 0, 10, 10);
	AddElement(btnBack = new C4GUI::CallbackButton<Survey>(LoadResStr("IDS_BTN_BACK_MENU"), rcDefault, &Survey::OnBackBtn));
	AddElement(btnSubmit = new C4GUI::CallbackButton<Survey>(LoadResStr("IDS_BTN_SUBMIT"), rcDefault, &Survey::OnSubmitBtn));
	AddElement(btnVeryUnimpt = new C4GUI::CallbackButton<Survey>(LoadResStr("SURVEY_1"), rcDefault, &Survey::OnVeryUnimptBtn));
	AddElement(btnUnimpt = new C4GUI::CallbackButton<Survey>(LoadResStr("SURVEY_2"), rcDefault, &Survey::OnUnimptBtn));
	AddElement(btnImpt = new C4GUI::CallbackButton<Survey>(LoadResStr("SURVEY_3"), rcDefault, &Survey::OnImptBtn));
	AddElement(btnVeryImpt = new C4GUI::CallbackButton<Survey>(LoadResStr("SURVEY_4"), rcDefault, &Survey::OnVeryImptBtn));
	UpdateBottomButtons();
}

//Updates profile
int Survey::ModifyProfile()
{
	PlayerProfile::SendFeedback(result[0], result[1], result[2], result[3], feedbackChar);
	return 1;
}

void Survey::DoBack()
{
	// back 2 main, restart quiz
	if (currQs < NUM_QUESTIONS+1) {
		StdStrBuf sError;
		sError.Format(LoadResStr("IDS_MSG_INCOMPLETESURVEY_MSG"));
		GetScreen()->ShowMessage(sError.getData(), LoadResStr("IDS_MSG_INCOMPLETESURVEY"), C4GUI::Ico_Error);
	}
	currQs = 0;
	C4Startup::Get()->SwitchDialog(C4Startup::SDID_Back);
}

void Survey::DoNext()
{	
	ShowQuestion(++currQs);
}

void Survey::DoNext(int feedback)
{
	if(currQs < NUM_QUESTIONS)
		result[currQs - 1] = feedback;
	else if (currQs == NUM_QUESTIONS) {
		StdStrBuf feedbackStr(feedbackQs->GetText());
		SCopy(feedbackStr.getData(), feedbackChar, FEEDBACKBUFFER);
	}

	ShowQuestion(++currQs);
}

//Handles question rotation and warnings
void Survey::ShowQuestion(int index) {
	questionWindow->ClearText(true);
	if (index > 0 && index <= NUM_QUESTIONS)
	{
		char displayStr[20] = "SURVEY_QUESTION";
		char number[5];
		itoa(index, number, 10);
		strcat(displayStr, number);
		questionWindow->AddTextLine(FormatString(LoadResStr(displayStr)).getData(), &C4Startup::Get()->Graphics.BookFont, ClrPlayerItem, false, false);
		if (index == NUM_QUESTIONS) {
			btnVeryUnimpt->SetVisibility(false);
			btnUnimpt->SetVisibility(false);
			btnImpt->SetVisibility(false);
			btnVeryImpt->SetVisibility(false);
			feedbackQs->SetVisibility(true);
			btnSubmit->SetVisibility(true);
		}
	}
	else if (index > NUM_QUESTIONS) {
		ModifyProfile();
		feedbackQs->SetVisibility(false);
		btnSubmit->SetVisibility(false);
		questionWindow->AddTextLine(FormatString(LoadResStr("SURVEY_THANKS")).getData(), &C4Startup::Get()->Graphics.BookFont, ClrPlayerItem, false, false);	
	}
}

void Survey::UpdateBottomButtons()
{
	// bottom line buttons depend on list mode
	C4GUI::ComponentAligner caBottomButtons(rcBottomButtons, 0, 0);

	btnBack->SetToolTip(LoadResStr("IDS_DLGTIP_BACKMAIN"));
	btnBack->SetBounds(caBottomButtons.GetGridCell(0, 6, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnSubmit->SetBounds(caBottomButtons.GetGridCell(3, 6, 0, 1, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnSubmit->SetVisibility(false);
	btnVeryUnimpt->SetBounds(caBottomButtons.GetGridCell(0, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnUnimpt->SetBounds(caBottomButtons.GetGridCell(1, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnImpt->SetBounds(caBottomButtons.GetGridCell(2, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));
	btnVeryImpt->SetBounds(caBottomButtons.GetGridCell(3, 4, 0, 3, iBottomButtonWidth, C4GUI_ButtonHgt, true));

}

Survey::~Survey()
{
}
