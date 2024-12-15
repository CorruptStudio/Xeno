#include "Token.h"

namespace xeno::lexer
{
	Token::Token(TokenType type, const std::string& value, int line, int column)
		: type(type), value(value), line(line), column(column) {}

	std::string Token::toString() const
	{
		std::stringstream ss;
		ss << "Token(type: " << tokenTypeToString(type)
			<< ", value: \"" << value << "\""
			<< ", line: " << line
			<< ", column: " << column << ")";
		return ss.str();
	}

	std::string Token::tokenTypeToString(TokenType token) const
	{
		switch (type) {
			// Access Modifiers
		case TokenType::Public: return "Public";
		case TokenType::Private: return "Private";
		case TokenType::Protected: return "Protected";

			// Class and Object
		case TokenType::Class: return "Class";
		case TokenType::Interface: return "Interface";
		case TokenType::Enum: return "Enum";
		case TokenType::Static: return "Static";
		case TokenType::New: return "New";

			// Functions and Methods
		case TokenType::Function: return "Function";
		case TokenType::Void: return "Void";
		case TokenType::Return: return "Return";
		case TokenType::Overload: return "Overload";

			// Control Flow
		case TokenType::If: return "If";
		case TokenType::Else: return "Else";
		case TokenType::ElseIf: return "ElseIf";
		case TokenType::While: return "While";
		case TokenType::For: return "For";
		case TokenType::Foreach: return "Foreach";
		case TokenType::Try: return "Try";
		case TokenType::Catch: return "Catch";
		case TokenType::Finally: return "Finally";
		case TokenType::Throw: return "Throw";
		case TokenType::Match: return "Match";
		case TokenType::Case: return "Case";
		case TokenType::Default: return "Default";
		case TokenType::When: return "When";
		case TokenType::Break: return "Break";
		case TokenType::Continue: return "Continue";

			// Primitive Types (Integers)
		case TokenType::TypeSByte: return "TypeSByte";
		case TokenType::TypeByte: return "TypeByte";
		case TokenType::TypeShort: return "TypeShort";
		case TokenType::TypeUShort: return "TypeUShort";
		case TokenType::TypeInt: return "TypeInt";
		case TokenType::TypeUInt: return "TypeUInt";
		case TokenType::TypeLong: return "TypeLong";
		case TokenType::TypeULong: return "TypeULong";

			// Primitive Types (Floating Point)
		case TokenType::TypeFloat: return "TypeFloat";
		case TokenType::TypeDouble: return "TypeDouble";
		case TokenType::TypeDecimal: return "TypeDecimal";

			// Primitive Types (Other)
		case TokenType::TypeChar: return "TypeChar";
		case TokenType::TypeString: return "TypeString";
		case TokenType::TypeBool: return "TypeBool";

			// Primitive Collections
		case TokenType::TypeList: return "TypeList";
		case TokenType::TypeDictionary: return "TypeDictionary";

			// Array Types
		case TokenType::TypeSByteArray: return "TypeSByteArray";
		case TokenType::TypeByteArray: return "TypeByteArray";
		case TokenType::TypeShortArray: return "TypeShortArray";
		case TokenType::TypeUShortArray: return "TypeUShortArray";
		case TokenType::TypeIntArray: return "TypeIntArray";
		case TokenType::TypeUIntArray: return "TypeUIntArray";
		case TokenType::TypeLongArray: return "TypeLongArray";
		case TokenType::TypeULongArray: return "TypeULongArray";
		case TokenType::TypeFloatArray: return "TypeFloatArray";
		case TokenType::TypeDoubleArray: return "TypeDoubleArray";
		case TokenType::TypeDecimalArray: return "TypeDecimalArray";
		case TokenType::TypeCharArray: return "TypeCharArray";
		case TokenType::TypeStringArray: return "TypeStringArray";
		case TokenType::TypeBoolArray: return "TypeBoolArray";

			// Literals
		case TokenType::IntegerLiteral: return "IntegerLiteral";
		case TokenType::FloatLiteral: return "FloatLiteral";
		case TokenType::StringLiteral: return "StringLiteral";
		case TokenType::CharLiteral: return "CharLiteral";
		case TokenType::BoolLiteral: return "BoolLiteral";
		case TokenType::NullLiteral: return "NullLiteral";

			// Operators
		case TokenType::Plus: return "Plus";
		case TokenType::Minus: return "Minus";
		case TokenType::Multiply: return "Multiply";
		case TokenType::Divide: return "Divide";
		case TokenType::Modulo: return "Modulo";
		case TokenType::Assign: return "Assign";
		case TokenType::PlusAssign: return "PlusAssign";
		case TokenType::MinusAssign: return "MinusAssign";
		case TokenType::MultiplyAssign: return "MultiplyAssign";
		case TokenType::DivideAssign: return "DivideAssign";
		case TokenType::Equals: return "Equals";
		case TokenType::NotEquals: return "NotEquals";
		case TokenType::LessThan: return "LessThan";
		case TokenType::GreaterThan: return "GreaterThan";
		case TokenType::LessThanOrEqual: return "LessThanOrEqual";
		case TokenType::GreaterThanOrEqual: return "GreaterThanOrEqual";
		case TokenType::LogicalAnd: return "LogicalAnd";
		case TokenType::LogicalOr: return "LogicalOr";
		case TokenType::LogicalNot: return "LogicalNot";
		case TokenType::Increment: return "Increment";
		case TokenType::Decrement: return "Decrement";

			// Symbols
		case TokenType::LeftParen: return "LeftParen";
		case TokenType::RightParen: return "RightParen";
		case TokenType::LeftBrace: return "LeftBrace";
		case TokenType::RightBrace: return "RightBrace";
		case TokenType::LeftBracket: return "LeftBracket";
		case TokenType::RightBracket: return "RightBracket";
		case TokenType::Semicolon: return "Semicolon";
		case TokenType::Colon: return "Colon";
		case TokenType::Comma: return "Comma";
		case TokenType::Dot: return "Dot";
		case TokenType::Arrow: return "Arrow";
		case TokenType::DollarSign: return "DollarSign";
		case TokenType::SingleQuote: return "SingleQuote";
		case TokenType::DoubleQuote: return "DoubleQuote";

			// Identifiers and Others
		case TokenType::Import: return "Import";
		case TokenType::Identifier: return "Identifier";
		case TokenType::EndOfFile: return "EndOfFile";

		default: return "Unknown";
		}
	}
}