#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */
#define PERMS 0666 /* RW for owner, group, others */
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
typedef struct _iobuf {
    int cnt; /* characters left */
    char *ptr; /* next character position */
    char *base; /* location of buffer */
    struct{
        unsigned _READ : 1;
        unsigned _WRITE : 1;
        unsigned _UNBUF : 1;
        unsigned _EOF : 1;
        unsigned _ERR : 1;
    } flag; /* mode of file access */
    int fd; /* file descriptor */
} FILE;

FILE _iob[OPEN_MAX];

FILE *fopen(char *name, const char *mode)
{
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!(fp->flag._READ | fp->flag._WRITE))
            break; /* found free slot */
    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1) /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if(*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;
    if(!fp->flag._READ || fp->flag._EOF || fp->flag._ERR)
        return EOF;
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int main(void)
{
    FILE *fp1 = fopen("a", "r");
    FILE *fp2 = fopen("b", "w");
    int c1 = getc(fp1);
    int c2 = getc(fp2);
    if(c1 != EOF)
        write(STDOUT_FILENO, &c1, 1);
    if(c2 != EOF)
        write(STDOUT_FILENO, &c2, 1);
}