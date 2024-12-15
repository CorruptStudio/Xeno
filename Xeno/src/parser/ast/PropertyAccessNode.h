#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class PropertyAccessNode : public Node
	{
	public:
		std::shared_ptr<Node> identifier;
		std::string property;

		PropertyAccessNode(std::shared_ptr<Node> identifier, std::string property)
			: identifier(identifier), property(property) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "PropertyAccessNode" << std::endl;
			if (identifier) identifier->printAst(depth + 1);
		}
	};
}