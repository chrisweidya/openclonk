//Created by Chris
//Player profile handling, see function for comments


#include <C4Include.h>
#include <C4StartupNetDlg.h>
#include <time.h>
#include <DBConnector.h>
#include <dlib/svm.h>
using namespace dlib;

PlayerProfile::PlayerProfile()
{	
	Default();
}
void PlayerProfile::Default()
{
}

//Parses data taken from scenario for sending to database
//Categorisation of player 
//Sends parsed data to database
void PlayerProfile::Evaluate(int32_t keyboardPresses, int32_t clicks, int32_t secondsInRound, int32_t restarts, const char * name) {
	float apm = keyboardPresses * 60.0 / secondsInRound ;
	keyboardAPM = (int)apm;
	float cpm = clicks * 60.0 / secondsInRound;
	mouseAPM = (int)cpm;
	round++;
	restartCount = restarts;
	timeTakenToComplete = secondsInRound;
	int32_t percentageBatDeaths = 0;
	
	Categorise();
	if (achievementLevel > 0 && batDeaths > 0)
		percentageBatDeaths = batDeaths * 100 / (6 * (achievementLevel - category));

	std::string nameStr(name);
	std::string dataStr = "username=" + nameStr + "&achievementScore=" + std::to_string(achievementScore) + "&socialScore=" + std::to_string(socialScore) +
		"&immersionScore=" + std::to_string(immersionScore) + "&achievementLevel=" + std::to_string(achievementLevel) +
		"&immersionLevel=" + std::to_string(immersionLevel) + "&achResult=" + std::to_string(achResult) + "&immResult=" + std::to_string(immResult) +
		"&round=" + std::to_string(round) + "&seed=" + std::to_string(seed) +
		"&restarts=" + std::to_string(restarts) +"&immersionChoices=" + std::to_string(immersionChoices) + 
		"&achievementChoices=" + std::to_string(achievementChoices) + "&roundTime=" + std::to_string(timeTakenToComplete) + 
		"&keyboardAPM=" + std::to_string(keyboardAPM) + "&mouseAPM=" + std::to_string(mouseAPM) +"&playerDeaths=" + std::to_string(playerDeaths) +
		"&batDeaths=" + std::to_string(percentageBatDeaths) + "&treesChopped=" + std::to_string(treesChopped) + "&immersionTime=" + std::to_string(immersionTime) +
		"&achievementTime=" + std::to_string(achievementTime) + "&objectiveCompleted=" + std::to_string(objectiveCompleted);
	const char* sendData = dataStr.c_str();

	char * hostname = "http://openclonkplus.comp.nus.edu.sg/experiment2.php";
	DBConnector db_connector = DBConnector();
	db_connector.Execute(sendData, hostname);
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

//Handles player survey data and sends it to database
void PlayerProfile::SendFeedback(int ans1, int ans2, int ans3, int ans4, char * feedback) {
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return;
	core.Profile.doneQuestionnaire = true;
	
	std::cout << "here";
	std::string nameStr(szPlayerFilename);
	std::string dataStr = "username=" + nameStr + "&achievementScore=" + std::to_string(core.Profile.achievementScore) + "&socialScore=" + std::to_string(core.Profile.socialScore) +
		"&immersionScore=" + std::to_string(core.Profile.immersionScore) + "&achievementLevel=" + std::to_string(core.Profile.achievementLevel) +
		"&immersionLevel=" + std::to_string(core.Profile.immersionLevel) + "&question1=" + std::to_string(ans1) + "&question2=" + std::to_string(ans2) +
		"&question3=" + std::to_string(ans3) + "&question4=" + std::to_string(ans4);

	std::string feedback1(feedback);
	dataStr += "&feedback=" + feedback1;
	const char* sendData = dataStr.c_str();
	std::cout << sendData << "\n";
	char * hostname = "http://openclonkplus.comp.nus.edu.sg/feedback2.php";
	DBConnector db_connector = DBConnector();
	db_connector.Execute(sendData, hostname);
	if (!PlayerGrp.Close())
		return;
}

//Categorisation of player using .dat files from c_svm algorithm based on in-game variables
void PlayerProfile::Categorise() {
	typedef matrix<double, 8, 1> sample_type;
	typedef radial_basis_kernel<sample_type> kernel_type; 
	typedef decision_function<kernel_type> dec_funct_type;
	typedef normalized_function<dec_funct_type> funct_type;
	funct_type learned_function;
	sample_type sample;
	
	sample(0) = keyboardAPM;
	sample(1) = mouseAPM;
	sample(2) = timeTakenToComplete;
	sample(3) = batDeaths;
	sample(4) = playerDeaths;
	sample(5) = immersionTime;
	sample(6) = achievementTime;
	sample(7) = objectiveCompleted;
	deserialize("achievement_result.dat") >> learned_function;
	achResult = learned_function(sample);
	std::cout << "ach result " << achResult;
	deserialize("immersion_result.dat") >> learned_function;
	immResult = learned_function(sample);
	std::cout << "imm result " << immResult;

	if (achResult < immResult)
		category += 1;
	else
		category -= 1;
	if (category > 2)
		category = 2;
	if (category < -2)
		category = -2;
}

void PlayerProfile::updatePlayerType(float achievementScore, float socialScore, float immersionScore)
{
	Config.General.Participants[0];
}

int32_t PlayerProfile::getScoreDiff() {
	return category;
}

//Gets current seed for game session
int32_t PlayerProfile::getSeed(bool init) {	
	int32_t tempSeed;
	if (init) {
		tempSeed = seed = time(NULL);
		PlayerProfile::saveSeed(tempSeed);
		return tempSeed;
	}
	else {
		tempSeed = seed;
		std::cout << "getting" << seed << "\n";
		return tempSeed;
	}
}

//Saves seed of rescued NPC
void PlayerProfile::updateFoundNPC(int seed) {
	for (int i = 0; i < foundNPCSize; i++) {
		if (foundNPC[i] == 0) {
			foundNPC[i] = seed;
			break;
		}
	}	
}

//Saves data taken from game session 
void PlayerProfile::updateProfileData(int32_t v_playerDeaths, int32_t v_batDeaths, int32_t v_treesChopped,
	int32_t v_immersionTime, int32_t v_achievementTime, int32_t v_objectiveCompleted) {
	playerDeaths = v_playerDeaths;
	batDeaths = v_batDeaths;
	treesChopped = v_treesChopped;
	immersionTime = v_immersionTime;
	achievementTime = v_achievementTime;
	objectiveCompleted = v_objectiveCompleted;
}

//Gets seed of rescued NPC
int32_t PlayerProfile::getFoundNPC(int index) {
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

//Gets and loads player profile from saved profile
PlayerProfile* PlayerProfile::getSingleProfile() {
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore nfo;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !nfo.Load(PlayerGrp) || !PlayerGrp.Close())
		return nullptr;
	
	return &nfo.Profile;
}

//Saves player profile
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

int32_t PlayerProfile::saveSeed(int32_t seed) {

	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return -1;
	core.Profile.seed = seed;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
	return 1;
}

//Supposed to be save list of rescued NPC, however transformed to data clearing function
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
	return 1;
}

//Saves questionnaire results, achievement immersion and social scores after questionnaire completion.
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
	core.Profile.doneQuestionnaire = true;
	if (!core.Save(PlayerGrp) || !PlayerGrp.Close())
		return -1;
	return 1;
}

//Checks if player has completed questionnaire
bool PlayerProfile::getDoneQuestionnaire() {
	assert(SModuleCount(Config.General.Participants) == 1);
	C4Group PlayerGrp;
	C4PlayerInfoCore core;
	const char *szPlayerFilename = Config.AtUserDataPath(Config.General.Participants);
	if (!FileExists(szPlayerFilename) || !PlayerGrp.Open(szPlayerFilename) || !core.Load(PlayerGrp))
		return false;
	if (!PlayerGrp.Close())
		return -1;
	return core.Profile.doneQuestionnaire;
}

//Function to save various variables to openclonk .ocp file
void PlayerProfile::CompileFunc(StdCompiler *pComp)
{
	pComp->Value(mkNamingAdapt(doneQuestionnaire, "doneQuestionnaire",false));
	pComp->Value(mkNamingAdapt(achievementScore, "achievementScore", 0));
	pComp->Value(mkNamingAdapt(socialScore, "socialScore", 0));
	pComp->Value(mkNamingAdapt(immersionScore, "immersionScore", 0));
	pComp->Value(mkNamingAdapt(achievementLevel, "achievementLevel", 0));
	pComp->Value(mkNamingAdapt(immersionLevel, "immersionLevel", 0));
	pComp->Value(mkNamingAdapt(category, "category", 0));
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