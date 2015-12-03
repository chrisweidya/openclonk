#include <PlayerProfile.h>
#include <C4Include.h>
#include <C4StartupNetDlg.h>

PlayerProfile::PlayerProfile()
{	

}

void PlayerProfile::setAchievementScore(float score)
{
	Config.General.Participants[0];
	achievementScore = score;
}

void PlayerProfile::updatePlayerType(float achievementScore, float socialScore, float immersionScore)
{
	Config.General.Participants[0];
}

PlayerProfile* PlayerProfile::getSingleProfile() {
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore nfo;
	PlayerProfile profile;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	std::cout << "getprofile\n";
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !nfo.Load(PlayerGrp))
		return nullptr;
	profile = nfo.Profile;
	std::cout << "before: " << profile.achievementScore << "\n";
	profile.achievementScore = 3.0;
	nfo.Profile = profile;
	C4PlayerInfoCore &newCore = nfo;
	if (!newCore.Save(PlayerGrp) || !PlayerGrp.Close())
		return nullptr;
	std::cout << "-->" << newCore.Profile.achievementScore << "\n";
	return &nfo.Profile;
}


int PlayerProfile::saveSingleProfile(PlayerProfile profile) {	
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);	
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	core.Profile = profile;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
	std::cout << "-->" << profile.achievementScore << "\n";
	return 1;
} 

