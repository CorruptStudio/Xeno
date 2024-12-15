#pragma once
#include "Token.h"
#include <string>
#include <vector>

namespace xeno::lexer
{
	class Lexer {
	public:
		explicit Lexer(const std::string& source);
		Token getNextToken();
		std::vector<Token> tokenize();

	private:
		std::string source;
		size_t current;
		int line;
		int column;

		char advance();
		char parseEscapeSequence();
		char peek() const;
		char peekNext() const;
		bool isAtEnd() const;
		void skipWhitespace();
		void skipComment();
		Token identifierOrKeyword();
		Token number();
		Token string();
		Token charLiteral();
		Token singleCharToken(TokenType type);
	};
}