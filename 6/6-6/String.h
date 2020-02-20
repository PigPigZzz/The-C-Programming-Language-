#define STRING_STEP_LEN 1024
struct String
{
    char *str;
    int len;
    int size;
};

struct String creatString();
void deleteString(struct String *s);
void clearString(struct String *s);
void extendString(struct String *s);
void pushString(struct String *s, char c);