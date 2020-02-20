#include <stdlib.h>
#include <string.h>
typedef struct Link
{
    struct Link *next;
    struct Link *pre;
    void *data;
}Link;//链表元素
typedef struct LinkHead
{
    Link *head;
    Link *tail;
    int length;
}LinkHead;//链表头
LinkHead *creatLink(void);//创建链表
void delLink(LinkHead *hdr);//删除链表
int push_backLink(void *data, int size, LinkHead *hdr);//从后面放入元素
int push_frontLink(void *data, int size, LinkHead *hdr);//从前面放入元素
void pop_backLink(LinkHead *hdr);//从后面弹出元素
void pop_frontLink(LinkHead *hdr);//从前面弹出元素
