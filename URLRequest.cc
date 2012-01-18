
#include "URLRequest.hh"
#include <curl/curl.h>
#include <iostream>

using namespace std;

extern "C" size_t
write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
	if (size * nmemb > 0)
	{
		const std::string data(
			reinterpret_cast<const char*>(buffer), (size * nmemb)
			); 
		reinterpret_cast<URLRequest*>(userp)->writeFunction(data);
		return (size * nmemb);
	}
	else
	{
		return 0;
	}
}

URLRequest::URLRequest(const string& url):
	myUrl(url),
	myData("")
{

}

void
URLRequest::writeFunction(const string& data)
{
	cerr << "writeFunction.  Cur Data Size: " << myData.length() << endl;
	myData.append(data);
}

void
URLRequest::send()
{
	sendRequest();
}

const string
URLRequest::getData()
{
	return myData;
}

void
URLRequest::sendRequest()
{
	CURL* curlHandle(curl_easy_init());
	if (curlHandle) 
	{
		curl_easy_setopt(curlHandle, CURLOPT_URL, myUrl.c_str());
		curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, this);
		CURLcode result(curl_easy_perform(curlHandle));
		if(result != 0)
		{
			cerr << "URLRequest::sendRequest()\n" <<
				"curl_easy_perform() failed" << endl;
		}
		curl_easy_cleanup(curlHandle);
	}
	else
	{
		cerr << "URLRequest::sendRequest()\n" <<
			"Call to curl_easy_init() failed" << endl;
	}
}
