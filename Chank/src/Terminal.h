#pragma once
#include "Tree.h"

namespace chank
{
	class Terminal
	{
	private:
		Tree* tree; // file system
	public:
		Terminal();
		~Terminal();
		void HandleInput();
	};
}
