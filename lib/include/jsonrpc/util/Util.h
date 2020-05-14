#ifndef HEADER_C731E470_956A_11EA_B57A_784F43782D09
#define HEADER_C731E470_956A_11EA_B57A_784F43782D09

#include <chrono>
#include <iomanip>

namespace util
{

auto ts()
{
	auto pt = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(pt);
	return std::put_time(std::localtime(&tt), "%F %T");
}

} // namespace util

#endif // HEADER_C731E470_956A_11EA_B57A_784F43782D09
