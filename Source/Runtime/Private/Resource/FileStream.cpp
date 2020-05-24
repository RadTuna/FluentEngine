
// Primary Include
#include "Resource/FileStream.h"


namespace Fluent
{
	FileStream::FileStream(const std::string& filePath, u32 ioFlags)
	{
		Assert(ioFlags > 0);

		i32 streamFlags = std::ios::binary;
		
		if ((ioFlags & EFileStreamMode::Read) != 0)
		{
			streamFlags |= std::ios::in;
		}
		if ((ioFlags & EFileStreamMode::Write) != 0)
		{
			streamFlags |= std::ios::out;
		}
		
		mFileStream.open(filePath, streamFlags);
		if (mFileStream.fail())
		{
			LOG_CONSOLE_FORMAT("Failded to find /%s", filePath.c_str());
			mbIsOpen = false;
			return;
		}

		mbIsOpen = true;
	}

	FileStream::~FileStream()
	{
		Close();
	}

	void FileStream::Close()
	{
		if (mFileStream.is_open())
		{
			mFileStream.close();
		}
	}

	void FileStream::ReadHeader(FileHeader* outHeader)
	{
		mFileStream.read(reinterpret_cast<i8*>(outHeader), sizeof(FileHeader));
	}

	void FileStream::WriteHeader(const FileHeader& header)
	{
		mFileStream.write(reinterpret_cast<const i8*>(&header), sizeof(FileHeader));
	}
}
