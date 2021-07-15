#ifndef __FINK_ENDIANDEV_PKG_ENDIAN_H__
#define __FINK_ENDIANDEV_PKG_ENDIAN_H__ 1

/** compatibility header for endian.h
 * This is a simple compatibility shim to convert
 * BSD/Linux endian macros to the Mac OS X equivalents.
 * It is public domain.
 *  h代表本机架构 be是大端(big endian), le是小端(little endian)
 *
 *
 * */

#ifdef __APPLE__ __APPLE__

#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)

#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)

#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)

#elif _WIN32
#include <stdint.h>

static inline uint32_t bswap32(uint32_t x) {
	return ((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) |
		((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF);
}

static inline uint16_t cbswap16(uint16_t v) {
	return (((v & 0xff) << 8) | (((v) >> 8) & 0xff));
}

static inline uint64_t cbswap64(uint64_t v) {
	return ((((v) & 0x00000000000000ffULL) << 56) |
		(((v) & 0x000000000000ff00ULL) << 40) |
		(((v) & 0x0000000000ff0000ULL) << 24) |
		(((v) & 0x00000000ff000000ULL) << 8) |
		(((v) & 0x000000ff00000000ULL) >> 8) |
		(((v) & 0x0000ff0000000000ULL) >> 24) |
		(((v) & 0x00ff000000000000ULL) >> 40) |
		(((v) & 0xff00000000000000ULL) >> 56));
}



static inline uint16_t htobe16(uint16_t x) {
#ifdef	__LITTLE_ENDIAN
	return cbswap16(x);
#else
	return x;
#endif

}

static inline uint16_t be16toh(uint16_t x) {
#ifndef	__LITTLE_ENDIAN
	return x;
#else
	return cbswap16(x);
#endif
}

static inline uint32_t le16toh(uint32_t x) {
#ifdef  __LITTLE_ENDIAN
	return x;
#else
	return cbswap16(x);
#endif //  __LITTLE_ENDIAN
}


static inline uint32_t htole16(uint32_t x) {
#ifdef __LITTLE_ENDIAN
	return x;
#else
	return cbswap16(x);
#endif
}




static inline uint32_t htobe32(uint32_t x) {
#ifdef	__LITTLE_ENDIAN
	return bswap32(x);
#else
	return x;
#endif
}

static inline uint32_t be32toh(uint32_t x) {
#ifndef	__LITTLE_ENDIAN
	return x;
#else
	return bswap32(x);
#endif
}

static inline uint32_t le32toh(uint32_t x) {
#ifdef  __LITTLE_ENDIAN
	return x;
#else
	return bswap32(x);
#endif //  __LITTLE_ENDIAN
}



static inline uint32_t htole32(uint32_t x) {
#ifdef __LITTLE_ENDIAN
	return x;
#else
	return bswap32(x);
#endif
}




static inline uint64_t htobe64(uint64_t x) {
#ifdef	__LITTLE_ENDIAN
	return cbswap64(x);
#else
	return x;
#endif
}

static inline uint64_t be64toh(uint64_t x) {
#ifndef	__LITTLE_ENDIAN
	return x;
#else
	return cbswap64(x);
#endif
}

static inline uint64_t le64toh(uint64_t x) {
#ifdef  __LITTLE_ENDIAN
	return x;
#else
	return cbswap64(x);
#endif //  __LITTLE_ENDIAN
}



static inline uint64_t htole64(uint64_t x) {
#ifdef __LITTLE_ENDIAN
	return x;
#else
	return cbswap64(x);
#endif
}

#endif

#endif	/* __FINK_ENDIANDEV_PKG_ENDIAN_H__ */