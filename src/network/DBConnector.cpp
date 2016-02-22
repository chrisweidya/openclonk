#include <C4Include.h>
#include <DBConnector.h>
#include <iostream>

DBConnector::DBConnector(){
}

bool DBConnector::Execute(const char * options, char * hostname) {
		
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, hostname);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, options);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);	
	}
	return true;
}

