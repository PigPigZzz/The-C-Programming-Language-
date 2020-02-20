#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist
{ /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL)
    { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *s)
{
    struct nlist *np;
    unsigned hashval = hash(s);
    if(strcmp(hashtab[hashval]->name, s) == 0)
    {
        np = hashtab[hashval];
        hashtab[hashval] = np->next;
        free(np);
        return;
    }
    for (np = hashtab[hashval]; np->next != NULL; np = np->next)
    {
        if (strcmp(s, np->next->name) == 0)
        {
            struct nlist *tmp = np->next;
            np->next = tmp->next;
            free(tmp);
        }
    }
}

int main(void)
{
    install("HELLO", "hello");
    struct nlist *lp = lookup("HELLO");
    printf("%s:%s\n", lp->name, lp->defn);
    undef("HELLO");
    lp = lookup("HELLO");
    printf("%p\n", lp);
    return 0;
}