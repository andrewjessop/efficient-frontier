
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <iostream>
#include "ParseYahoo.hh"

using namespace std;

void
ParseYahoo::ParseASX200(string& html)
{
	htmlcxx::HTML::ParserDom parser;
	Tree dom = parser.parseTree(html);
	//cout << dom.size() << endl;

	// Find the table of interest
	for (TreeIt it = dom.begin(); it != dom.end(); ++it)
	{
		if (it->tagName() == "table")
		{
			it->parseAttributes();
			pair<bool, string> result(it->attribute("class"));
			if (result.first && result.second == "yfnc_tableout1")
			{
				cout << it->text() << endl;
				//cout << result.second << endl;

				//printSiblings(dom, it);
				printChildren(dom, it);
				cout << it->closingText() << endl;
			}
		}
	}
}

void
ParseYahoo::printSiblings(Tree& dom, TreeIt& oldIt)
{
	cout << "printSiblings()" << endl;
	cout << "-----------------------" << endl;

	TreeIt it(dom.begin(dom.parent(oldIt)));
	while(dom.is_valid(it))
	{
		cout << it->text() << endl;
		cout << it->closingText() << endl;
		it = dom.next_sibling(it);
	}
	cout << "-----------------------" << endl;
}

void
ParseYahoo::printChildren(Tree& dom, TreeIt& oldIt)
{
	//cout << "printChildren()" << endl;

	TreeIt it(dom.begin(oldIt));
	while(dom.is_valid(it))
	{
		string str(trim(it->text()));
		if (it->isTag())
		{
			cout << it->text() << endl;
			printChildren(dom, it);
			cout << it->closingText() << endl;
		}
		else if (!str.empty())
		{
			cout << str << endl;
		}
		it = dom.next_sibling(it);
	}
}

const string
ParseYahoo::trim(const string& pString, const string& pWhitespace)
{
    const size_t beginStr = pString.find_first_not_of(pWhitespace);
    if (beginStr == string::npos)
    {
        // no content
        return "";
    }

    const size_t endStr = pString.find_last_not_of(pWhitespace);
    const size_t range = endStr - beginStr + 1;

    return pString.substr(beginStr, range);
}
