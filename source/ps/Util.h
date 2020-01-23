#ifndef PS_UTIL_H
#define PS_UTIL_H

#include "../lib/os_path.h"
#include "../lib/file/vfs/vfs_path.h"

struct Tex;

void WriteSystemInfo();

const wchar_t* ErrorString(int err);

OsPath createDateIndexSubdirectory(const OsPath& parentDir);

void WriteScreenshot(const VfsPath& extension);
void WriteBigScreenshot(const VfsPath& extension, int tiles);

Status tex_write(Tex* t, const VfsPath& filename);

std::string Hexify(const std::string& s);
std::string Hexify(const u8* s, size_t length);

#endif // PS_UTIL_H
