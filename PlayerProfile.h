#ifndef INC_PLAYERPROFILE
#define INC_PLAYERPROFILE

class PlayerProfile
{
public:
	PlayerProfile();
	float achievementScore=1.0;

	enum DialogID { SDID_Main = 0, SDID_ScenSel, SDID_ScenSelNetwork, SDID_NetJoin, SDID_Options, SDID_About, SDID_PlrSel, SDID_Back, SDID_Questionnaire };
	void setAchievementScore(float score);
	void updatePlayerType(float achievementScore, float socialScore, float immersionScore);
	static PlayerProfile *getSingleProfile();
	static int saveSingleProfile(PlayerProfile profile);


private:
	float socialScore= 0.0;
	float immersionScore=0.0;


};

#endif
