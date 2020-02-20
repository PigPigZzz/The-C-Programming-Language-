#define LIST_SIZE 1024
struct Tree;
struct Tnode
{
    char *str;
    int line_num_list[LIST_SIZE];
    int list_size;
    struct Tnode *left;
    struct Tnode *right;
};

struct Tree
{
    struct Tnode *root;
};

struct Tree creatTree();
struct Tnode *pushTree(struct Tree *root, char *str, int n);
void printTree(struct Tree *root);
void deleteTree(struct Tree *root);
void recursionTree(struct Tnode *node, void (*callback)(struct Tnode *));
static struct Tnode *insertTnode(struct Tnode *node, char *str, int n);
static void printNode(struct Tnode *node);
static void freeNode(struct Tnode *node);
static struct Tnode *Talloc();