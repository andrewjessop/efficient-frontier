#ifndef ParseYahoo_hh
#define ParseYahoo_hh

#include <htmlcxx/html/ParserDom.h>

class ParseYahoo
{
public:
	typedef tree<htmlcxx::HTML::Node> Tree;
	typedef Tree::iterator TreeIt;

	/// \brief Parse a HTML document, printing out the specific
	/// yahoo specific information required for ASX200
	///
	/// \note This function will modify the string in place if required
	///       to parse the HTML.
	static void ParseASX200(std::string& html);

private:
	static void printSiblings(Tree& dom, TreeIt& oldIt);
	static void printChildren(Tree& dom, TreeIt& oldIt);
	static void parseRow(Tree& dom, TreeIt& oldIt);
	
	static const std::string trim(const std::string& pString,
		const std::string& pWhiteSpace = " \t");
};

#endif // ParseYahoo_hh
