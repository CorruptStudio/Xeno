#include "Parser.h"
#include <iostream>
#include <stdexcept>

namespace xeno::parser
{
#pragma region Utilities
	Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

	const std::vector<TokenType> Parser::returnTypes = {
		TokenType::TypeSByte, TokenType::TypeByte,
			TokenType::TypeShort, TokenType::TypeUShort,
			TokenType::TypeInt, TokenType::TypeUInt,
			TokenType::TypeLong, TokenType::TypeULong,
			TokenType::TypeFloat, TokenType::TypeDouble, TokenType::TypeDecimal,
			TokenType::TypeChar, TokenType::TypeString, TokenType::TypeBool,
			TokenType::TypeList, TokenType::TypeDictionary,
			TokenType::TypeSByteArray, TokenType::TypeByteArray,
			TokenType::TypeShortArray, TokenType::TypeUShortArray,
			TokenType::TypeIntArray, TokenType::TypeUIntArray,
			TokenType::TypeLongArray, TokenType::TypeULongArray,
			TokenType::TypeFloatArray, TokenType::TypeDoubleArray,
			TokenType::TypeDecimalArray, TokenType::TypeCharArray,
			TokenType::TypeStringArray, TokenType::TypeBoolArray,
			TokenType::Identifier, TokenType::Void
	};

	const std::vector<TokenType> Parser::types = {
		TokenType::TypeSByte, TokenType::TypeByte,
		TokenType::TypeShort, TokenType::TypeUShort,
		TokenType::TypeInt, TokenType::TypeUInt,
		TokenType::TypeLong, TokenType::TypeULong,
		TokenType::TypeFloat, TokenType::TypeDouble, TokenType::TypeDecimal,
		TokenType::TypeChar, TokenType::TypeString, TokenType::TypeBool,
		TokenType::TypeList, TokenType::TypeDictionary,
		TokenType::TypeSByteArray, TokenType::TypeByteArray,
		TokenType::TypeShortArray, TokenType::TypeUShortArray,
		TokenType::TypeIntArray, TokenType::TypeUIntArray,
		TokenType::TypeLongArray, TokenType::TypeULongArray,
		TokenType::TypeFloatArray, TokenType::TypeDoubleArray,
		TokenType::TypeDecimalArray, TokenType::TypeCharArray,
		TokenType::TypeStringArray, TokenType::TypeBoolArray,
		TokenType::Identifier
	};

	const std::vector<TokenType> Parser::classes = {
		TokenType::Class, TokenType::Interface, TokenType::Enum
	};

	std::shared_ptr<Node> Parser::parse()
	{
		auto program = std::make_shared<ProgramNode>();

		while (!isAtEnd()) {
			if (match(TokenType::Import)) {
				program->imports.push_back(parseImportDeclaration());
			}
			else if (peek().type == TokenType::Class || peek().type == TokenType::Interface || peek().type == TokenType::Enum) {
				program->classDeclarations.push_back(parseClassDeclaration());
			}
			else {
				throw std::runtime_error("Expected 'class', 'interface', or 'enum' at line " +
					std::to_string(peek().line) + ", column " +
					std::to_string(peek().column) + ". Found: " + peek().value);
			}
		}

		return program;
	}

	bool Parser::isAtEnd() const
	{
		return current >= tokens.size() || peek().type == TokenType::EndOfFile;
	}

	const Token& Parser::peek() const
	{
		return tokens[current];
	}

	const Token& Parser::peekNext() const
	{
		return tokens[current + 1];
	}

	const Token& Parser::advance()
	{
		if (!isAtEnd()) current++;
		return previous();
	}

	const Token& Parser::previous() const
	{
		return tokens[current - 1];
	}

	bool Parser::match(TokenType type)
	{
		if (isAtEnd() || peek().type != type) return false;
		advance();
		return true;
	}

	bool Parser::isTypeToken(TokenType type) const
	{
		return type == TokenType::TypeSByte || type == TokenType::TypeByte ||
			type == TokenType::TypeShort || type == TokenType::TypeUShort ||
			type == TokenType::TypeInt || type == TokenType::TypeUInt ||
			type == TokenType::TypeLong || type == TokenType::TypeULong ||
			type == TokenType::TypeFloat || type == TokenType::TypeDouble ||
			type == TokenType::TypeDecimal || type == TokenType::TypeChar ||
			type == TokenType::TypeString || type == TokenType::TypeBool ||
			type == TokenType::TypeList || type == TokenType::TypeDictionary ||
			type == TokenType::TypeSByteArray || type == TokenType::TypeByteArray ||
			type == TokenType::TypeShortArray || type == TokenType::TypeUShortArray ||
			type == TokenType::TypeIntArray || type == TokenType::TypeUIntArray ||
			type == TokenType::TypeLongArray || type == TokenType::TypeULongArray ||
			type == TokenType::TypeFloatArray || type == TokenType::TypeDoubleArray ||
			type == TokenType::TypeDecimalArray || type == TokenType::TypeCharArray ||
			type == TokenType::TypeStringArray || type == TokenType::TypeBoolArray ||
			type == TokenType::Identifier; // Include user-defined types
	}

	const Token& Parser::consume(TokenType type, const std::string& message)
	{
		if (match(type)) return previous();
		throw std::runtime_error(message + " at line " + std::to_string(peek().line) + ", column " + std::to_string(peek().column) + ". Found: " + peek().value);
	}

	const Token& Parser::consumeAny(const std::vector<TokenType>& types, const std::string& errorMessage) {
		for (const auto& type : types) {
			if (match(type)) return previous();
		}
		throw std::runtime_error(errorMessage + " at line " + std::to_string(peek().line) + ", column " + std::to_string(peek().column) + ". Found: " + peek().value);
	}
#pragma endregion

#pragma region Program and Class Parsing
	std::shared_ptr<ImportDeclarationNode> Parser::parseImportDeclaration()
	{
		Token moduleName;
		bool isGlobal;
		if (match(TokenType::LessThan)) {
			moduleName = consume(TokenType::Identifier, "Expected module name inside '<>'");
			consume(TokenType::GreaterThan, "Expected '>' to close import");
			isGlobal = true;
		}
		else if (match(TokenType::StringLiteral)) {
			moduleName = previous();
			isGlobal = false;
		}
		else {
			throw std::runtime_error("Expected module name in import statement");
		}

		return std::make_shared<ImportDeclarationNode>(moduleName.value, isGlobal);
	}

	std::shared_ptr<ClassDeclarationNode> Parser::parseClassDeclaration()
	{
		Token classType = consumeAny(classes, "Expected 'class', 'interface', or 'enum'");
		Token className = consume(TokenType::Identifier, "Expected class name");

		std::string baseClassName;
		if (match(TokenType::Colon))
		{
			baseClassName = consume(TokenType::Identifier, "Expected base class or interface name after ':'").value;
		}

		std::vector<std::shared_ptr<Node>> members;
		consume(TokenType::LeftBrace, "Expected '{' after class name");
		currentClassName = className.value;

		switch (classType.type)
		{
			case TokenType::Class:
			case TokenType::Interface:
				while (!match(TokenType::RightBrace) && !isAtEnd()) {
					members.push_back(parseAccessDeclaration());
				}
				break;

			case TokenType::Enum:
			{
				int currentValue = 0;

				do
				{
					Token identifier = consume(TokenType::Identifier, "Expected enum member name");
					if (match(TokenType::Equals))
					{
						Token valueToken = consume(TokenType::IntegerLiteral, "Expected integer value for enum member");
						currentValue = static_cast<size_t>(std::stoi(valueToken.value));
					}

					auto member = std::make_shared<EnumMemberNode>(identifier.value, currentValue++);
					members.push_back(member);
				} while (match(TokenType::Comma));

				consume(TokenType::RightBrace, "Expected '}' after enum members");
				break;
			}

			default:
				throw std::runtime_error("Unexpected declaration type");
		}

		return std::make_shared<ClassDeclarationNode>(classType.value, className.value, members);
	}

	std::shared_ptr<AccessDeclarationNode> Parser::parseAccessDeclaration()
	{
		Token accessModifier = consumeAny({ TokenType::Public, TokenType::Private, TokenType::Protected }, "Expected access modifier");
		consume(TokenType::Colon, "Expected ':' after access modifier");

		auto accessNode = std::make_shared<AccessDeclarationNode>(accessModifier.value);

		while (peek().type != TokenType::Public && peek().type != TokenType::Private &&
			peek().type != TokenType::Protected && peek().type != TokenType::RightBrace) {
			if (match(TokenType::Function) || ((peek().type == TokenType::Static || peek().type == TokenType::Overload) && peekNext().type == TokenType::Function)) {
				accessNode->members.push_back(parseFunctionDeclaration());
			}
			else if (match(TokenType::Identifier) && previous().value == currentClassName) {
				accessNode->members.push_back(parseConstructorDeclaration());
			}
			else if (isTypeToken(peek().type) || peek().type == TokenType::Static) {
				accessNode->members.push_back(parseVariableDeclaration());
			}
			else {
				throw std::runtime_error("Unexpected token in access declaration at line " + std::to_string(peek().line) + ", column " + std::to_string(peek().column) + ". Found: " + peek().value);
			}
		}

		return accessNode;
	}
#pragma endregion

#pragma region Access Body Parsing
	std::shared_ptr<FunctionDeclarationNode> Parser::parseFunctionDeclaration()
	{
		bool isStatic = false;
		bool isOverloaded = false;

		if (match(TokenType::Static))
		{
			consume(TokenType::Function, "Expected function after 'static'");
			isStatic = true;
		}

		if (match(TokenType::Overload))
		{
			consume(TokenType::Function, "Expected function after 'overload'");
		}

		Token functionName = consume(TokenType::Identifier, "Expected function name");
		std::vector<std::string> parameters;
		consume(TokenType::LeftParen, "Expected '(' after function name");

		if (!match(TokenType::RightParen)) {
			do {
				Token paramType = consumeAny(types, "Expected parameter type");
				Token paramName = consume(TokenType::Identifier, "Expected parameter name");
				parameters.push_back(paramName.value);
			} while (match(TokenType::Comma));

			consume(TokenType::RightParen, "Expected ')' after parameters");
		}

		consume(TokenType::Colon, "Expected ':' before return type");
		Token returnType = consumeAny(returnTypes, "Expected return type");

		std::vector<std::shared_ptr<Node>> body;

		if (peek().type == TokenType::LeftBrace)
		{
			body = parseBlock();
		}
		else if (match(TokenType::Semicolon)) {}
		else throw std::runtime_error("Expected '{' or ';' after function declaration");

		return std::make_shared<FunctionDeclarationNode>(functionName.value, returnType.value, parameters, body, isStatic, isOverloaded);
	}

	std::shared_ptr<ConstructorDeclarationNode> Parser::parseConstructorDeclaration()
	{
		Token constructorName = previous();
		consume(TokenType::LeftParen, "Expected '(' after constructor name");

		std::vector<std::string> parameters;
		if (!match(TokenType::RightParen)) {
			do {
				Token paramType = consumeAny(types, "Expected parameter type");
				Token paramName = consume(TokenType::Identifier, "Expected parameter name");
				parameters.push_back(paramName.value);
			} while (match(TokenType::Comma));

			consume(TokenType::RightParen, "Expected ')' after parameters");
		}

		auto body = parseBlock();
		return std::make_shared<ConstructorDeclarationNode>(constructorName.value, parameters, body);
	}

	std::shared_ptr<VariableDeclarationNode> Parser::parseVariableDeclaration()
	{
		bool isStatic = match(TokenType::Static);
		bool isUnsigned = match(TokenType::Unsigned);

		std::shared_ptr<Node> typeNode;
		std::string type;
		if (match(TokenType::TypeList))
		{ 
			typeNode = parseListType();
			type = "list<" + std::static_pointer_cast<ListTypeNode>(typeNode)->element + ">";
		}
		else if (match(TokenType::TypeDictionary))
		{ 
			typeNode = parseDictionaryType();
			type = "dictionary<" + std::static_pointer_cast<DictionaryTypeNode>(typeNode)->keyType + ", " + std::static_pointer_cast<DictionaryTypeNode>(typeNode)->valueType + ">";
		}
		else 
		{ 
			Token baseType = consumeAny(Parser::types, "Expected variable type"); 
			type = baseType.value; 
		}

		Token name = consume(TokenType::Identifier, "Expected variable name");

		std::shared_ptr<Node> initializer = nullptr;
		if (match(TokenType::Assign)) {
			initializer = parseExpression();
		}

		consume(TokenType::Semicolon, "Expected ';' after variable declaration");

		return std::make_shared<VariableDeclarationNode>(type, name.value, initializer, isStatic, isUnsigned);
	}
#pragma endregion

#pragma region Composite Type Parsing
	std::shared_ptr<Node> Parser::parseListType()
	{
		consume(TokenType::LessThan, "Expected '<' after 'list'");
		Token elementType = consumeAny(types, "Expected type inside 'list<>'");
		consume(TokenType::GreaterThan, "Expected '>' after type in 'list<>'");
		return std::make_shared<ListTypeNode>(elementType.value);
	}

	std::shared_ptr<Node> Parser::parseDictionaryType()
	{
		consume(TokenType::LessThan, "Expected '<' after 'dictionary'");
		Token keyType = consumeAny(types, "Expected type inside 'dictionary<>'");
		consume(TokenType::Comma, "Expected ',' between key and value in 'dictionary<>'");
		Token valueType = consumeAny(types, "Expected type inside 'dictionary<>'");
		consume(TokenType::GreaterThan, "Expected '>' after types in 'dictionary<>'");
		return std::make_shared<DictionaryTypeNode>(keyType.value, valueType.value);
	}

	std::shared_ptr<Node> Parser::parseList()
	{
		consume(TokenType::LeftBracket, "Expected '[' to start a list");

		std::vector<std::shared_ptr<Node>> elements;
		if (!(peek().type == TokenType::RightBracket))
		{
			do
			{
				elements.push_back(parseExpression());
			} while (match(TokenType::Comma));
		}


		consume(TokenType::RightBracket, "Expected ']' after list elements");
		return std::make_shared<ListNode>(elements);
	}

	std::shared_ptr<Node> Parser::parseDictionary()
	{
		consume(TokenType::LeftBrace, "Expected '{' to start a dictionary");

		std::map<std::shared_ptr<Node>, std::shared_ptr<Node>> elements;
		if (!(peek().type == TokenType::RightBrace))
		{
			do {
				auto key = parseExpression();
				consume(TokenType::Colon, "Expectes ':' after dictionary key");
				auto value = parseExpression();
				elements[key] = value;
			} while (match(TokenType::Comma));
		}

		consume(TokenType::RightBrace, "Expected '}' after list elements");
		return std::make_shared<DictionaryNode>(elements);
	}
#pragma endregion

#pragma region Expression Parsing
	std::shared_ptr<Node> Parser::parseExpression()
	{
		return parseTernary();
	}

	std::shared_ptr<Node> Parser::parseAssignment()
	{
		auto expr = parseTernary();

		if (match(TokenType::Assign))
		{
			Token equals = previous();
			std::shared_ptr<Node> value = parseAssignment();

			if (auto var = std::dynamic_pointer_cast<IdentifierNode>(expr))
			{
				return std::make_shared<AssignmentNode>(var->name, value);
			}
			else if (auto dotOp = std::dynamic_pointer_cast<DotOperationNode>(expr))
			{
				return std::make_shared<DotOperationNode>(dotOp->object, dotOp->member, value);
			}

			throw std::runtime_error("Invalid assignment target");
		}

		return expr;
	}

	std::shared_ptr<Node> Parser::parseTernary()
	{
		auto condition = parseLogical();

		if (match(TokenType::TernaryConditional))
		{
			auto trueBranch = parseExpression();
			consume(TokenType::Colon, "Expected ':' in ternary expression");
			auto falseBranch = parseExpression();
			return std::make_shared<TernaryExpresssionNode>(condition, trueBranch, falseBranch);
		}

		return condition;
	}

	std::shared_ptr<Node> Parser::parseLogical()
	{
		auto node = parseEquality();

		while (match(TokenType::LogicalAnd) || match(TokenType::LogicalOr))
		{
			Token operatorToken = previous();
			auto right = parseEquality();
			node = std::make_shared<BinaryExpressionNode>(node, operatorToken.value, right);
		}

		return node;
	}

	std::shared_ptr<Node> Parser::parseEquality()
	{
		auto node = parseComparison();

		while (match(TokenType::Equals) || match(TokenType::NotEquals))
		{
			Token operatorToken = previous();
			auto right = parseComparison();
			node = std::make_shared<BinaryExpressionNode>(node, operatorToken.value, right);
		}

		return node;
	}

	std::shared_ptr<Node> Parser::parseComparison()
	{
		auto node = parseTerm();

		while (match(TokenType::LessThan) || match(TokenType::GreaterThan) || match(TokenType::LessThanOrEqual) || match(TokenType::GreaterThanOrEqual))
		{
			Token operatorToken = previous();
			auto right = parseTerm();
			node = std::make_shared<BinaryExpressionNode>(node, operatorToken.value, right);
		}

		return node;
	}

	std::shared_ptr<Node> Parser::parseTerm()
	{
		auto node = parseFactor();

		while (match(TokenType::Plus) || match(TokenType::Minus))
		{
			Token operatorToken = previous();
			auto right = parseFactor();
			node = std::make_shared<BinaryExpressionNode>(node, operatorToken.value, right);
		}

		return node;
	}

	std::shared_ptr<Node> Parser::parseFactor()
	{
		auto node = parseUnary();

		while (match(TokenType::Multiply) || match(TokenType::Divide))
		{
			Token operatorToken = previous();
			auto right = parseUnary();
			node = std::make_shared<BinaryExpressionNode>(node, operatorToken.value, right);
		}

		return node;
	}

	std::shared_ptr<Node> Parser::parseUnary()
	{
		if (match(TokenType::Minus) || match(TokenType::LogicalNot) || match(TokenType::BitwiseNot))
		{
			Token operatorToken = previous();
			auto operand = parseUnary();
			return std::make_shared<UnaryExpressionNode>(operatorToken.value, operand, true);
		}

		auto node = parsePrimary();

		if (match(TokenType::Increment) || match(TokenType::Decrement))
		{
			Token operatorToken = previous();
			return std::make_shared<UnaryExpressionNode>(operatorToken.value, node, false);
		}

		return node;
	}

	std::shared_ptr<Node> Parser::parsePrimary()
	{
		if (peek().type == TokenType::IntegerLiteral || peek().type == TokenType::FloatLiteral || peek().type == TokenType::StringLiteral || peek().type == TokenType::CharLiteral || peek().type == TokenType::BoolLiteral)
		{
			std::string value = previous().value;
			std::string type;

			switch (peek().type)
			{
			case TokenType::IntegerLiteral: type = "int"; break;
			case TokenType::FloatLiteral: type = "float"; break;
			case TokenType::StringLiteral: type = "string"; break;
			case TokenType::CharLiteral: type = "char"; break;
			case TokenType::BoolLiteral: type = "bool"; break;
			default: throw std::runtime_error("Unknown literal type");
			}

			match(peek().type);
			return std::make_shared<LiteralNode>(previous().value, type);
		}

		if (match(TokenType::This))
		{
			return parseDotOperation();
		}

		if (match(TokenType::New))
		{
			return parseNewExpression();
		}
		else if (match(TokenType::Identifier))
		{
			if (peek().type == TokenType::Dot)
			{
				return parseDotOperation();
			}

			auto node = std::make_shared<IdentifierNode>(previous().value);

			if (match(TokenType::LeftBracket))
			{
				auto index = parseExpression();
				consume(TokenType::RightBracket, "Expected ']' after index");
				return std::make_shared<ArrayAccessNode>(node, index);
			}

			return node;
		}

		if (match(TokenType::LeftParen))
		{
			auto node = parseExpression();
			consume(TokenType::RightParen, "Expected ')' after expression");
			return node;
		}

		if (peek().type == TokenType::LeftBracket)
		{
			return parseList();
		}

		if (peek().type == TokenType::LeftBrace)
		{
			return parseDictionary();
		}

		throw std::runtime_error("Unexpected token in expression at line " +
			std::to_string(peek().line) + ", column " +
			std::to_string(peek().column) + ". Found: " + peek().value);
	}

	std::shared_ptr<Node> Parser::parseDotOperation()
	{
		auto node = std::make_shared<IdentifierNode>(previous().value);
		consume(TokenType::Dot, "Expected '.' after 'this'");
		Token member = consume(TokenType::Identifier, "Expected identifier after '.'");

		if (match(TokenType::Assign))
		{
			auto value = parseExpression();
			return std::make_shared<DotOperationNode>(node, member.value, value);
		}

		if (match(TokenType::LeftParen))
		{
			std::vector<std::shared_ptr<Node>> arguments;

			if (!(peek().type == TokenType::RightParen))
			{
				do
				{
					arguments.push_back(parseExpression());
				} while (match(TokenType::Comma));
			}

			consume(TokenType::RightParen, "Expected ')' after arguments");
			auto functionCallNode = std::make_shared<FunctionCallNode>(std::make_shared<IdentifierNode>(member.value), arguments);
			return std::make_shared<DotOperationNode>(node, member.value, functionCallNode);
		}

		return std::make_shared<DotOperationNode>(node, member.value);
	}
#pragma endregion

#pragma region Control Flow Parsing
	std::shared_ptr<Node> Parser::parseIfStatement()
	{
		consume(TokenType::If, "Expected 'if'");
		consume(TokenType::LeftParen, "Expected '(' after 'if'");
		auto condition = parseExpression();
		consume(TokenType::RightParen, "Expected ')' after condition");

		auto thenBranch = parseBlock();
		std::shared_ptr<Node> elseBranch = nullptr;

		if (match(TokenType::Else))
		{
			if (peek().type == TokenType::If)
			{
				elseBranch = parseIfStatement();
			}
			else
			{
				elseBranch = parseStatement();
			}
		}

		return std::make_shared<IfStatementNode>(condition, thenBranch, elseBranch);
	}

	std::shared_ptr<Node> Parser::parseWhileStatement()
	{
		consume(TokenType::While, "Expected 'while'");
		consume(TokenType::LeftParen, "Expected '(' after 'while'");
		auto condition = parseExpression();
		consume(TokenType::RightParen, "Exprected ')' after condition");

		auto body = parseBlock();
		return std::make_shared<WhileStatementNode>(condition, body);
	}

	std::shared_ptr<Node> Parser::parseForStatement()
	{
		consume(TokenType::For, "Expected 'for'");
		consume(TokenType::LeftParen, "Expected '(' after 'for'");
		auto initializer = parseVariableDeclaration();

		auto condition = parseExpression();
		consume(TokenType::Semicolon, "Expected ';' after condition");

		auto increment = parseExpression();
		consume(TokenType::RightParen, "Expected ')' after increment");

		auto body = parseBlock();
		return std::make_shared<ForStatementNode>(initializer, condition, increment, body);
	}

	std::shared_ptr<Node> Parser::parseMatchStatement()
	{
		consume(TokenType::Match, "Expected 'match'");
		consume(TokenType::LeftParen, "Expected '(' after 'match'");
		auto expression = parseExpression();
		consume(TokenType::RightParen, "Expected ')' after match expression");
		consume(TokenType::LeftBrace, "Expected '{' after match expression");

		std::vector<std::shared_ptr<CaseNode>> cases;
		std::shared_ptr<Node> defaultCase = nullptr;

		while (!match(TokenType::RightBrace) && !isAtEnd())
		{
			if (match(TokenType::Case))
			{
				auto caseValue = parseExpression();
				consume(TokenType::Colon, "Expected ':' after case value");

				std::vector<std::shared_ptr<Node>> body;
				while (!(peek().type == TokenType::Case) && !(peek().type == TokenType::Default) && !(peek().type == TokenType::RightBrace) && !isAtEnd())
				{
					body.push_back(parseStatement());
				}
				cases.push_back(std::make_shared<CaseNode>(caseValue, body));
			}
			else if (match(TokenType::Default))
			{
				consume(TokenType::Colon, "Expected ':' after default");
				defaultCase = parseStatement();
			}
			else
			{
				throw std::runtime_error("Unexpected token in match statement");
			}
		}

		return std::make_shared<MatchStatementNode>(expression, cases, defaultCase);
	}

	std::shared_ptr<Node> Parser::parseBreakStatement()
	{
		Token breakToken = consume(TokenType::Break, "Expected 'break' keyword");
		consume(TokenType::Semicolon, "Expected ';' after 'break' keyword");
		return std::make_shared<BreakStatementNode>(breakToken.line, breakToken.column);
	}

	std::shared_ptr<Node> Parser::parseFunctionStatement()
	{
		consume(TokenType::Identifier, "Expected identifier");
		auto identifier = std::make_shared<IdentifierNode>(previous().value);
		std::vector<std::shared_ptr<Node>> args;
		consume(TokenType::LeftParen, "Expected '(' after identifier");

		if (!match(TokenType::RightParen))
		{
			do
			{
				args.push_back(parseExpression());
			} while (match(TokenType::Comma));
			consume(TokenType::RightParen, "Expected ')' after expression");
		}

		consume(TokenType::Semicolon, "Expected ';' after ')'");

		return std::make_shared<FunctionCallNode>(identifier, args);
	}

	std::shared_ptr<Node> Parser::parseReturnStatement()
	{
		consume(TokenType::Return, "Expected 'return'");
		
		std::shared_ptr<Node> value = nullptr;
		if (!(peek().type == TokenType::Semicolon))
		{
			value = parseExpression();
		}

		consume(TokenType::Semicolon, "Expected ';' after return value");
		return std::make_shared<ReturnStatementNode>(value);
	}
	
	std::shared_ptr<Node> Parser::parseForeachStatement()
	{
		consume(TokenType::Foreach, "Expected 'foreach' keyword");
		consume(TokenType::LeftParen, "Exprected '(' after 'foreach'");

		auto variableType = consumeAny(types, "Expected type for foreach variable");
		auto variableName = consume(TokenType::Identifier, "Expected identifier for foreach variable");

		consume(TokenType::Colon, "Expected ':' in foreach statement");
		auto collection = parseExpression();

		consume(TokenType::RightParen, "Expected ')' after foreach collection");

		auto body = parseStatement();

		return std::make_shared<ForeachStatementNode>(variableType.value, variableName.value, collection, body);
	}

	std::shared_ptr<Node> Parser::parseNewExpression()
	{
		Token type = consumeAny(types, "Expected type after 'new'");

		if (match(TokenType::LeftBracket))
		{
			auto size = parseExpression();
			consume(TokenType::RightBracket, "Expected ']' after array size");
			return std::make_shared<ArrayInstantiationNode>(type.value, size);
		}

		if (match(TokenType::LeftParen))
		{
			std::vector<std::shared_ptr<Node>> arguments;

			if (!(peek().type == TokenType::RightParen))
			{
				do
				{
					arguments.push_back(parseExpression());
				} while (match(TokenType::Comma));

				consume(TokenType::RightParen, "Expected ')' after arguments");
				return std::make_shared<ObjectInstantiationNode>(type.value, arguments);
			}

			throw std::runtime_error("Invalid 'new' expression at line " + std::to_string(type.line) + ", column " + std::to_string(type.column));
		}
	}
#pragma endregion

#pragma region Statement and Block Parsing
	std::shared_ptr<Node> Parser::parseStatement()
	{
		if (peek().type == TokenType::If)
		{
			return parseIfStatement();
		}

		if (peek().type == TokenType::While)
		{
			return parseWhileStatement();
		}

		if (peek().type == TokenType::For)
		{
			return parseForStatement();
		}

		if (peek().type == TokenType::Foreach)
		{
			return parseForeachStatement();
		}

		if (peek().type == TokenType::Match)
		{
			return parseMatchStatement();
		}

		if (peek().type == TokenType::Return)
		{
			return parseReturnStatement();
		}

		if (peek().type == TokenType::Break)
		{
			return parseBreakStatement();
		}

		if (peek().type == TokenType::LeftBrace)
		{
			return std::make_shared<BlockNode>(parseBlock());
		}

		if (peek().type == TokenType::Identifier && peekNext().type == TokenType::LeftParen)
		{
			return parseFunctionStatement();
		}

		if (isTypeToken(peek().type) && peekNext().type != TokenType::Dot)
		{
			return parseVariableDeclaration();
		}

		auto expr = parseExpression();
		consume(TokenType::Semicolon, "Expected ';' after expression");
		return expr;
	}

	std::vector<std::shared_ptr<Node>> Parser::parseBlock()
	{
		consume(TokenType::LeftBrace, "Expected '{' to start block");

		std::vector<std::shared_ptr<Node>> statements;
		while (!match(TokenType::RightBrace) && !isAtEnd()) {
			statements.push_back(parseStatement());
		}

		return statements;
	}
#pragma endregion
}
