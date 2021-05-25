#pragma once

namespace Lippets
{
	namespace LUtils
	{
		class NonCopyable
		{
		protected:
			NonCopyable() = default;
			~NonCopyable() = default;
			NonCopyable(NonCopyable const &) = delete;
			NonCopyable& operator=(NonCopyable const &) = delete;
		};
		template<typename T>
		class Singleton : Lippets::LUtils::NonCopyable {
		public:
			static T& getInstance();
		};
		template<typename T>
		inline T& Singleton<T>::getInstance()
		{
			static T instance{ };
			return instance;
		}
	}
}


