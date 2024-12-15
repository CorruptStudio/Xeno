#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class AccessDeclarationNode : public Node
	{
	public:
		std::string accessModifier;
		std::vector<std::shared_ptr<Node>> members;

		AccessDeclarationNode(const std::string& accessModifier)
			: accessModifier(accessModifier) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "AccessDeclaration: " << accessModifier << std::endl;

			for (const auto& member : members)
			{
				member->printAst(depth + 1);
			}
		}
	};
}