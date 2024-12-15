#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class TernaryExpresssionNode : public Node
	{
	public:
		std::shared_ptr<Node> condition;
		std::shared_ptr<Node> trueBranch;
		std::shared_ptr<Node> falseBranch;

		TernaryExpresssionNode(std::shared_ptr<Node> condition, std::shared_ptr<Node> trueBranch, std::shared_ptr<Node> falseBranch)
			: condition(condition), trueBranch(trueBranch), falseBranch(falseBranch) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "TernaryExpresssionNode" << std::endl;
			if (condition) condition->printAst(depth + 1);
			if (trueBranch) trueBranch->printAst(depth + 1);
			if (falseBranch) falseBranch->printAst(depth + 1);
		}
	};
}