#ifndef INCLUDED_FILE
#define INCLUDED_FILE

#include "../os_path.h"
#include "../sysdep/filesystem.h"	// O_*, S_*

namespace ERR
{
	const Status FILE_ACCESS = -110300;
	const Status FILE_NOT_FOUND = -110301;
}

// @param oflag: either O_RDONLY or O_WRONLY (in which case O_CREAT and
//   O_TRUNC are added), plus O_DIRECT if aio is desired
// @return file descriptor or a negative Status
LIB_API Status FileOpen(const OsPath& pathname, int oflag);
LIB_API void FileClose(int& fd);

class File
{
public:
	File()
		: m_PathName(), m_FileDescriptor(-1)
	{
	}

	File(const OsPath& pathname, int oflag)
	{
		THROW_STATUS_IF_ERR(Open(pathname, oflag));
	}

	~File()
	{
		Close();
	}

	Status Open(const OsPath& pathName, int openFlag)
	{
		Status ret = FileOpen(pathName, openFlag);
		RETURN_STATUS_IF_ERR(ret);
		m_PathName = pathName;
		m_FileDescriptor = static_cast<int>(ret);
		m_OpenFlag = openFlag;
		return INFO::OK;
	}

	void Close()
	{
		FileClose(m_FileDescriptor);
	}

	const OsPath& Pathname() const
	{
		return m_PathName;
	}

	int Descriptor() const
	{
		return m_FileDescriptor;
	}

	int Flags() const
	{
		return m_OpenFlag;
	}

private:
	OsPath m_PathName;
	int m_FileDescriptor;
	int m_OpenFlag;
};

typedef shared_ptr<File> PFile;

#endif	// #ifndef INCLUDED_FILE
