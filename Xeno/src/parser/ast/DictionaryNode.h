#pragma once
#include "Node.h"
#include <map>

namespace xeno::parser::ast
{
	class DictionaryNode : public Node
	{
	public:
		std::map<std::shared_ptr<Node>, std::shared_ptr<Node>> elements;
		  
		DictionaryNode(const std::map<std::shared_ptr<Node>, std::shared_ptr<Node>>& elements)
			: elements(elements) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "DictionaryNode" << std::endl;

			for (const auto& element : elements)
			{
				std::cout << indent << "Key:" << std::endl;
				element.first->printAst(depth + 1);
				std::cout << indent << "Value:" << std::endl;
				element.second->printAst(depth + 1);
			}
		}
	};
}