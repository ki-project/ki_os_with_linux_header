#include <sys/types.h>

#ifndef page_h_
#define page_h_

typedef struct page
{
   uint32 present    : 1;   // Page present in memory
   uint32 rw         : 1;   // Read-only if clear, readwrite if set
   uint32 user       : 1;   // Supervisor level only if clear
   uint32 accessed   : 1;   // Has the page been accessed since last refresh?
   uint32 dirty      : 1;   // Has the page been written to since last refresh?
   uint32 unused     : 7;   // Amalgamation of unused and reserved bits
   uint32 frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   page_table_t *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   uint32 tablesPhysical[1024];
   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   uint32 physicalAddr;
} page_directory_t;

#endif //page_h_