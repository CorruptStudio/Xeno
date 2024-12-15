#pragma once
#include "Node.h"

namespace xeno::parser::ast
{
	class ListNode : public Node
	{
	public:
		std::vector<std::shared_ptr<Node>> elements;

		ListNode(const std::vector<std::shared_ptr<Node>>& elements)
			: elements(elements) {}

		void printAst(int depth = 0) const override {
			std::string indent(depth * 2, ' ');
			std::cout << indent << "ListNode: " << std::endl;

			for (auto& element : elements)
			{
				element->printAst(depth + 1);
			}
		}
	};
}