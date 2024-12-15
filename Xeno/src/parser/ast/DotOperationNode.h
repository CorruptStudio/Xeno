#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class DotOperationNode : public Node
	{
	public:
		std::shared_ptr<Node> object;
		std::string member;
		std::shared_ptr<Node> value;

		DotOperationNode(std::shared_ptr<Node> object, const std::string& member, std::shared_ptr<Node> value = nullptr)
			: object(object), member(member), value(value) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "DotOperationNode: " << std::endl;
			if (object) object->printAst(depth + 1);
			std::cout << indent << "." << member << std::endl;
			
			if (value) {
				value->printAst(depth + 1);
			}
		}
	};
}