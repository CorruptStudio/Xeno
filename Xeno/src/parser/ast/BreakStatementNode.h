// BreakStatementNode.h
#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class BreakStatementNode : public Node {
	public:
		int line;
		int column;

		BreakStatementNode(int line, int column)
			: line(line), column(column) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "BreakStatement at line " << line << ", column " << column << std::endl;
		}
	};
}