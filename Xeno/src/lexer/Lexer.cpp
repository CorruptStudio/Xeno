#include "Lexer.h"
#include <cctype>
#include <sstream>

namespace xeno::lexer
{
	Lexer::Lexer(const std::string& source) : source(source), current(0), line(1), column(0) {}

	char Lexer::advance()
	{
		column++;
		return source[current++];
	}

	char Lexer::parseEscapeSequence()
	{
		char c = advance();

		switch (c)
		{
		case '\'': return '\'';
		case '\"': return '\"';
		case '\\': return '\\';
		case 'n': return '\n';
		case 't': return '\t';
		default:
			throw std::runtime_error("Unknown escape sequence at line " + std::to_string(line) + ", column " + std::to_string(column));
		}
	}

	char Lexer::peek() const
	{
		return isAtEnd() ? '\0' : source[current];
	}

	char Lexer::peekNext() const
	{
		if (current + 1 < source.length())
		{
			return source[current + 1];
		}
		return '\0';
	}

	bool Lexer::isAtEnd() const
	{
		return current >= source.length();
	}

	void Lexer::skipWhitespace()
	{
		while (!isAtEnd() && std::isspace(peek()))
		{
			if (peek() == '\n')
			{
				line++;
				column = 0;
			}
			if (peek() == '\t')
			{
				column += 3;
			}
			advance();
		}
	}

	void Lexer::skipComment() {
		if (peek() == '/' && peekNext() == '/') {
			// Single-line comment
			advance(); // Skip the first '/'
			advance(); // Skip the second '/'
			while (!isAtEnd() && peek() != '\n') {
				advance(); // Skip until the end of the line
			}

			if (peek() == '\n')
			{
				line++;
				column = 0;
			}
			advance();
		}
		else if (peek() == '/' && peekNext() == '*') {
			// Multi-line comment
			advance(); // Skip the first '/'
			advance(); // Skip the '*'
			while (!isAtEnd()) {
				if (peek() == '*' && peekNext() == '/') {
					advance(); // Skip the '*'
					advance(); // Skip the '/'
					break;
				}

				if (peek() == '\n')
				{
					line++;
					column = 0;
				}

				advance(); // Skip all other characters
			}
			if (isAtEnd()) {
				throw std::runtime_error("Unterminated multi-line comment");
			}
		}
	}

	Token Lexer::getNextToken() {
		skipWhitespace();

		if (isAtEnd()) {
			return Token(TokenType::EndOfFile, "", line, column);
		}

		char c = peek();

		if (c == '/' && (peekNext() == '/' || peekNext() == '*'))
		{
			skipComment();
			return getNextToken();
		}

		// Handle identifiers and keywords
		if (std::isalpha(c) || c == '_') {
			return identifierOrKeyword();
		}

		// Handle numeric literals
		if (std::isdigit(c)) {
			return number();
		}

		// Handle string literals
		if (c == '"' || c == '$') {
			return string();
		}

		// Handle character literals
		if (c == '\'') {
			return charLiteral();
		}

		// Handle single-character tokens and multi-character operators
		switch (c) {
		case '+':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::PlusAssign, "+=", line, column); }
			if (peek() == '+') { advance(); return Token(TokenType::Increment, "++", line, column); }
			return Token(TokenType::Plus, "+", line, column);
		case '-':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::MinusAssign, "-=", line, column); }
			if (peek() == '-') { advance(); return Token(TokenType::Decrement, "--", line, column); }
			return Token(TokenType::Minus, "-", line, column);
		case '*':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::MultiplyAssign, "*=", line, column); }
			return Token(TokenType::Multiply, "*", line, column);
		case '/':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::DivideAssign, "/=", line, column); }
			return Token(TokenType::Divide, "/", line, column);
		case '%':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::ModuloAssign, "%=", line, column); }
			return Token(TokenType::Modulo, "%", line, column);
		case '=':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::Equals, "==", line, column); }
			return Token(TokenType::Assign, "=", line, column);
		case '!':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::NotEquals, "!=", line, column); }
			return Token(TokenType::LogicalNot, "!", line, column);
		case '<':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::LessThanOrEqual, "<=", line, column); }
			if (peek() == '<')
			{ 
				advance();
				if (peek() == '=') { advance(); return Token(TokenType::LeftShiftAssign, "<<=", line, column); }
				return Token(TokenType::LeftShift, "<<", line, column);
			}
			return Token(TokenType::LessThan, "<", line, column);
		case '>':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::GreaterThanOrEqual, ">=", line, column); }
			if (peek() == '>')
			{ 
				advance();
				if (peek() == '=') { advance(); return Token(TokenType::RightShiftAssign, ">>=", line, column); }
				return Token(TokenType::RightShift, ">>", line, column);
			}
			return Token(TokenType::GreaterThan, ">", line, column);
		case '&':
			advance();
			if (peek() == '&') { advance(); return Token(TokenType::LogicalAnd, "&&", line, column); }
			if (peek() == '=') { advance(); return Token(TokenType::AndAssign, "&=", line, column); }
			return Token(TokenType::BitwiseAnd, "x", line, column);
		case '|':
			advance();
			if (peek() == '|') { advance(); return Token(TokenType::LogicalOr, "||", line, column); }
			if (peek() == '=') { advance(); return Token(TokenType::OrAssign, "|=", line, column); }
			return Token(TokenType::BitwiseOr, "|", line, column);
		case '^':
			advance();
			if (peek() == '=') { advance(); return Token(TokenType::XorAssign, "^=", line, column); }
			return Token(TokenType::BitwiseXor, "^", line, column);
		case '~':
			advance();
			return Token(TokenType::BitwiseNot, "~", line, column);
		case '?':
			advance();
			if (peek() == '?') { advance(); return Token(TokenType::NullCoalescing, "??", line, column); }
			return Token(TokenType::TernaryConditional, "?", line, column);

			// Delimiters and grouping symbols
		case '(':
			advance();
			return Token(TokenType::LeftParen, "(", line, column);
		case ')':
			advance();
			return Token(TokenType::RightParen, ")", line, column);
		case '{':
			advance();
			return Token(TokenType::LeftBrace, "{", line, column);
		case '}':
			advance();
			return Token(TokenType::RightBrace, "}", line, column);
		case '[':
			advance();
			return Token(TokenType::LeftBracket, "[", line, column);
		case ']':
			advance();
			return Token(TokenType::RightBracket, "]", line, column);
		case ';':
			advance();
			return Token(TokenType::Semicolon, ";", line, column);
		case ':':
			advance();
			return Token(TokenType::Colon, ":", line, column);
		case ',':
			advance();
			return Token(TokenType::Comma, ",", line, column);
		case '.':
			advance();
			return Token(TokenType::Dot, ".", line, column);
		case '\'':
			advance();
			return Token(TokenType::SingleQuote, "'", line, column);

		default:
			// Skip unrecognized characters and continue
			advance();
			throw std::runtime_error("Unrecognized token");
		}
	}

	std::vector<Token> Lexer::tokenize()
	{
		std::vector<Token> tokens;
		while (true)
		{
			Token token = getNextToken();
			tokens.push_back(token);
			if (token.type == TokenType::EndOfFile) break;
		}

		return tokens;
	}


	Token Lexer::identifierOrKeyword() {
		std::string value;
		int startColumn = column;

		while (std::isalnum(peek()) || peek() == '_' || peek() == '[' || peek() == ']') {
			value += advance();
		}

		if (value == "import") return Token(TokenType::Import, value, line, startColumn);
		if (value == "this") return Token(TokenType::This, value, line, startColumn);

		// Match control flow keywords
		if (value == "public") return Token(TokenType::Public, value, line, startColumn);
		if (value == "private") return Token(TokenType::Private, value, line, startColumn);
		if (value == "protected") return Token(TokenType::Protected, value, line, startColumn);

		// Match class and object keywords
		if (value == "class") return Token(TokenType::Class, value, line, startColumn);
		if (value == "interface") return Token(TokenType::Interface, value, line, startColumn);
		if (value == "enum") return Token(TokenType::Enum, value, line, startColumn);
		if (value == "static") return Token(TokenType::Static, value, line, startColumn);
		if (value == "new") return Token(TokenType::New, value, line, startColumn);
		if (value == "unsigned") return Token(TokenType::Unsigned, value, line, startColumn);

		// Match function and method keywords
		if (value == "function") return Token(TokenType::Function, value, line, startColumn);
		if (value == "void") return Token(TokenType::Void, value, line, startColumn);
		if (value == "return") return Token(TokenType::Return, value, line, startColumn);
		if (value == "overload") return Token(TokenType::Overload, value, line, startColumn);

		// Match control flow keywords
		if (value == "if") return Token(TokenType::If, value, line, startColumn);
		if (value == "else") return Token(TokenType::Else, value, line, startColumn);
		if (value == "elseif") return Token(TokenType::ElseIf, value, line, startColumn);
		if (value == "while") return Token(TokenType::While, value, line, startColumn);
		if (value == "for") return Token(TokenType::For, value, line, startColumn);
		if (value == "foreach") return Token(TokenType::Foreach, value, line, startColumn);
		if (value == "try") return Token(TokenType::Try, value, line, startColumn);
		if (value == "catch") return Token(TokenType::Catch, value, line, startColumn);
		if (value == "finally") return Token(TokenType::Finally, value, line, startColumn);
		if (value == "throw") return Token(TokenType::Throw, value, line, startColumn);
		if (value == "match") return Token(TokenType::Match, value, line, startColumn);
		if (value == "case") return Token(TokenType::Case, value, line, startColumn);
		if (value == "default") return Token(TokenType::Default, value, line, startColumn);
		if (value == "when") return Token(TokenType::When, value, line, startColumn);
		if (value == "break") return Token(TokenType::Break, value, line, startColumn);
		if (value == "continue") return Token(TokenType::Continue, value, line, startColumn);

		// Match primitive types
		if (value == "sbyte") return Token(TokenType::TypeSByte, value, line, startColumn);
		if (value == "byte") return Token(TokenType::TypeByte, value, line, startColumn);
		if (value == "short") return Token(TokenType::TypeShort, value, line, startColumn);
		if (value == "ushort") return Token(TokenType::TypeUShort, value, line, startColumn);
		if (value == "integer") return Token(TokenType::TypeInt, value, line, startColumn);
		if (value == "uint") return Token(TokenType::TypeUInt, value, line, startColumn);
		if (value == "long") return Token(TokenType::TypeLong, value, line, startColumn);
		if (value == "ulong") return Token(TokenType::TypeULong, value, line, startColumn);
		if (value == "float") return Token(TokenType::TypeFloat, value, line, startColumn);
		if (value == "double") return Token(TokenType::TypeDouble, value, line, startColumn);
		if (value == "decimal") return Token(TokenType::TypeDecimal, value, line, startColumn);
		if (value == "char") return Token(TokenType::TypeChar, value, line, startColumn);
		if (value == "string") return Token(TokenType::TypeString, value, line, startColumn);
		if (value == "bool") return Token(TokenType::TypeBool, value, line, startColumn);

		// Match primitive collections
		if (value == "list") return Token(TokenType::TypeList, value, line, startColumn);
		if (value == "dictionary") return Token(TokenType::TypeDictionary, value, line, startColumn);

		// Match array types
		if (value == "sbyte[]") return Token(TokenType::TypeSByteArray, value, line, startColumn);
		if (value == "byte[]") return Token(TokenType::TypeByteArray, value, line, startColumn);
		if (value == "short[]") return Token(TokenType::TypeShortArray, value, line, startColumn);
		if (value == "ushort[]") return Token(TokenType::TypeUShortArray, value, line, startColumn);
		if (value == "integer[]") return Token(TokenType::TypeIntArray, value, line, startColumn);
		if (value == "uinteger[]") return Token(TokenType::TypeUIntArray, value, line, startColumn);
		if (value == "long[]") return Token(TokenType::TypeLongArray, value, line, startColumn);
		if (value == "ulong[]") return Token(TokenType::TypeULongArray, value, line, startColumn);
		if (value == "float[]") return Token(TokenType::TypeFloatArray, value, line, startColumn);
		if (value == "double[]") return Token(TokenType::TypeDoubleArray, value, line, startColumn);
		if (value == "decimal[]") return Token(TokenType::TypeDecimalArray, value, line, startColumn);
		if (value == "char[]") return Token(TokenType::TypeCharArray, value, line, startColumn);
		if (value == "string[]") return Token(TokenType::TypeStringArray, value, line, startColumn);
		if (value == "bool[]") return Token(TokenType::TypeBoolArray, value, line, startColumn);

		// Match literals
		if (value == "null") return Token(TokenType::NullLiteral, value, line, startColumn);

		// Match identifiers and other types
		return Token(TokenType::Identifier, value, line, startColumn);
	}


	Token Lexer::number() {
		std::string value;
		int startColumn = column;
		bool isFloat = false;

		// Read the initial digits (for integer or float start)
		while (std::isdigit(peek())) {
			value += advance();
		}

		// Check for a decimal point and ensure it's valid
		if (peek() == '.') {
			value += advance(); // Add the decimal point to the value
			isFloat = true;

			// Ensure there is at least one digit after the decimal point
			if (!std::isdigit(peek())) {
				throw std::runtime_error("Invalid float literal: decimal point must be followed by digits");
			}

			// Continue reading digits after the decimal point
			while (std::isdigit(peek())) {
				value += advance();
			}
		}

		// Return as float if we found a decimal point, else as an integer
		if (isFloat) {
			return Token(TokenType::FloatLiteral, value, line, startColumn);
		}
		else {
			return Token(TokenType::IntegerLiteral, value, line, startColumn);
		}
	}



	Token Lexer::string()
	{
		std::string value;
		int startColumn = column + 1;
		bool isInterpolated = false;

		if (peek() == '$')
		{
			isInterpolated = true;
			advance();

			if (peek() != '"') throw std::runtime_error("Invalid interpolated string format.");
		}

		advance();

		while (!isAtEnd() && peek() != '"')
		{
			if (peek() == '{' && isInterpolated)
			{
				advance();
				value += "{";

				while (!isAtEnd() && peek() != '}') value += advance();

				if (isAtEnd()) throw std::runtime_error("Unterminated expression in interpolated string.");

				value += "}";
				advance();
			}
			else if (peek() == '\\')
			{
				advance();
				value += parseEscapeSequence();
			}
			else value += advance();
		}

		if (isAtEnd()) throw std::runtime_error("Unterminated string literal");

		advance();
		return Token(TokenType::StringLiteral, value, line, column);
	}

	Token Lexer::charLiteral()
	{
		std::string value;
		int startColumn = column;

		if (peek() != '\'')
			throw std::runtime_error("Expected character literal to start with a single quote at line " + std::to_string(line) + ", column " + std::to_string(startColumn));

		advance();

		if (peek() == '\\')
		{
			advance();
			char c = parseEscapeSequence();
			value += c;
		}
		else
		{
			value += advance();
		}

		if (peek() != '\'')
			throw std::runtime_error("Unterminated character literal at line " + std::to_string(line) + ", column " + std::to_string(column));

		advance();

		return Token(TokenType::CharLiteral, value, line, startColumn);
	}



	Token Lexer::singleCharToken(TokenType type)
	{
		int startColumn = column + 1;
		advance();
		return Token(type, std::string(1, source[current - 1]), line, startColumn);
	}
}