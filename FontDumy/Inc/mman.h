#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_


#include "stdint.h"

#define PROT_READ	(0x01)
#define	PROT_WRITE	(0x03)

#define	MAP_PRIVATE	(0x10)
#define	MAP_SHARED	(0x00)


#ifdef WIN32
#	ifndef	LIKELY
#		define LIKELY( exp )	exp
#		define UNLIKELY( exp )	exp
#	endif
#else
#	ifndef	LIKELY
#		define LIKELY( exp )	(__builtin_expect( (exp) != 0, true  ))
#		define UNLIKELY( exp )	(__builtin_expect( (exp) != 0, false ))
#	endif
#endif

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);

#endif
