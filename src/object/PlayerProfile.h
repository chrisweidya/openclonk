#ifndef INC_PLAYERPROFILE
#define INC_PLAYERPROFILE

class PlayerProfile
{
public:
	PlayerProfile();
	//Player scores
	bool doneQuestionnaire = false;
	int32_t achievementScore = 0;
	int32_t socialScore = 0;
	int32_t immersionScore = 0;

	//map creation params
	int32_t achievementLevel = 0;
	int32_t immersionLevel = 0;
	int32_t category = 0;
	int32_t seed = 0;
	int32_t foundNPCSize = 5;
	int32_t foundNPC[5] = { 0, 0, 0, 0, 0 };
	int32_t buildingsCompleted = 0;

	//Game data
	int32_t round = 0;
	int32_t restartCount = 0;
	int32_t immersionChoices = 0;
	int32_t achievementChoices = 0;
	int32_t timeTakenToComplete = 0;
	int32_t keyboardAPM = 0;
	int32_t mouseAPM = 0;
	int32_t playerDeaths = 0;
	int32_t batDeaths = 0;
	int32_t treesChopped = 0;
	int32_t immersionTime = 0;
	int32_t achievementTime = 0;
	int32_t objectiveCompleted = 0;

	void Evaluate(int32_t keyboardPresses, int32_t clicks, int32_t secondsInRound, int32_t restarts, const char * name);
	static void SendFeedback(int ans1, int ans2, int ans3, int ans4, char * feedback);
	void Categorise();

	//profile saving or loading
	void updatePlayerType(float achievementScore, float socialScore, float immersionScore);
	int32_t getScoreDiff();
	int32_t getSeed(bool init);
	int32_t saveSeed(int32_t seed);
	static int32_t saveNPC(int32_t npc1, int32_t npc2, int32_t npc3, int32_t npc4, int32_t npc5);
	static int32_t saveQuestionnaireData(int32_t achievementSCore, int32_t socialScore, int32_t immersionScore);
	static bool getDoneQuestionnaire();
	void updateFoundNPC(int seed);
	int32_t getFoundNPC(int index);
	void updateBuildingsCompleted();
	int32_t getBuildingsCompleted();
	void updateProfileData(int32_t playerDeaths, int32_t batDeaths, int32_t treesChopped,
		int32_t immersionTime, int32_t achievementTime, int32_t objectiveCompleted);

	static PlayerProfile *getSingleProfile();
	static int32_t saveSingleProfile(PlayerProfile profile);

	void Default();
	void CompileFunc(StdCompiler *pComp);

private:


};

#endif
