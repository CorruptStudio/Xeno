#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ConstructorDeclarationNode : public Node
	{
	public:
		std::string name;
		std::vector<std::string> parameters;
		std::vector<std::shared_ptr<Node>> body;

		ConstructorDeclarationNode(const std::string& name, const std::vector<std::string>& parameters, const std::vector<std::shared_ptr<Node>>& body)
			: name(name), parameters(parameters), body(body) {}

		void printAst(int depth) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ConstructorDeclaration: " << name << std::endl;
			for (const auto& param : parameters) {
				std::cout << indent << "  Parameter: " << param << std::endl;
			}
			for (const auto& member : body)
			{
				member->printAst(depth + 1);
			}
		}
	};
}