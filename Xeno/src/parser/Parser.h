#pragma once
#include "lexer/Token.h"
#include "ast/AstNodes.h"
#include <memory>
#include <vector>

using namespace xeno::lexer;
using namespace xeno::parser::ast;

namespace xeno::parser
{
	class Parser
	{
	public:
		// Constructor and Destructor
		Parser(const std::vector<Token>& tokens);

		// Entry Point
		std::shared_ptr<Node> parse();

	private:
		// Member Variables
		const std::vector<Token>& tokens;
		size_t current;
		std::string currentClassName;
		static const std::vector<TokenType> returnTypes;
		static const std::vector<TokenType> types;
		static const std::vector<TokenType> classes;

		// Utility Functions
		bool isAtEnd() const;
		const Token& peek() const;
		const Token& peekNext() const;
		const Token& advance();
		const Token& previous() const;
		bool match(TokenType type);
		bool isTypeToken(TokenType type) const;
		const Token& consume(TokenType type, const std::string& message);
		const Token& consumeAny(const std::vector<TokenType>& types, const std::string& errorMessage);

		// Import and Class Declarations
		std::shared_ptr<ImportDeclarationNode> parseImportDeclaration();
		std::shared_ptr<ClassDeclarationNode> parseClassDeclaration();
		std::shared_ptr<AccessDeclarationNode> parseAccessDeclaration();

		// Function and Variable Declarations
		std::shared_ptr<ConstructorDeclarationNode> parseConstructorDeclaration();
		std::shared_ptr<FunctionDeclarationNode> parseFunctionDeclaration();
		std::shared_ptr<VariableDeclarationNode> parseVariableDeclaration();

		// Composite Types Parsing
		std::shared_ptr<Node> parseListType();
		std::shared_ptr<Node> parseDictionaryType();
		std::shared_ptr<Node> parseList();
		std::shared_ptr<Node> parseDictionary();

		// Expression Parsing
		std::shared_ptr<Node> parseExpression();
		std::shared_ptr<Node> parseAssignment();
		std::shared_ptr<Node> parseTernary();
		std::shared_ptr<Node> parseLogical();
		std::shared_ptr<Node> parseEquality();
		std::shared_ptr<Node> parseComparison();
		std::shared_ptr<Node> parseTerm();
		std::shared_ptr<Node> parseFactor();
		std::shared_ptr<Node> parseUnary();
		std::shared_ptr<Node> parsePrimary();
		std::shared_ptr<Node> parseDotOperation();
		
		// Statement Parsing
		std::shared_ptr<Node> parseIfStatement();
		std::shared_ptr<Node> parseWhileStatement();
		std::shared_ptr<Node> parseForStatement();
		std::shared_ptr<Node> parseMatchStatement();
		std::shared_ptr<Node> parseBreakStatement();
		std::shared_ptr<Node> parseFunctionStatement();
		std::shared_ptr<Node> parseReturnStatement();
		std::shared_ptr<Node> parseForeachStatement();
		std::shared_ptr<Node> parseNewExpression();

		// Block and General Statements
		std::shared_ptr<Node> parseStatement();
		std::vector<std::shared_ptr<Node>> parseBlock();
	};
}