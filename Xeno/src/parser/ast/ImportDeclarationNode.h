#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ImportDeclarationNode : public Node
	{
	public:
		std::string moduleName;
		bool isGlobal;

		explicit ImportDeclarationNode(const std::string& moduleName, bool isGlobal)
			: moduleName(moduleName), isGlobal(isGlobal) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ImportDeclaration: " << moduleName << std::endl;
			std::cout << indent << "  isGlobal: " << (isGlobal == true ? "Global" : "Local") << std::endl;
		}
	};
}