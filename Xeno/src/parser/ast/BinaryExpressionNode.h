#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class BinaryExpressionNode : public Node
	{
	public:
		std::shared_ptr<Node> left;
		std::string op;
		std::shared_ptr<Node> right;

		BinaryExpressionNode(std::shared_ptr<Node> left, const std::string& op, std::shared_ptr<Node> right)
			: left(left), op(op), right(right) {}

		void printAst(int depth) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "BinaryExpression: " << op << std::endl;
			if (left) left->printAst(depth + 1);
			if (right) right->printAst(depth + 1);
		}
	};
}