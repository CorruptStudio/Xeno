#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class BlockNode : public Node
	{
	public:
		std::vector<std::shared_ptr<Node>> statements;

		explicit BlockNode(const std::vector<std::shared_ptr<Node>>& statements)
			: statements(statements) { }

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "Block" << std::endl;

			for (const auto& statement : statements)
			{
				statement->printAst(depth + 1);
			}
		}
	};
}