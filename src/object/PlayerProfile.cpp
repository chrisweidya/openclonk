
#include <C4Include.h>
#include <C4StartupNetDlg.h>
#include <time.h>

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
	int32_t scoreDiff = immersionLevel - achievementLevel;
	return -2;
	if (scoreDiff > 2)
		return 2;
	if (scoreDiff < -2)
		return -2;
	return scoreDiff;
}

int32_t PlayerProfile::getSeed(bool init) {	
	if (init) {
		int32_t tempSeed;
		tempSeed = seed = time(NULL);
		std::cout << tempSeed << "\n";
		saveSingleProfile(*this);
		return tempSeed;
	}
	std::cout <<"getting"<< seed << "\n";
	return seed;
}

void PlayerProfile::updateFoundNPC(int seed) {
	for (int i = 0; i < foundNPCSize; i++) {
		if (foundNPC[i] == 0) {
			foundNPC[i] = seed;
	//		std::cout << i<<"savedfee"<<seed << "\n";
			break;
		}
	}	
}

int32_t PlayerProfile::getFoundNPC(int index) {
	return foundNPC[index];
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
	return 1;
} 

void PlayerProfile::CompileFunc(StdCompiler *pComp)
{
	pComp->Value(mkNamingAdapt(achievementScore, "achievementScore", 0));
	pComp->Value(mkNamingAdapt(socialScore, "socialScore", 0));
	pComp->Value(mkNamingAdapt(immersionScore, "immersionScore", 0));
	pComp->Value(mkNamingAdapt(achievementLevel, "achievementLevel", 0));
	pComp->Value(mkNamingAdapt(immersionLevel, "immersionLevel", 0));
	pComp->Value(mkNamingAdapt(seed, "seed", 0));
	pComp->Value(mkNamingAdapt(toC4CArr(foundNPC), "foundNPC"));
}