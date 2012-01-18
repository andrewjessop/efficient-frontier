#ifndef URLRequest_hh
#define URLRequest_hh

#include <string>

class URLRequest
{
public:
	URLRequest(const std::string& url);

	void send();
	const std::string getData();

	// used internally (TODO, could be hidden by Impl)
	void writeFunction(const std::string& data);
private:
	// Curl request wrapper
	void sendRequest();

	std::string myUrl;
	std::string myData;
};

#endif
