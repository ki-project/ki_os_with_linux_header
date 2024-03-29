#include <sys/types.h>
#include <asm/lowlevel.h>
#include <printk.c>

#ifndef _fs_kifs_h_
#define _fs_kifs_h_

typedef struct *fs_entry
{
  u32 data_type;
  u32 *path;
  u32 *flags; //rwx, rw, rx, r, w, wx, 
  u32 *save_loc;
  u32 *last_accessed; //date and time
} *fs_entry;

protected signed long bool read_allowed (*fs_entry file)
{
  u32 flg;
  flg = file->*flags;
  if (flg = "rwx" || flg = "rw" || flg = "rx" || flg = "r")
    return true;
  else
    return false;
}

protected signed long bool write_allowed (*fs_entry file)
{
  u32 flg;
  flg = file->*flags;
  if (flg = "rwx" || flg = "rw" || flg = "wx" || flg = "w")
    return true;
  else
    return false;
}

protected signed long bool exec_allowed (*fs_entry file)
{
  u32 flg;
  flg = file->*flags;
  if (flg = "rwx" || flg = "wx" || flg = "rx" || flg = "x")
    return true;
  else
    return false;
}

protected signed long long void move_file(*fs_entry file, u32 *dest)
{
  file *old_entry;
  file->*path = *dest;
  if (updateEntry(file,*dest) = 0)
    return FSUCCESS;
  else
    return FFAIL;
}

protected signed long long void create_file(u32 path, u32 flg)
{
  *fs_entry new_file;
  u32 last_accessed = getTime();
  new_file->data_type = "FILE";
  new_file->*path = path;
  new_file->*flag = flg;
  new_file->*save_loc = loc;
  new_file->*last_accessed = last_accessed;
  return new_file;
}

protected signed long long void create_folder(u32 path)
{
  *fs_entry new_folder;
  u32 last_accessed = getTime();
  u32 loc = getNextLoc();
  new_folder->data_type = "FOLDER";
  new_folder->*path = path;
  new_folder->*flag = "drw";
  new_folder->*save_loc = loc;
  new_folder->*last_accessed = last_accessed;
  return new_folder;
}

#endif //fs_kifs_h
