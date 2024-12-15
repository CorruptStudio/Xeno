#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class UnaryExpressionNode : public Node
	{
	public:
		std::string op;
		std::shared_ptr<Node> operand;
		bool isPrefix;

		UnaryExpressionNode(const std::string& op, std::shared_ptr<Node> operand, bool isPrefix)
			: op(op), operand(operand), isPrefix(isPrefix) {}

		void printAst(int depth) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << (isPrefix ? "PrefixUnary" : "PostfixUnary") << op << std::endl;
			if (operand) operand->printAst(depth + 1);
		}
	};
}