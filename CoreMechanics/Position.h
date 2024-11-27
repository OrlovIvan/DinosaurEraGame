#pragma once

namespace positions
{
	const int Max_X = (32);
	const int Max_Y = (32);
	const int Min_X = (0);
	const int Min_Y = (0);

	struct Position
	{
		int x{ Max_X/2 };
		int y{ Max_Y/2 };
	};
}