#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/Parser.h"

using namespace xeno::parser;
using namespace xeno::lexer;

std::string readFileContents(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open the file: " + filePath);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

int main()
{
	try {
		std::string sourceCode = readFileContents("examples/testScript.xmod");
		Lexer lexer(sourceCode);

		std::vector<Token> tokens = lexer.tokenize();
/*
		for (const Token& token : tokens)
		{
			std::cout << token.toString() << std::endl;
		}
*/
		Parser parser(tokens);
		auto programNode = parser.parse();
		programNode->printAst();
	}
	catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

	return 0;
}
