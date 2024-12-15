#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ArrayInstantiationNode : public Node
	{
	public:
		std::string type;
		std::shared_ptr<Node> size;

		ArrayInstantiationNode(const std::string& type, std::shared_ptr<Node> size)
			: type(type), size(size) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ArrayInstantiationNode: " << type << "[]" << std::endl;
			if (size) size->printAst(depth + 1);
		}
	};
}