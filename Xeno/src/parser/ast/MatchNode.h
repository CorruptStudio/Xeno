#pragma once
#include "Node.h"
#include "CaseNode.h"

namespace xeno::parser::ast
{
	class MatchStatementNode : public Node
	{
	public:
		std::shared_ptr<Node> expression;
		std::vector<std::shared_ptr<CaseNode>> cases;
		std::shared_ptr<Node> defaultCase;

		MatchStatementNode(std::shared_ptr<Node> expression, std::vector<std::shared_ptr<CaseNode>> cases, std::shared_ptr<Node> defaultCase)
			: expression(expression), cases(cases), defaultCase(defaultCase) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "MatchStatementNode" << std::endl;
			if (expression) expression->printAst(depth + 1);

			for (const auto& member : cases)
			{
				member->printAst(depth + 1);
			}

			if (defaultCase) defaultCase->printAst(depth + 1);
		}
	};
}