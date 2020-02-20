#include "Link.h"
LinkHead *creatLink(void)
{
    LinkHead *res = (LinkHead *)malloc(sizeof(LinkHead));
    res->head = (Link *)malloc(sizeof(Link));//创建首元素
    res->tail = (Link *)malloc(sizeof(Link));//创建尾元素
    res->head->data = NULL;
    res->head->next = res->tail;
    res->head->pre = NULL;
    res->tail->data = NULL;
    res->tail->next = NULL;
    res->tail->pre = res->head;
    res->length = 0;
    return res;
}
void delLink(LinkHead *hdr)
{
    while(hdr->length != 0)
        pop_frontLink(hdr);
    free(hdr->head);
    free(hdr->tail);
    free(hdr);
    hdr = NULL;
}
int push_backLink(void *data, int size, LinkHead *hdr)
{
    void *new_data = malloc(size);
    Link *node = (Link *)malloc(sizeof(Link));
    if(new_data == NULL || node == NULL)
        return -1;
    memcpy(new_data, data, size);
    node->data = new_data;
    node->pre = hdr->tail->pre;
    node->next = hdr->tail;
    node->pre->next = node;
    hdr->tail->pre = node;
    hdr->length++;
    return 0;
}
int push_frontLink(void *data, int size, LinkHead *hdr)
{
    void *new_data = malloc(size);
    Link *node = (Link *)malloc(sizeof(Link));
    if(new_data == NULL || node == NULL)
        return -1;
    memcpy(new_data, data, size);
    node->data = new_data;
    node->next = hdr->head->next;
    node->pre = hdr->head;
    node->next->pre = node;
    hdr->head->next = node;
    hdr->length++;
    return 0;
}
void pop_backLink(LinkHead *hdr)
{
    Link *node = hdr->tail->pre;
    hdr->tail->pre = node->pre;
    node->pre->next = hdr->tail;
    free(node->data);
    free(node);
    hdr->length--;
}
void pop_frontLink(LinkHead *hdr)
{
    Link *node = hdr->head->next;
    hdr->head->next = node->next;
    node->next->pre = hdr->head;
    free(node->data);
    free(node);
    hdr->length--;
}
