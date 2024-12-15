// ForeachStatementNode.h
#pragma once
#include "Node.h"
#include <memory>

namespace xeno::parser::ast
{
	class ForeachStatementNode : public Node {
	public:
		std::string variableType;
		std::string variableName;
		std::shared_ptr<Node> collection;
		std::shared_ptr<Node> body;

		ForeachStatementNode(const std::string& variableType, const std::string& variableName, std::shared_ptr<Node> collection, std::shared_ptr<Node> body)
			: variableType(variableType), variableName(variableName), collection(collection), body(body) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ForeachStatement:" << std::endl;
			std::cout << indent << "  Variable: " << variableType << " " << variableName << std::endl;
			std::cout << indent << "  Collection:" << std::endl;
			if (collection) collection->printAst(depth + 1);
			std::cout << indent << "  Body:" << std::endl;
			if (body) body->printAst(depth + 1);
		}
	};
}