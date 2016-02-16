#ifndef _DBCONNECTOR_H_INCLUDED_
#define _DBCONNECTOR_H_INCLUDED_
#include <curl/curl.h>

class DBConnector {
private:
	CURL *curl;
	CURLcode res;
	char* hostname = "http://openclonkplus.comp.nus.edu.sg/test_data.php";
	char* options = "id=5&participant_name=e1ample";
public:
	DBConnector();
	bool Execute();
};

#endif