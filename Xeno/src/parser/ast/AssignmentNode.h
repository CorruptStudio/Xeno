#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class AssignmentNode : public Node
	{
	public:
		std::string member;
		std::shared_ptr<Node> value;

		AssignmentNode(const std::string& member, std::shared_ptr<Node> value)
			: member(member), value(value) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "AssignmentNode: " << std::endl;

			if (value) {
				std::cout << " = " << std::endl;
				value->printAst(depth + 1);
			}
		}
	};
}