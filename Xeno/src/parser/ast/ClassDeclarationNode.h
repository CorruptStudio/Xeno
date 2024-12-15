#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ClassDeclarationNode : public Node
	{
	public:
		std::string name;
		std::string classType;
		std::vector<std::shared_ptr<Node>> members;
		std::string baseClass;

		ClassDeclarationNode(const std::string& name, const std::string& classType, std::vector<std::shared_ptr<Node>> members, const std::string& baseClass = "")
			: name(name), classType(classType), members(members), baseClass(baseClass) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ClassDeclaration: " << name << std::endl;

			for (const auto& accessDecl : members) {
				accessDecl->printAst(depth + 1);
			}
		}
	};
}