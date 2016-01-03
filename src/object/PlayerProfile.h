#ifndef INC_PLAYERPROFILE
#define INC_PLAYERPROFILE

class PlayerProfile
{
public:
	PlayerProfile();
	int32_t achievementScore = 0;
	int32_t socialScore = 0;
	int32_t immersionScore = 0;
	int32_t achievementPoints = 0;
	int32_t immersionPoints = 0;
	int32_t seed = 0;

	int32_t foundNPCSize = 5;
	int32_t foundNPC[5] = { 0, 0, 0, 0, 0 };

	void updatePlayerType(float achievementScore, float socialScore, float immersionScore);
	int32_t getScoreDiff();
	int32_t getSeed(bool init);

	void updateFoundNPC(int seed);
	int32_t getFoundNPC(int index);
	static PlayerProfile *getSingleProfile();
	static int32_t saveSingleProfile(PlayerProfile profile);

	void Default();
	void CompileFunc(StdCompiler *pComp);

private:


};

#endif
