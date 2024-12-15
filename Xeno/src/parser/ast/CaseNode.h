#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class CaseNode : public Node
	{
	public:
		std::shared_ptr<Node> caseValue;
		std::vector<std::shared_ptr<Node>> body;

		CaseNode(std::shared_ptr<Node> caseValue, std::vector<std::shared_ptr<Node>> body)
			: caseValue(caseValue), body(body) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "CaseNode" << std::endl;
			caseValue->printAst(depth + 1);

			for (const auto& member : body)
			{
				member->printAst(depth + 1);
			}
		}
	};
}