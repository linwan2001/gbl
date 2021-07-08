#ifndef GBL_LIST_H
#define GBL_LIST_H

#ifdef __cplusplus
extern "c"
{
#endif

/*
 * 多核无锁环境注意乱序问题
 */

#define GBL_LIST_INIT_VAL(node) { &(node), &(node) }

typedef struct gblListNode
{
    struct gblListNode *pNext;
    struct gblListNode *pPrev;
}gblListNode_t;

typedef gblListNode_t gblListHead_t;

static inline void gblListInit(gblListNode_t *pNode)
{
    pNode->pPrev = pNode;
    pNode->pNext = pNode;
    
    return;
}

static inline void gblListAddBetween(gblListNode_t *pPrev, gblListNode_t *pNext, 
    gblListNode_t *pNode)
{
    pNext->pPrev = pNode;
    pNode->pNext = pNext;
    pNode->pPrev = pPrev;
    pPrev->pNext = pNode;
    
    return;
}

static inline void gblListAdd(gblListNode_t *pHead, gblListNode_t *pNode)
{
    gblListAddBetween(pHead, pHead->pNext, pNode);
    
    return;
}

static inline void gblListAddTail(gblListNode_t *pHead, gblListNode_t *pNode)
{
    gblListAddBetween(pHead->pPrev, pHead, pNode);
    
    return;
}

static inline void gblListDelBetween(gblListNode_t *pPrev, gblListNode_t *pNext)
{
    pNext->pPrev = pPrev;
    pPrev->pNext = pNext;
    
    return;
}

static inline void gblListDel(gblListNode_t *pNode)
{
    gblListDelBetween(pNode->pPrev, pNode->pNext);
    
    pNode->pNext = NULL;
    pNode->pPrev = NULL;
    
    return;
}

#define GBL_LIST_ENTRY(pNode, type, member) GBL_CONTAINER_OF(pNode, type, member)

#define GBL_LIST_FIRST_ENTRY(pHead, type, member) GBL_LIST_ENTRY((pHead)->pNext, type, member)

#define GBL_LIST_LAST_ENTRY(pHead, type, member) GBL_LIST_ENTRY((pHead)->pPrev, type, member)

#define GBL_LIST_NEXT_ENTRY(pEntry, member) \
    GBL_LIST_ENTRY((pEntry)->member.pNext, typeof(*(pEntry)), member)

#define GBL_LIST_PREV_ENTRY(pEntry, member) \
    GBL_LIST_ENTRY((pEntry)->member.pPrev, typeof(*(pEntry)), member)

#define GBL_LIST_TRAVERSE(pHead, pNode) \
    for ((pNode) = (pHead)->pNext; (pNode) != (pHead); (pNode) = (pNode)->pNext)

#define GBL_LIST_SAFE_TRAVERSE(pHead, pNode, pNext) \
    for ((pNode) = (pHead)->pNext, (pNext) = (pNode)->pNext; \
        (pNode) != (pHead); \
        (pNode) = (pNext), (pNext) = (pNode)->pNext)

#define GBL_LIST_TRAVERSE_ENTRY(pHead, pEntry, member) \
    for ((pEntry) = GBL_LIST_FIRST_ENTRY(pHead, typeof(*(pEntry)), member); \
        &(pEntry)->member != (pHead); \
        (pEntry) = GBL_LIST_NEXT_ENTRY(pEntry, member))

#define GBL_LIST_SAFE_TRAVERSE_ENTRY(pHead, pEntry, pNext, member) \
    for ((pEntry) = GBL_LIST_FIRST_ENTRY(pHead, typeof(*(pEntry)), member), \
        (pNext) = GBL_LIST_NEXT_ENTRY(pEntry, member); \
        &(pEntry)->member != (pHead); \
        (pEntry) = (pNext), \
        (pNext) = GBL_LIST_NEXT_ENTRY(pEntry, member))

#ifdef __cplusplus
}
#endif

#endif
