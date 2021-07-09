#pragma once

namespace Lippets
{
	namespace LUtils
	{
		namespace Classes
		{
			class NonCopyable
			{
			protected:
				NonCopyable() = default;
				~NonCopyable() = default;
				NonCopyable(NonCopyable const&) = delete;
				NonCopyable& operator=(NonCopyable const&) = delete;
			};
			template<typename T>
			class Singleton : NonCopyable {
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
		template<class T> T& getLValueFormRValue(T&& t) { return t; }
		template<class T> T* getRValueObjectPtr(T&& t) { return &t; }
	}
}
