#ifndef INC_PLAYERPROFILE
#define INC_PLAYERPROFILE

class PlayerProfile
{
public:
	PlayerProfile();
	int32_t achievementScore = 0;
	int32_t socialScore = 0;
	int32_t immersionScore = 0;
	int32_t achievementLevel = 0;
	int32_t immersionLevel = 0;
	int32_t seed = 0;

	int32_t foundNPCSize = 5;
	int32_t foundNPC[5] = { 0, 0, 0, 0, 0 };

	void updatePlayerType(float achievementScore, float socialScore, float immersionScore);
	int32_t getScoreDiff();
	int32_t getSeed(bool init);
	int32_t saveSeed(int32_t seed);
	static int32_t saveNPC(int32_t npc1, int32_t npc2, int32_t npc3, int32_t npc4, int32_t npc5);

	void updateFoundNPC(int seed);
	int32_t getFoundNPC(int index);
	static PlayerProfile *getSingleProfile();
	static int32_t saveSingleProfile(PlayerProfile profile);

	void Default();
	void CompileFunc(StdCompiler *pComp);

private:


};

#endif
