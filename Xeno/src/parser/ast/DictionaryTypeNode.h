#pragma once
#include "Node.h"
#include <map>

namespace xeno::parser::ast
{
	class DictionaryTypeNode : public Node
	{
	public:
		std::string keyType;
		std::string valueType;

		DictionaryTypeNode(const std::string& keyType, const std::string& valueType)
			: keyType(keyType), valueType(valueType) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "DictionaryTypeNode: <" << keyType << ", " << valueType << ">" << std::endl;
		}
	};
}