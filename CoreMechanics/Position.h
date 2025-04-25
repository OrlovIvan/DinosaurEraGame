#pragma once

namespace positions
{
	const int Max_X = (32);
	const int Max_Y = (32);
	const int Min_X = (0);
	const int Min_Y = (0);

	struct Position
	{
		Position() = default;
		Position(int x, int y) : x(x), y(y) {}
		int x{};
		int y{};
	};
}