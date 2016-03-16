#include <sys/types.h>

#ifndef strlen_c_
#define strlen_c_

size_t strlen(const char* str) { 
  size_t ret = 0;
  while ( str[ret] != 0 ) ret++;
  return ret;
}

#endif //strlen_c_