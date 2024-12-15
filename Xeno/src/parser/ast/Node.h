#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>

namespace xeno::parser::ast
{
	class Node {
	public:
		virtual ~Node() = default;
		virtual void printAst(int depth = 0) const = 0;
	};
}