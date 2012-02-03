
#include <iostream>
#include <sstream>
#include <fstream>

#include "ParseYahoo.hh"
#include "URLRequest.hh"

using namespace std;

int main(int argc, char * argv[])
{
/*
 * Reading from a file code
	std::ifstream stream("test1.html");
	std::string html(
		(std::istreambuf_iterator<char>(stream)),
		std::istreambuf_iterator<char>()
		);
	stream.close();
*/

	std::string ticker("BHP");
	std::stringstream url;

	/* TODO: Individual stock URL
	url << "http://ichart.finance.yahoo.com/table.csv?s=" << ticker <<
		"&d=9&e=23&f=2010&g=d&a=01&b=01&c=2000&ignore=.csv";
	*/

	ifstream input("axjo.html");
	string inputData;
	if (!input)
	{
		url << "http://au.finance.yahoo.com/q/cp?s=^AXJO&c=";
		std::cerr << "Downloading file from URL: " << url.str() << std::endl;
		URLRequest request(url.str());
		request.send();
		std::cerr << "Downloaded " << request.getData().size()
			<< " bytes." << std::endl;
		inputData.assign(request.getData());

		ofstream file("axjo.html");
		file << request.getData();
		file.close();
	}
	else
	{
		std::string temp(
			(istreambuf_iterator<char>(input)),
			istreambuf_iterator<char>()
			);
		inputData.assign(temp);
		cerr << "Using existing ASX cache, size: " << temp.length() << endl;
	}

	// parse the html we've read in
	std::string html(inputData);
	ParseYahoo::ParseASX200(html);
	
	return 0;
}


