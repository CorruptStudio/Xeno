#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class FunctionCallNode : public Node
	{
	public:
		std::shared_ptr<Node> identifier;
		std::vector<std::shared_ptr<Node>> args;

		FunctionCallNode(std::shared_ptr<Node> identifier, std::vector<std::shared_ptr<Node>> args)
			: identifier(identifier), args(args) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "FunctionCallNode" << std::endl;
			if (identifier) identifier->printAst(depth + 1);

			for (const auto& arg : args)
			{
				arg->printAst(depth + 1);
			}
		}
	};
}