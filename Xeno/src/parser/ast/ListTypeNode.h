#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ListTypeNode : public Node
	{
	public:
		std::string element;

		ListTypeNode(const std::string& element)
			: element(element) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ListTypeNode: " << element << std::endl;
		}
	};
}