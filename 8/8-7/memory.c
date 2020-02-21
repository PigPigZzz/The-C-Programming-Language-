#include <unistd.h>
#include "memory.h"

#define NALLOC 1024

typedef long Align;
typedef union header
{
    struct
    {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
} Header;

static Header base;
static Header *allocator = NULL;
static Header *freep = NULL;

static Header *morecore(unsigned nu)
{
    void *cp;
    Header *up;
    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk((nu + 1) * sizeof(Header));
    if(cp == (void *)-1)
        return NULL;
    up = (Header *)cp;
    if(allocator == NULL)
    {
        allocator = up;
        allocator->s.size = nu + 1;
        allocator->s.ptr = allocator;
    }
    else
    {
        Header *tmp = allocator->s.ptr;
        allocator->s.ptr = up;
        allocator = up;
        allocator->s.size = nu + 1;
        allocator->s.ptr = tmp;
    }
    (up + 1)->s.size = nu;
    free(up + 2);
    return freep;
}

void *malloc(size_t size)
{
    Header *p, *prevp;
    unsigned nunits;
    if(size <= 0)
        return NULL;
    nunits = (size + sizeof(Header) - 1) / sizeof(Header) + 1;
    if((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for(p = prevp->s.ptr; p->s.size < nunits; prevp = p, p = p->s.ptr)
    {
        if(p == freep)
            if((p = morecore(nunits)) == NULL)
                return NULL;
    }
    if(p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
    else
    {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
    }
    return (void *)(p + 1);
}

void *calloc(size_t nmemb, size_t size)
{
    unsigned sum = nmemb * size;
    void *ptr = malloc(sum);
    if(ptr == NULL)
        return NULL;
    for(unsigned i = 0; i < sum; i++)
        *((char *)ptr + i) = 0;
    return ptr;
}

void free(void *ptr)
{
    Header *bp, *p;
    bp = (Header *)ptr - 1;
    if(allocator == NULL)
        goto err;
    for(p = allocator->s.ptr; !(ptr >= p && ptr < (p + p->s.size)); p = p->s.ptr)
        if(p == allocator)
        {
            err:
            write(STDERR_FILENO, "Illegal field\n", sizeof("Illegal field\n") - 1);
            return;
        }
    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;
}
