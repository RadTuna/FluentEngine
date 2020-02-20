#pragma once

template<typename T>
struct PointerRemover
{
	using Type = T;
};

template<typename T>
struct PointerRemover<T*>
{
	using Type = T;
};
