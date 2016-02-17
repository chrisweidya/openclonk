#ifndef _DBCONNECTOR_H_INCLUDED_
#define _DBCONNECTOR_H_INCLUDED_
#include <curl/curl.h>

class DBConnector {
private:
	CURL *curl;
	CURLcode res;
	char* hostname = "http://openclonkplus.comp.nus.edu.sg/experiment1.php";
//	char* options = "username=testname&achievementScore=1&socialScore=2&immersionScore=2&achievementLevel=2&immersionLevel=23&round=2&seed=1234&restarts=3&immersionChoices=0&achievementChoices=1&roundTime=60&keyboardAPM=9000&mouseAPM=9001&playerDeaths=3&batDeaths=4&treesChopped=5&immersionTime=55&achievementTime=55&objectiveCompleted=2";
//	char* options = "id=5&name=e1ample";
public:
	DBConnector();
	bool Execute(const char * options);
};

#endif