#pragma once
#include <vector>
using std::vector;
namespace Lippets
{
	namespace Containers
	{
		template <class T, typename T2>
		inline void insertTo(T* arr, const T2& data, bool begin = true)
		{
			if (begin)
				arr->emplace(arr->begin(), data);
			else
				arr->emplace(arr->end(), data);
		}
		template <class T>
		inline void deleteFrom(T* arr, size_t id)
		{
			arr->erase(arr->begin() + id);
		}
		template <class T, typename T2>
		inline bool findIn(T* arr, T2 val) /////////
		{
			return (std::find(arr->begin(), arr->end(), val) != arr->end());
		}
		template <class T, typename T2>
		inline int countIn(T* arr, T2 val)
		{
			int ret = 0;
			for (auto&& e : *arr)
				if (e == val)
					ret += 1;
			return ret;
		} // namespace Containers
	} // namespace Lippets
}
