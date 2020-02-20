#pragma once

#include <utility>

#include "Core/Core.h"
#include "Core/Utility.h"

namespace Fluent
{

	template<typename Fn, typename FnType>
	class FunctionCaller;
	
	template<typename Fn, typename R, typename ...Params>
	class FunctionCaller<Fn, R(Params...)>
	{
	public:
		
		static R Call(void* object, Params&... params)
		{
			return std::forward<Fn>(*(Fn*)object)(std::forward<Params>(params)...);
		}

	};
	
	template<typename T>
	class Functor;

	template<typename R, typename ...Params>
	class Functor<R(Params...)>
	{
	public:

		using Func = R(*)(void*, Params...);
		
		explicit Functor() noexcept;

		template<typename Fn>
		explicit Functor(Fn&& function) noexcept;

		Functor(const Functor& other) = delete;
		Functor(Functor&& other) noexcept;

		~Functor() = default;

		Functor& operator=(const Functor&) = delete;
		Functor& operator=(Functor&& other) noexcept;

		template<typename Fn>
		Functor& operator=(Fn&& function);
		
		R operator()(Params... args);

		bool IsValid() const;

	private:

		Func mFunction;
		void* mConvertedFunction;

	};

	template <typename R, typename ... Params>
	Functor<R(Params...)>::Functor() noexcept
	{
		mFunction = nullptr;
		mConvertedFunction = nullptr;
	}

	template <typename R, typename ... Params>
	template <typename Fn>
	Functor<R(Params...)>::Functor(Fn&& function) noexcept
	{
		mConvertedFunction = (void*)&function;
		using DecayedFuncType = typename PointerRemover<decltype(&function)>::Type;

		if (mConvertedFunction != nullptr)
		{ 
			mFunction = FunctionCaller<DecayedFuncType, R(Params...)>::Call;
		}
	}

	template <typename R, typename ... Params>
	Functor<R(Params...)>::Functor(Functor&& other) noexcept
	{
		mFunction = other.mFunction;
		mConvertedFunction = other.mConvertedFunction;
		other.mFunction = nullptr;
		other.mConvertedFunction = nullptr;
	}

	template <typename R, typename ... Params>
	Functor<R(Params...)>& Functor<R(Params...)>::operator=(Functor&& other) noexcept
	{
		mFunction = other.mFunction;
		mConvertedFunction = other.mConvertedFunction;
		other.mFunction = nullptr;
		other.mConvertedFunction = nullptr;
	}

	template <typename R, typename ... Params>
	template <typename Fn>
	Functor<R(Params...)>& Functor<R(Params...)>::operator=(Fn&& function)
	{
		mConvertedFunction = (void*)&function;
		using DecayedFuncType = typename PointerRemover<decltype(&function)>::Type;
		
		if (mConvertedFunction != nullptr)
		{
			mFunction = FunctionCaller<DecayedFuncType, R(Params...)>::Call;
		}

		return *this;
	}

	template <typename R, typename ... Params>
	R Functor<R(Params...)>::operator()(Params... args)
	{
		return mFunction(mConvertedFunction, args...);
	}

	template <typename R, typename ... Params>
	bool Functor<R(Params...)>::IsValid() const
	{
		return mFunction != nullptr ? true : false;
	}
}

