#ifndef INCLUDED_FILE_SYSTEM
#define INCLUDED_FILE_SYSTEM

#include "../os_path.h"
#include "../posix/posix_filesystem.h"	// mode_t


LIB_API bool DirectoryExists(const OsPath& path);
LIB_API bool FileExists(const OsPath& pathname);

LIB_API u64 FileSize(const OsPath& pathname);


// (bundling size and mtime avoids a second expensive call to stat())
class CFileInfo
{
public:
	CFileInfo()
	{
	}

	CFileInfo(const OsPath& name, off_t size, time_t mtime)
		: name(name), size(size), mtime(mtime)
	{
	}

	const OsPath& Name() const
	{
		return name;
	}

	off_t Size() const
	{
		return size;
	}

	time_t MTime() const
	{
		return mtime;
	}

private:
	OsPath name;
	off_t size;
	time_t mtime;
};

LIB_API Status GetFileInfo(const OsPath& pathname, CFileInfo* fileInfo);

typedef std::vector<CFileInfo> CFileInfos;
typedef std::vector<OsPath> DirectoryNames;

LIB_API Status GetDirectoryEntries(const OsPath& path, CFileInfos* files, DirectoryNames* subdirectoryNames);

// same as boost::filesystem::create_directories, except that mkdir is invoked with
// <mode> instead of 0755.
// If the breakpoint is enabled, debug_break will be called if the directory didn't exist and couldn't be created.
LIB_API Status CreateDirectories(const OsPath& path, mode_t mode, bool breakpoint = true);

LIB_API Status DeleteDirectory(const OsPath& dirPath);

LIB_API Status CopyFile(const OsPath& path, const OsPath& newPath, bool override_if_exists = false);

#endif	// #ifndef INCLUDED_FILE_SYSTEM
