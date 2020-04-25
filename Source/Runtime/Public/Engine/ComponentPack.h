#pragma once

// External Include
#include <set>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "Core/Functor.h"
#include "IComponent.h"


namespace Fluent
{
	
	class ComponentPack
	{
	public:

		std::set<u64> ComponentIDSet;
		std::vector<void**> ComponentPtr;
		std::vector<u32> ComponentSize;
		
	public:

		explicit ComponentPack(u32 dataCapacity = 128)
		{
			mComponentInitData.reserve(dataCapacity);
		}
		~ComponentPack() = default;

		
		template<typename Type, typename ...Param>
		void AppendComponent(Type** componentPtr, Param&&... params);

		template<typename D>
		void CopyInitData(D* const dest, u64 size);

		void Clear();

	private:

		std::vector<u8> mComponentInitData;
		u32 mComponentDataSize = 0;

	};

	template <typename Type, typename ...Param>
	void ComponentPack::AppendComponent(Type** componentPtr, Param&&... params)
	{
		ReflectionClass* refClass = Type::GetClass();
		const u64 componentID = refClass->GetClassID();
		ComponentIDSet.emplace(componentID);

		ComponentPtr.emplace_back(reinterpret_cast<void**>(componentPtr));
		ComponentSize.emplace_back(static_cast<u32>(sizeof(Type)));

		
		Type initObject(params...);
		Type* initObjectPtr = &initObject;

		const u64 dataSize = static_cast<u64>(sizeof(Type));
		if (mComponentInitData.capacity() - mComponentDataSize <= dataSize)
		{
			const u64 currentCapacity = mComponentInitData.capacity() * 2;
			mComponentInitData.reserve(currentCapacity);
		}
		
		u8* const destPtr = mComponentInitData.data() + mComponentDataSize;
		MemCpy(destPtr, initObjectPtr, dataSize);
		mComponentDataSize += dataSize;
	}

	template <typename D>
	void ComponentPack::CopyInitData(D* const dest, u64 size)
	{
		MemCpy(dest, mComponentInitData.data(), size);
	}

	inline void ComponentPack::Clear()
	{
		ComponentIDSet.clear();
		ComponentPtr.clear();
		ComponentSize.clear();
		mComponentInitData.clear();
		mComponentDataSize = 0;
	}

}
