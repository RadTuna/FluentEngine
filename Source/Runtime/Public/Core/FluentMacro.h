#pragma once

#define INDEX_NONE		(-1)

#define CLASS_BODY(Class, SuperClass) \
	public: \
		using Super = SuperClass; \
		using ThisClass = Class; \
		inline static ReflectionClass* GetClass() \
		{ \
			static ReflectionClass* refClass = nullptr; \
			if (!refClass) \
			{ \
				refClass = NewStack<ReflectionClass>( \
					gStackAllocator, \
					Super::GetClass(), \
					GenerateFID(), \
					#Class, \
					sizeof(Class)); \
			} \
			return refClass; \
		} \
	private: \

#define CLASS_BODY_NO_SUPER(Class) \
	public: \
		using ThisClass = Class; \
		inline static ReflectionClass* GetClass() \
		{ \
			static ReflectionClass* refClass = nullptr; \
			if (!refClass) \
			{ \
				refClass = NewStack<ReflectionClass>( \
					gStackAllocator, \
					nullptr, \
					GenerateFID(), \
					#Class, \
					sizeof(Class)); \
			} \
			return refClass; \
		} \
	private: \

	
