struct Tree;
struct Tnode
{
    void *element;
    struct Tnode *left;
    struct Tnode *right;
};

struct Tree
{
    struct Tnode *root;
};

struct Tree creatTree();
struct Tnode *pushTree(struct Tree *root, void *element, int (*cmp)(void *, void *), void *(*callback_element)(void *, void *));
void printTree(struct Tree *root, void (*callback_print)(void *));
void deleteTree(struct Tree *root, void (*callback_free)(void *));
void recursionTree(struct Tnode *node, void (*callback)(void *));
static struct Tnode *insertTnode(struct Tnode *node, void *element, int (*cmp)(void *, void *), void *(*callback_element)(void *, void *));
static void freeNode(struct Tnode *node, void (*callback_free)(void *));
static struct Tnode *Talloc();
