#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class IfStatementNode : public Node {
	public:
		std::shared_ptr<Node> condition;
		std::vector<std::shared_ptr<Node>> thenBranch;
		std::shared_ptr<Node> elseBranch;

		IfStatementNode(std::shared_ptr<Node> condition, std::vector<std::shared_ptr<Node>> thenBranch, std::shared_ptr<Node> elseBranch = nullptr)
			: condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "IfStatementNode" << std::endl;
			if (condition) condition->printAst(depth + 1);

			for (const auto& member : thenBranch)
			{
				member->printAst(depth + 1);
			}

			if (elseBranch) elseBranch->printAst(depth + 1);
		}
	};
}