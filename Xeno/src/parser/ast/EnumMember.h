#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class EnumMemberNode : public Node
	{
	public:
		std::string name;
		int value;

		EnumMemberNode(const std::string& name, int value)
			: name(name), value(value) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "EnumMemberNode: " << name << ", Value:" << value << std::endl;
		}
	};
}