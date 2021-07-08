#ifndef GBL_UTIL_H
#define GBL_UTIL_H

#ifdef __cplusplus
extern "c"
{
#endif

#define GBL_MIN(a, b) ((a) < (b) ? (a) : (b))
#define GBL_MAX(a, b) ((a) > (b) ? (a) : (b))
#define GBL_NON_ZERO_MIN(a, b) ((a) == 0 ? (b) : ((b) == 0 ? (a) : GBL_MIN(a, b)))

#define GBL_OFFSET_OF(type, member) ((size_t)&((type *)0)->member)
#define GBL_CONTAINER_OF(pMember, type, member) ((type *)((int8_t *)pMember - GBL_OFFSET_OF(type, member)))

#ifdef __cplusplus
}
#endif

#endif
