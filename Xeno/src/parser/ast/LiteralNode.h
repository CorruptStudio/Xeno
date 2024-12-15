#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class LiteralNode : public Node
	{
	public:
		std::string value;
		std::string type;

		explicit LiteralNode(const std::string& value, const std::string& type) : value(value), type(type) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "Literal " << type << ", value " << value << std::endl;
		}
	};
}