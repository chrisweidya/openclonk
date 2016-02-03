
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

void PlayerProfile::Evaluate(int32_t keyboardPresses, int32_t clicks, int32_t secondsInRound) {
	std::cout << "cpm before: " << mouseAPM << "\n";
	float apm = keyboardPresses * 60.0 / secondsInRound ;
	keyboardAPM = (int)apm;
	float cpm = clicks * 60.0 / secondsInRound;
	mouseAPM = (int)cpm;
	std::cout << "cpm: " << mouseAPM << "\n";
}

void PlayerProfile::updatePlayerType(float achievementScore, float socialScore, float immersionScore)
{
	Config.General.Participants[0];
}

int32_t PlayerProfile::getScoreDiff() {
	int32_t scoreDiff = immersionLevel - achievementLevel;
	if (scoreDiff > 2)
		return 2;
	if (scoreDiff < -2)
		return -2;
	return scoreDiff;
}

int32_t PlayerProfile::getSeed(bool init) {	
	int32_t tempSeed;
	if (init) {
		tempSeed = seed = time(NULL);
//		std::cout << seed << "seedbefore\n";
		PlayerProfile::saveSeed(tempSeed);
//		std::cout << seed << "seedafter\n";
		return tempSeed;
	}
	else {
		tempSeed = seed;
		std::cout << "getting" << seed << "\n";
		return tempSeed;
	}
}

void PlayerProfile::updateFoundNPC(int seed) {
	for (int i = 0; i < foundNPCSize; i++) {
		if (foundNPC[i] == 0) {
			foundNPC[i] = seed;
			std::cout << i<<"savedfee"<<seed << "\n";
			break;
		}
	}	
}

int32_t PlayerProfile::getFoundNPC(int index) {
//	std::cout << "found npc " << foundNPC[index] << "\n";
	int32_t npc_seed = foundNPC[index];
	std::cout << "found npc2 " << npc_seed << "\n";
	return npc_seed;
}

void PlayerProfile::updateBuildingsCompleted() {
	buildingsCompleted++;
}

int32_t PlayerProfile::getBuildingsCompleted() {
	int32_t count = buildingsCompleted;
	std::cout << timeTakenToComplete << "check \n";
	return count;
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
	std::cout << profile.seed << " saving profile\n";
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	core.Profile = profile;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
	std::cout <<core.Profile.seed << " saving profile\n";
	return 1;
} 

int32_t PlayerProfile::saveSeed(int32_t seed) {

	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	std::cout << seed << " seed\n";
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	core.Profile.seed = seed;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
	std::cout << core.Profile.seed << " 2seed\n";
	return 1;
}

int32_t PlayerProfile::saveNPC(int32_t npc1, int32_t npc2, int32_t npc3, int32_t npc4, int32_t npc5) {

	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	core.Profile.foundNPC[0] = npc1;
	core.Profile.foundNPC[1] = npc2;
	core.Profile.foundNPC[2] = npc3;
	core.Profile.foundNPC[3] = npc4;
	core.Profile.foundNPC[4] = npc5;
	core.Profile.achievementLevel = 0;
	core.Profile.immersionLevel = 0;
	core.Profile.keyboardAPM = 0;
	core.Profile.mouseAPM = 0;
	core.Profile.timeTakenToComplete = 0;
	core.Profile.buildingsCompleted = 0;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
	std::cout << core.Profile.foundNPC[0] << " npc\n";
	return 1;
}

int32_t PlayerProfile::saveQuestionnaireData(int32_t achievementScore, int32_t socialScore, int32_t immersionScore) {

	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	std::cout << core.Profile.achievementScore << " " << core.Profile.socialScore << " " << core.Profile.immersionScore << "after \n";
	core.Profile.achievementScore = achievementScore;
	core.Profile.socialScore = socialScore;
	core.Profile.immersionScore = immersionScore;
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
	pComp->Value(mkNamingAdapt(buildingsCompleted, "buildingsCompleted", 0));

	pComp->Value(mkNamingAdapt(timeTakenToComplete, "timeTakenToComplete", 0));
	pComp->Value(mkNamingAdapt(keyboardAPM, "keyboardAPM", 0));
	pComp->Value(mkNamingAdapt(mouseAPM, "mouseAPM", 0));
}