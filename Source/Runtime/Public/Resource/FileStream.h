#pragma once

// External Include
#include <fstream>
#include <vector>

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	namespace EFileStreamMode
	{
		enum Enum : u32
		{
			Read = 1 << 0,
			Write = 1 << 1
		};
	}

	struct FileHeader
	{
		u32 ArrayNum = 1;
		u32 StrideSize = 0;
	};
	
	class FileStream final
	{
	public:

		explicit FileStream(const std::string& filePath, u32 ioFlag);
		~FileStream();

		
		[[nodiscard]] bool IsOpenFile() const { return mbIsOpen; }
		void Close();
		
		template<typename Type>
		void Read(Type* outData);

		template<typename Type>
		void ReadToArray(std::vector<Type>* outData);

		template<typename Type>
		void Write(const Type& data);

		template<typename Type>
		void WriteFromArray(const std::vector<Type>& data);
		
	private:

		void ReadHeader(FileHeader* outHeader);
		void WriteHeader(const FileHeader& header);
		
	private:

		std::fstream mFileStream;
		bool mbIsOpen = false;
		
	};
	
	template <typename Type>
	void FileStream::Read(Type* outData)
	{
		FileHeader header;
		ReadHeader(&header);

		Assert(header.ArrayNum == 1 && header.StrideSize == sizeof(Type));
		mFileStream.read(reinterpret_cast<char*>(outData), header.StrideSize);
	}

	template <typename Type>
	void FileStream::ReadToArray(std::vector<Type>* outData)
	{
		FileHeader header;
		ReadHeader(&header);

		Assert(header.ArrayNum >= 1 && header.StrideSize == sizeof(Type));

		*outData->clear();
		*outData->shrink_to_fit();

		*outData->resize(header.ArrayNum);
		
		mFileStream.read(reinterpret_cast<i8*>(*outData->data()), header.ArrayNum * header.StrideSize);
	}

	template <typename Type>
	void FileStream::Write(const Type& data)
	{
		FileHeader header;
		ReadHeader(&header);

		Assert(header.ArrayNum == 1 && header.StrideSize == sizeof(Type));
		mFileStream.write(reinterpret_cast<const i8*>(&data), header.StrideSize);
	}

	template <typename Type>
	void FileStream::WriteFromArray(const std::vector<Type>& data)
	{
		FileHeader header;
		ReadHeader(&header);

		Assert(header.ArrayNum == 1 && header.StrideSize == sizeof(Type));
		mFileStream.write(reinterpret_cast<const i8*>(&data), header.ArrayNum * header.StrideSize);
	}
}
