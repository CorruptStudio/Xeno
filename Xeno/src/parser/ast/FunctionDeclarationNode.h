#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class FunctionDeclarationNode : public Node
	{
	public:
		std::string name;
		std::string returnType;
		std::vector <std::string> parameters;
		std::vector <std::shared_ptr<Node>> body;
		bool isStatic;
		bool isOverloaded;

		FunctionDeclarationNode(const std::string& name, const std::string& returnType, const std::vector<std::string>& parameters,  const std::vector <std::shared_ptr<Node>>& body, bool isStatic, bool isOverloaded)
			: name(name), returnType(returnType), parameters(parameters), body(body), isStatic(isStatic), isOverloaded(isOverloaded) {}

		void printAst(int depth) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "FunctionDeclaration: " << name << std::endl;
			for (const auto& param : parameters) {
				std::cout << indent << "  Parameter: " << param << std::endl;
			}
			std::cout << indent << " Return Type: " << returnType << std::endl;
			for (const auto& member : body)
			{
				member->printAst(depth + 1);
			}
			std::cout << indent << " Static: " << (isStatic ? "Yes" : "No") << std::endl;
		}
	};
}