#ifndef _LGRESOURCE_READER_H_
#define _LGRESOURCE_READER_H_

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mman.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#endif
#include <errno.h>

// CLGResourceReader
class CLGResourceReader {
public:
	virtual ~CLGResourceReader() {
	}

	virtual bool isValid() = 0;
	virtual void seek(size_t pos) = 0;
	virtual size_t readData(uint8_t *buf, size_t size) = 0;
	virtual bool readUint32(uint32_t& val) = 0;
	virtual bool isLengthValid() const { return false; }
	virtual size_t getLength() const { return 0; }
	virtual bool isBufferValid() const { return false; }
	virtual const uint8_t* getBuffer() const { return NULL; }

	virtual const uint8_t* peekData(size_t size) {return NULL; }
};


class CFileReader : public CLGResourceReader {
public:
	CFileReader(const char *path) : fp(NULL) {       
		fp = fopen(path, "rb");       
		if(fp) {
			fseek(fp, 0, SEEK_END);
			length = (long)ftell(fp);
			fseek(fp, 0, SEEK_SET);
		}
	}

	~CFileReader() {
		if(fp) {
			fclose(fp);
			fp = NULL;
		}
	}

	virtual bool isValid() {
		return (fp != NULL);
	}

	virtual void seek(size_t pos) {
		if(-1 == fseek(fp, pos, SEEK_SET)) {
		}
	}

	virtual size_t readData(uint8_t *buf, size_t size) {
		return fread(buf, 1, size, fp);
	}

	virtual bool readUint32(uint32_t& val) {
		return (1 == fread(&val, sizeof(uint32_t), 1, fp));
	}

	virtual bool isLengthValid() const {
		return true;
	}

	virtual size_t getLengt() const {
		return length;
	}

private:
	FILE *fp;
	size_t length;
};

class CMemoryReader : public CLGResourceReader {
public:
	CMemoryReader(const uint8_t *buf, size_t bufSize) : mem(buf), memEnd(buf + bufSize), curPtr(buf) {
	}

	~CMemoryReader() {
	}

	virtual bool isValid() {
		return (mem != NULL);
	}

	virtual void seek(size_t pos) {
		if(LIKELY(mem + pos < memEnd)) {
			curPtr = mem + pos;
		} else {
			curPtr = memEnd;
		}
	}

	virtual size_t readData(uint8_t *buf, size_t size) {
		size_t readBytes = (size < (size_t)(memEnd - curPtr)) ? size : (size_t)(memEnd - curPtr);

		if(LIKELY(readBytes > 0)) {
			memcpy(buf, curPtr, readBytes);
			curPtr += readBytes;
		}

		return readBytes;
	}

	virtual bool readUint32(uint32_t& val) {
		if(LIKELY(memEnd - curPtr >= sizeof(uint32_t))) {
			val = curPtr[0] | (curPtr[1] << 8) | (curPtr[2] << 16) | (curPtr[3] << 24);
			curPtr += sizeof(uint32_t);
			return true;
		} else {
			return false;
		}
	}

	virtual const uint8_t* peekData(size_t size) { 
		const uint8_t *ptr = NULL;

		if(LIKELY(size <= (size_t)(memEnd - curPtr))) {
			ptr = curPtr;
			curPtr += size;
		}

		return ptr;
	}

	virtual bool isLengthValid() const {
		return true;
	}

	virtual size_t getLength() const {
		return (size_t)(memEnd - mem);
	};

	virtual bool isBufferValid() const { 
		return true;
	}

	virtual const uint8_t* getBuffer() const { 
		return mem;
	}

public:
	void set(const uint8_t *buf, size_t bufSize) {
		mem = curPtr = buf;
		memEnd = buf + bufSize;
	}

private:
	const uint8_t *mem, *memEnd, *curPtr;
};

class CMappedFileReader : public CLGResourceReader {
public:
	CMappedFileReader(const char *path) : fd(-1), memSize(0), mem(NULL), memEnd(NULL), curPtr(NULL) {       
		fd = open(path, O_RDONLY
#ifdef WIN32
			| O_BINARY
#endif
			);


		
		if(fd >= 0) {
			struct stat sb;
			if(fstat(fd, &sb) >= 0) {
				memSize = sb.st_size;

				mem = (uint8_t *)mmap(0, memSize, PROT_READ, MAP_SHARED, fd, 0);
				if(mem) {
					curPtr = mem;
					memEnd = mem + memSize;
				}
			}

			if(!mem) {
				close(fd);
				fd = -1;
			}
		}
	}

	~CMappedFileReader() {
		if(fd >= 0) {
			if(mem) {
				int ret = munmap(mem, memSize);
				assert(ret == 0);
				mem = NULL;
			}
			close(fd);
			fd = -1;
		}
	}

	virtual bool isValid() {
		return (mem != NULL);
	}

	virtual void seek(size_t pos) {		
		if(LIKELY(mem + pos < memEnd)) {
			curPtr = mem + pos;
		} else {
			curPtr = memEnd;
		}
	}

	virtual size_t readData(uint8_t *buf, size_t size) {
		size_t readBytes = (size < (size_t)(memEnd - curPtr)) ? size : (size_t)(memEnd - curPtr);

		if(LIKELY(readBytes > 0)) {
			memcpy(buf, curPtr, readBytes);
			curPtr += readBytes;
		}

		return readBytes;
	}

	virtual bool readUint32(uint32_t& val) {
		if(LIKELY(memEnd - curPtr >= sizeof(uint32_t))) {
			val = curPtr[0] | (curPtr[1] << 8) | (curPtr[2] << 16) | (curPtr[3] << 24);
			curPtr += sizeof(uint32_t);
			return true;
		} else {
			return false;
		}
	}

	virtual const uint8_t* peekData(size_t size) { 
		const uint8_t *ptr = NULL;

		if(LIKELY(size <= (size_t)(memEnd - curPtr))) {
			ptr = curPtr;
			curPtr += size;
		}

		return ptr;
	}

	virtual bool isLengthValid() const {
		return true;
	}

	virtual size_t getLength() const {
		return memSize;
	}

	virtual bool isBufferValid() const { 
		return true;
	}

	virtual const uint8_t* getBuffer() const { 
		return mem;
	}

private:
	int fd;
	size_t memSize;
	uint8_t *mem, *memEnd, *curPtr;
};

class CRawFileReader : public CLGResourceReader {
public:
	CRawFileReader(const char *path) : fd(-1) {       
		fd = open(path, O_RDONLY
#ifdef WIN32
			| O_BINARY
#endif
			);

		if(fd >= 0) {
			length = (size_t)lseek(fd, 0, SEEK_END);
			lseek(fd, 0, SEEK_SET);
		}
	}

	~CRawFileReader() {
		if(fd >= 0) {
			close(fd);
		}
	}

	virtual bool isValid() {
		return (fd >= 0);
	}

	virtual void seek(size_t pos) {
		if(-1 == lseek(fd, pos, SEEK_SET)) {
		}
	}

	virtual size_t readData(uint8_t *buf, size_t size) {
		return (size_t)read(fd, buf, size);
	}

	virtual bool readUint32(uint32_t& val) {
		return (sizeof(uint32_t) == read(fd, &val, sizeof(uint32_t)));
	}

	virtual bool isLengthValid() const {
		return true;
	}

	virtual size_t getLength() const {
		return length;
	}

private:
	int fd;
	size_t length;
};

class CSharedMemoryReader : public CLGResourceReader {
public:
	typedef enum {
		BINARY_TYPE_FONT,
		BINARY_TYPE_RESOURCE,
	} BinaryType;

private:
	enum {
		LGSHARED_MEMORY_READER_GUARD = 0x31524452, // RDR1

		LGSHARED_MEMORY_READER_SHM_KEY_FONT		= 9990,
		LGSHARED_MEMORY_READER_SHM_KEY_RESOURCE	= 9991,

		LGSHARED_MEMORY_READER_SHM_SIZE_FONT		= (500 * 1024),
		LGSHARED_MEMORY_READER_SHM_SIZE_RESOURCE	= (7 * 1024 * 1024),
	};

#define	LGSHARED_MEMORY_READER_SEM_NAME				"LGSHARED_MEMORY_READER_SEM_NAME"
#define	LGSHARED_MEMORY_READER_SHM_NAME_FONT		"LGSHARED_MEMORY_READER_SHM_NAME_FONT"
#define	LGSHARED_MEMORY_READER_SHM_NAME_RESOURCE	"LGSHARED_MEMORY_READER_SHM_NAME_RESOURCE"

public:
	CSharedMemoryReader(const char *path, BinaryType _binType) : reader(NULL), binType(_binType), shmId(-1), shmBuf(NULL)  {
#ifdef WIN32
		reader = new CMappedFileReader(path);
#else
		key_t shmKey;
		uint32_t shmSize;
		if(binType == BINARY_TYPE_FONT) {
			shmKey = (key_t)LGSHARED_MEMORY_READER_SHM_KEY_FONT;
			shmSize = LGSHARED_MEMORY_READER_SHM_SIZE_FONT;
		} else {
			shmKey = (key_t)LGSHARED_MEMORY_READER_SHM_KEY_RESOURCE;
			shmSize = LGSHARED_MEMORY_READER_SHM_SIZE_RESOURCE;
		}
				
		int fd = open(path, O_RDONLY);
		if(fd >= 0) {
			struct stat statBuf;
			if(0 == fstat(fd, &statBuf)) {
				if(statBuf.st_size > (shmSize - 4)) {
					reader = new CRawFileReader(path);
				} else {
					sem_t *sem = NULL;
			
					uint32_t *p32;
					
					do {
						sem = sem_open(LGSHARED_MEMORY_READER_SEM_NAME, O_CREAT, S_IRUSR | S_IWUSR, 1);
						if(!sem) break;
			
						// if(0 != sem_wait(sem)) break;
						sem_wait(sem);
			
						shmId = shmget(shmKey, shmSize, IPC_CREAT | 0666);
						if(shmId < 0) break;
			
						shmBuf = (uint8_t *)shmat(shmId, 0, 0);
						if(!shmBuf) break;
			
						p32 = (uint32_t *)shmBuf;
						if(*p32 != LGSHARED_MEMORY_READER_GUARD) {
							off_t totalRead = 0;
							uint8_t *p8 = shmBuf + 4, *p8_end = p8 + shmSize - 4;
							ssize_t readBytes;
			
							while(totalRead < statBuf.st_size) {
								readBytes = read(fd, p8, p8_end - p8);
								if(readBytes <= 0) break;
			
								p8 += readBytes;
								totalRead += readBytes;
							}
							if(totalRead != statBuf.st_size) break;
			
							*p32 = LGSHARED_MEMORY_READER_GUARD;
							// msync(shmBuf, 4, MS_SYNC | MS_INVALIDATE);
						}
			
						reader = new CMemoryReader(shmBuf + 4, shmSize - 4);
					} while(false);
			
					if(sem) {
						sem_post(sem);
			
						sem_close(sem);
						sem = NULL;
					}
			
					if(!reader) {
						if(shmBuf) {
							shmdt(shmBuf);
							shmBuf = NULL;
						}
			
						if(shmId >= 0) {
							shmctl(shmId, IPC_RMID, NULL);
							shmId = -1;
						}
					}
				}
			}

			close(fd);
		}
#endif
	}

	~CSharedMemoryReader() {
		if(reader) {
			delete reader;
		}

#ifndef WIN32
		if(shmBuf) {
			shmdt(shmBuf);
		}
			
		if(shmId >= 0) {
			shmctl(shmId, IPC_RMID, NULL);
		}
#endif
	}

	virtual bool isValid() {
		if(reader) {
			return reader->isValid();
		}
		return false;
	}

	virtual void seek(size_t pos) {
		if(reader) {
			reader->seek(pos);
		}
	}

	virtual size_t readData(uint8_t *buf, size_t size) {
		if(reader) {
			return reader->readData(buf, size);
		}
		return 0;
	}

	virtual bool readUint32(uint32_t& val) {
		if(reader) {
			return reader->readUint32(val);
		}
		return false;
	}

private:
	BinaryType binType;
	CLGResourceReader *reader;

	int shmId;
	uint8_t *shmBuf;
};

#endif

