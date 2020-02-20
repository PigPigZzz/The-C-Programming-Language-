#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>

void getMode(mode_t mode, char *buf)
{
    if (buf == NULL)
    {
        fprintf(stderr, "buf can't be NULL\n");
        return;
    }
    memset(buf, 0, 11);
    *buf++ = (mode & S_IFDIR) ? 'd' : '-';
    *buf++ = (mode & S_IRUSR) ? 'r' : '-';
    *buf++ = (mode & S_IWUSR) ? 'w' : '-';
    *buf++ = (mode & S_IXUSR) ? 'x' : '-';
    *buf++ = (mode & S_IRGRP) ? 'r' : '-';
    *buf++ = (mode & S_IWGRP) ? 'w' : '-';
    *buf++ = (mode & S_IXGRP) ? 'x' : '-';
    *buf++ = (mode & S_IROTH) ? 'r' : '-';
    *buf++ = (mode & S_IWOTH) ? 'w' : '-';
    *buf = (mode & S_IXOTH) ? 'x' : '-';
}

void timespace2str(struct timespec ts, char *buff)
{
    struct tm *tp = gmtime((time_t*)&ts.tv_sec);
    strftime(buff, 20, "%F %T", tp);
}

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[PATH_MAX];
    struct dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue; /* skip self and parent */
        if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                    dir, dp->d_name);
        else
        {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

void fsize(char *filename)
{
    struct stat stbuf;
    char mode_buff[11];
    char atime_buff[20], mtime_buff[20], ctime_buff[20];
    if(stat(filename, &stbuf) == -1)
    {
        fprintf(stderr, "fsize: can't access %s\n", filename);
        return;
    }
    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(filename, fsize);
    getMode(stbuf.st_mode, mode_buff);
    timespace2str(stbuf.st_atim, atime_buff);
    timespace2str(stbuf.st_mtim, mtime_buff);
    timespace2str(stbuf.st_ctim, ctime_buff);
    printf("size:%-8ld device:%d i-node:%d mode:%s uid:%d gid:%d atime:%s mtime:%s ctime:%s %s\n", stbuf.st_size, stbuf.st_dev, stbuf.st_ino, mode_buff,
            stbuf.st_uid, stbuf.st_gid, atime_buff, mtime_buff, ctime_buff, filename);
}

int main(int argc, char *argv[])
{
    if(argc == 1)
        fsize(".");
    else
        for(int i = 1; i < argc; i++)
            fsize(argv[i]);
    return 0;
}