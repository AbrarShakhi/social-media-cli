#pragma once
struct Color {
	struct FG {
		const char GRAY[8] = "\033[1;30m";
		const char RED[8] = "\033[1;31m";
		const char GREEN[8] = "\033[1;32m";
		const char YELLOW[8] = "\033[1;33m";
		const char BLUE[8] = "\033[1;34m";
	};
	struct BG {
		const char MAGENTA[8] = "\033[1;45m";
	};
	const char NORMAL[5] = "\033[0m";
	const FG FG;
	const BG BG;
};