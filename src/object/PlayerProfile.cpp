
#include <C4Include.h>
#include <C4StartupNetDlg.h>

PlayerProfile::PlayerProfile()
{	
	Default();
}
void PlayerProfile::Default()
{
}

void PlayerProfile::updatePlayerType(float achievementScore, float socialScore, float immersionScore)
{
	Config.General.Participants[0];
}

int32_t PlayerProfile::getScoreDiff() {
	int32_t scoreDiff = immersionPoints - achievementPoints;
	return 2;
	if (scoreDiff > 2)
		return 2;
	if (scoreDiff < -2)
		return -2;
	return scoreDiff;
}

PlayerProfile* PlayerProfile::getSingleProfile() {
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore nfo;
//	PlayerProfile profile;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
//	std::cout << "getprofile\n";
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !nfo.Load(PlayerGrp) || !PlayerGrp.Close())
		return nullptr;
//	profile = nfo.Profile;
//	std::cout << "before: " << nfo.Profile.achievementScore << "\n";
	
	return &nfo.Profile;
}


int32_t PlayerProfile::saveSingleProfile(PlayerProfile profile) {	
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);	
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	core.Profile = profile;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
//	std::cout << "-->" << profile.achievementScore << "\n";
	return 1;
} 

void PlayerProfile::CompileFunc(StdCompiler *pComp)
{
	pComp->Value(mkNamingAdapt(achievementScore, "achievementScore", 0));
	pComp->Value(mkNamingAdapt(socialScore, "socialScore", 0));
	pComp->Value(mkNamingAdapt(immersionScore, "immersiontScore", 0));
	pComp->Value(mkNamingAdapt(achievementPoints, "achievementPoints", 0));
	pComp->Value(mkNamingAdapt(immersionPoints, "immersionPoints", 0));
}