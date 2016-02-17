
#include <C4Include.h>
#include <C4StartupNetDlg.h>
#include <time.h>
#include <DBConnector.h>

PlayerProfile::PlayerProfile()
{	
	Default();
}
void PlayerProfile::Default()
{
}

void PlayerProfile::Evaluate(int32_t keyboardPresses, int32_t clicks, int32_t secondsInRound, int32_t restarts, const char * name) {
	float apm = keyboardPresses * 60.0 / secondsInRound ;
	keyboardAPM = (int)apm;
	float cpm = clicks * 60.0 / secondsInRound;
	mouseAPM = (int)cpm;
	round++;
	restartCount = restarts;

	std::string nameStr(name);
	std::string dataStr = "username=" + nameStr + "&achievementScore=" + std::to_string(achievementScore) + "&socialScore=" + std::to_string(socialScore) +
		"&immersionScore=" + std::to_string(immersionScore) + "&achievementLevel=" + std::to_string(achievementLevel) +
		"&immersionLevel=" + std::to_string(immersionLevel) + "&round=" + std::to_string(round) + "&seed=" + std::to_string(seed) +
		"&restarts=" + std::to_string(restarts) +"&immersionChoices=" + std::to_string(immersionChoices) + 
		"&achievementChoices=" + std::to_string(achievementChoices) + "&roundTime=" + std::to_string(timeTakenToComplete) + 
		"&keyboardAPM=" + std::to_string(keyboardAPM) + "&mouseAPM=" + std::to_string(mouseAPM) +"&playerDeaths=" + std::to_string(playerDeaths) +
		"&batDeaths=" + std::to_string(batDeaths) + "&treesChopped=" + std::to_string(treesChopped) + "&immersionTime=" + std::to_string(immersionTime) +
		"&achievementTime=" + std::to_string(achievementTime) + "&objectiveCompleted=" + std::to_string(objectiveCompleted);
	const char* sendData = dataStr.c_str();

	DBConnector db_connector = DBConnector();
	db_connector.Execute(sendData);
	std::cout << "seed " << seed << "\n";
	std::cout << "name " << name << "\n";
	std::cout << "round " << round << "\n";
	std::cout << "restartCount " << restartCount << "\n";
	std::cout << "immersionChoices " << immersionChoices << "\n";
	std::cout << "achievementChoices " << achievementChoices << "\n";
	std::cout << "timeTakenToComplete " << timeTakenToComplete << "\n";
	std::cout << "keyboardAPM " << keyboardAPM << "\n";
	std::cout << "mouseAPM " << mouseAPM << "\n";
	std::cout << "playerDeaths " << playerDeaths << "\n";
	std::cout << "batDeaths " << batDeaths << "\n";
	std::cout << "treesChopped " << treesChopped << "\n";
	std::cout << "immersionTime " << immersionTime << "\n";
	std::cout << "achievementTime " << achievementTime << "\n";
	std::cout << "objectiveCompleted " << objectiveCompleted << "\n";
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

void PlayerProfile::updateProfileData(int32_t v_playerDeaths, int32_t v_batDeaths, int32_t v_treesChopped,
	int32_t v_immersionTime, int32_t v_achievementTime, int32_t v_objectiveCompleted) {
	playerDeaths = v_playerDeaths;
	batDeaths = v_batDeaths;
	treesChopped = v_treesChopped;
	immersionTime = v_immersionTime;
	achievementTime = v_achievementTime;
	objectiveCompleted = v_objectiveCompleted;
}

int32_t PlayerProfile::getFoundNPC(int index) {
//	std::cout << "found npc " << foundNPC[index] << "\n";
	int32_t npc_seed = foundNPC[index];
	return npc_seed;
}

void PlayerProfile::updateBuildingsCompleted() {
	buildingsCompleted++;
}

int32_t PlayerProfile::getBuildingsCompleted() {
	int32_t count = buildingsCompleted;
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
	core.Profile.playerDeaths = 0;
	core.Profile.batDeaths = 0;
	core.Profile.treesChopped = 0;
	core.Profile.immersionTime = 0;
	core.Profile.achievementTime = 0;
	core.Profile.objectiveCompleted = 0;
	core.Profile.immersionChoices = 0;
	core.Profile.achievementChoices = 0;
	core.Profile.restartCount = 0;
	core.Profile.round = 0;
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

	pComp->Value(mkNamingAdapt(round, "round", 0));
	pComp->Value(mkNamingAdapt(restartCount, "restartCount", 0));
	pComp->Value(mkNamingAdapt(immersionChoices, "immersionChoices", 0));
	pComp->Value(mkNamingAdapt(achievementChoices, "achievementChoices", 0));
	pComp->Value(mkNamingAdapt(timeTakenToComplete, "timeTakenToComplete", 0));
	pComp->Value(mkNamingAdapt(keyboardAPM, "keyboardAPM", 0));
	pComp->Value(mkNamingAdapt(mouseAPM, "mouseAPM", 0));
	pComp->Value(mkNamingAdapt(playerDeaths, "playerDeaths", 0));
	pComp->Value(mkNamingAdapt(batDeaths, "batDeaths", 0));
	pComp->Value(mkNamingAdapt(treesChopped, "treesChopped", 0));
	pComp->Value(mkNamingAdapt(immersionTime, "immersionTime", 0));
	pComp->Value(mkNamingAdapt(achievementTime, "achievementTime", 0));
	pComp->Value(mkNamingAdapt(objectiveCompleted, "objectiveCompleted", 0));
}