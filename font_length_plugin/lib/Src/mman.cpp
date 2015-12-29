#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include "mman.h"

#ifdef WIN32

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
	void *buf = malloc(length);
	if(buf) {
		size_t total_read_bytes = 0;
		while(total_read_bytes < length) {
			int read_bytes = _read(fd, (uint8_t *)buf + total_read_bytes, length - total_read_bytes);
			if(read_bytes <= 0) break;
			total_read_bytes += read_bytes;
		}
		if(total_read_bytes != length) {
			free(buf); return NULL;
		}
	}

	return buf;
}

int munmap(void *addr, size_t length) {
	free(addr);
	return 0;
}

#endif

