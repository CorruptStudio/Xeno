#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ArrayAccessNode : public Node
	{
	public:
		std::shared_ptr<Node> identifier;
		std::shared_ptr<Node> index;

		ArrayAccessNode(std::shared_ptr<Node> identifier, std::shared_ptr<Node> index)
			: identifier(identifier), index(index) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ArrayAccessNode" << std::endl;

			if (identifier) identifier->printAst(depth + 1);
			if (index) index->printAst(depth + 1);
		}
	};
}