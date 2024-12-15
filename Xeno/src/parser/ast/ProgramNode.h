#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ProgramNode : public Node
	{
	public:
		std::vector<std::shared_ptr<Node>> imports;
		std::vector<std::shared_ptr<Node>> classDeclarations;

		void printAst(int depth) const override {
			std::string indent(depth * 2, '	');
			std::cout << indent << "ProgramNode" << std::endl;

			for (const auto & import : imports)
			{
				import->printAst(depth + 1);
			}
			for (const auto & classDecl : classDeclarations)
			{
				classDecl->printAst(depth + 1);
			}
		};
	};
}