
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
	TreeIt it = dom.begin();
	while (dom.is_valid(it)) 
	{
		if (it->tagName() == "table")
		{
			it->parseAttributes();
			pair<bool, string> result(it->attribute("class"));
			if (result.first && result.second == "yfnc_tableout1")
			{
				// move past the current table node
				++it;

				// consume the first outer table
				int found(0);
				while (dom.is_valid(it))
				{
					if(it->tagName() == "table")
					{
						++found;
					}
					if (found >= 1)
					{
						// We should now be at the "inner table"
						break;
					}
					++it;
				}
				cerr << "printing... '" << it->tagName() << "'" << endl;

				// Start processing the inner table
				while (dom.is_valid(it))
				{
					// Process table row, by table row
					if (it->tagName() == "tr")
					{
						parseRow(dom, it);
					}
					++it;
				}

				/*
				cout << it->text() << endl;
				printChildren(dom, it);
				cout << it->closingText() << endl;
				*/
			}
		}
		++it;
	}
}

void
ParseYahoo::parseRow(Tree& dom, TreeIt& oldIt)
{
	TreeIt it(oldIt);
	++it; ++it; ++it; ++it;
	if(dom.is_valid(it))
	{
		string ticker(it->text());
		cout << ticker << endl;
	}
}

void
ParseYahoo::printSiblings(Tree& dom, TreeIt& oldIt)
{
	cerr << "printSiblings()" << endl;
	cerr << "-----------------------" << endl;

	TreeIt it(dom.begin(dom.parent(oldIt)));
	while(dom.is_valid(it))
	{
		cout << it->text() << endl;
		cout << it->closingText() << endl;
		it = dom.next_sibling(it);
	}
	cerr << "-----------------------" << endl;
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
