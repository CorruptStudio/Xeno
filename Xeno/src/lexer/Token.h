#pragma once
#include <string>
#include <sstream>

namespace xeno::lexer
{
	enum class TokenType {
		// Access Modifiers
		Public, Private, Protected,

		// Class and Object
		Class, Interface, Enum, Static, New, Unsigned,

		// Functions and Methods
		Function, Void, Return, Overload,

		// Control Flow
		If, Else, ElseIf, While, For, Foreach, Try, Catch, Finally, Throw,
		Match, Case, Default, When, Break, Continue,

		// Primitive Types (Integers)
		TypeSByte, TypeByte, TypeShort, TypeUShort, TypeInt, TypeUInt, TypeLong, TypeULong,

		// Primitive Types (Floating Point)
		TypeFloat, TypeDouble, TypeDecimal,

		// Primitive Types (Other)
		TypeChar, TypeString, TypeBool,

		// Primitive Collections
		TypeList, TypeDictionary,

		// Array Types (All possible types)
		TypeSByteArray, TypeByteArray, TypeShortArray, TypeUShortArray,
		TypeIntArray, TypeUIntArray, TypeLongArray, TypeULongArray,
		TypeFloatArray, TypeDoubleArray, TypeDecimalArray,
		TypeCharArray, TypeStringArray, TypeBoolArray,

		// Literals
		IntegerLiteral, FloatLiteral, StringLiteral, CharLiteral, BoolLiteral, NullLiteral,

		// Operators
		// Arithmetic
		Plus, Minus, Multiply, Divide, Modulo,

		// Assignment
		Assign, PlusAssign, MinusAssign, MultiplyAssign, DivideAssign,
		ModuloAssign, AndAssign, OrAssign, XorAssign, LeftShiftAssign, RightShiftAssign,

		// Comparison
		Equals, NotEquals, LessThan, GreaterThan, LessThanOrEqual, GreaterThanOrEqual,

		// Logical
		LogicalAnd, LogicalOr, LogicalNot,

		// Bitwise
		BitwiseNot, BitwiseAnd, BitwiseOr, BitwiseXor, LeftShift, RightShift,

		// Increment/Decrement
		Increment, Decrement,

		// Ternary and Null-Coalescing
		TernaryConditional, NullCoalescing,

		// Symbols
		LeftParen, RightParen, LeftBrace, RightBrace, LeftBracket, RightBracket,
		Semicolon, Colon, Comma, Dot, Arrow, DollarSign, SingleQuote, DoubleQuote,

		// Identifiers and others
		This, Import, Identifier, EndOfFile // Indicates the end of input
	};


	struct Token {
		TokenType type;
		std::string value;
		int line;
		int column;

		Token() = default;
		Token(TokenType type, const std::string& value, int line, int column);
		std::string toString() const;
		std::string tokenTypeToString(TokenType token) const;
	};
}