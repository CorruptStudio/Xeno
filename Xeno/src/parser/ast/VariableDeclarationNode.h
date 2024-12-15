#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class VariableDeclarationNode : public Node {
	public:
		std::string name;
		std::string type;
		std::shared_ptr<Node> initializer;
		bool isStatic;
		bool isUnsigned;

		VariableDeclarationNode(const std::string& name, const std::string& type, std::shared_ptr<Node> initializer, bool isStatic, bool isUnsigned)
			: name(name), type(type), initializer(initializer), isStatic(isStatic), isUnsigned(isUnsigned) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "VariableDeclaration: " << name << " Type: " << type << std::endl;

			if (initializer) initializer->printAst(depth + 1);
			std::cout << indent << " Static: " << (isStatic ? "Yes" : "No") << std::endl;
		}
	};
}