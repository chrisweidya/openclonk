#ifndef INC_PLAYERPROFILE
#define INC_PLAYERPROFILE

class PlayerProfile
{
public:
	PlayerProfile();
	int32_t achievementScore=0;
	int32_t socialScore=0;
	int32_t immersionScore=0;
	void updatePlayerType(float achievementScore, float socialScore, float immersionScore);
	static PlayerProfile *getSingleProfile();
	static int saveSingleProfile(PlayerProfile profile);

	void Default();
	void CompileFunc(StdCompiler *pComp);

private:


};

#endif
