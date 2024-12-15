#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ForStatementNode : public Node
	{
	public:
		std::shared_ptr<Node> initializer;
		std::shared_ptr<Node> condition;
		std::shared_ptr<Node> increment;
		std::vector<std::shared_ptr<Node>> body;

		ForStatementNode(std::shared_ptr<Node> initializer, std::shared_ptr<Node> condition, std::shared_ptr<Node> increment, std::vector< std::shared_ptr<Node>> body)
			: initializer(initializer), condition(condition), increment(increment), body(body) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ForStatementNode" << std::endl;
			if (initializer) initializer->printAst(depth + 1);
			if (condition) condition->printAst(depth + 1);
			if (increment) increment->printAst(depth + 1);

			for (const auto& member : body)
			{
				member->printAst(depth + 1);
			}
		}
	};
}