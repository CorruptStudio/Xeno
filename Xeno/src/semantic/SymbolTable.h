#pragma once
#include <string>

namespace xeno::semantic
{
	class Symbol
	{
	public:
		std::string name;
		std::string type;
		bool isPublic;
	};

	class SymbolTable
	{
	};
}