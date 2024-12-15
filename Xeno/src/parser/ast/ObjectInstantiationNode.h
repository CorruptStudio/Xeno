#pragma once
#include "Node.h"
#include <vector>

namespace xeno::parser::ast
{
	class ObjectInstantiationNode : public Node {
	public:
		std::string type;
		std::vector<std::shared_ptr<Node>> arguments;

		ObjectInstantiationNode(const std::string& type, const std::vector<std::shared_ptr<Node>>& arguments)
			: type(type), arguments(arguments) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ObjectInstantiation: " << type << std::endl;
			for (const auto& arg : arguments) {
				arg->printAst(depth + 1);
			}
		}
	};
}