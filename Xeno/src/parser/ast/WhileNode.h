#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class WhileStatementNode : public Node
	{
	public:
		std::shared_ptr<Node> condition;
		std::vector<std::shared_ptr<Node>> body;

		WhileStatementNode(std::shared_ptr<Node> condition, std::vector<std::shared_ptr<Node>> body)
			: condition(condition), body(body) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "WhileStatementNode" << std::endl;

			if (condition) condition->printAst(depth + 1);

			for (const auto& member : body)
			{
				member->printAst(depth + 1);
			}
		}
	};
}