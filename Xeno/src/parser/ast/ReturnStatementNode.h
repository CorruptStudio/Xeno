#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ReturnStatementNode : public Node
	{
	public:
		std::shared_ptr<Node> value;

		ReturnStatementNode(std::shared_ptr<Node> value)
			:value(value) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ReturnStatementNode: " << std::endl;
			if (value) value->printAst(depth + 1);
		}
	};
}