#include <DBConnector.h>


DBConnector::DBConnector(){
}

bool DBConnector::Execute() {
		
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, hostname);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, options);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return true;
}

