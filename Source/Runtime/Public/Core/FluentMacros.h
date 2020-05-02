#pragma once

#define INDEX_NONE		(-1)

#define SIMD_CALL __vectorcall

#ifdef UNICODE
#define TXT(String) L##String
#elif
#define TXT(String) String
#endif

#define REFLECTION_CLASS(Class, SuperClass) \
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
					TXT(#Class), \
					sizeof(Class)); \
			} \
			return refClass; \
		} \
	private: \

#define REFLECTION_CLASS_NO_SUPER(Class) \
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
					TXT(#Class), \
					sizeof(Class)); \
			} \
			return refClass; \
		} \
	private: \


#define REFLECTION_PROPERTY (Type, Name) \
	static ReflectionProperty* refProperty_##Name = nullptr; \
	if (!refProperty_##Name) \
	{ \
		refProperty_##Name = NewStack<ReflectionProperty>( \
			gStackAllocator, \
			TXT(#Type), \
			TXT(#Name), \
			sizeof(Type));\
		refClass->AddProperty(refProperty_##Name); \
	} \


