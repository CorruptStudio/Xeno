#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class IdentifierNode : public Node
	{
	public:
		std::string name;

		explicit IdentifierNode(const std::string& value) : name(value) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "Identifier: " << name << std::endl;
		}
	};
}