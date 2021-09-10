struct trienode {
	struct trienode *child[255];
	int endofword;
	char meaning[500];
};

struct stack{
	struct trienode *m;
	int index;
};

struct word
{
    char w[200];
    struct word* next;
};

struct meaning
{
    char sentence[500];
    struct word* next_word;
    struct meaning* next_meaning;
};

char ret[100];
 

void insert_meaning(struct meaning** ,char *,char *);
void display_pairs(struct meaning* );
void insert_synonym(struct meaning** ,char *,char *);
int check_meaning(struct meaning* ,char*);
struct trienode* getnode();
void del_thes(struct meaning*, char* , char*);
void find_syn(struct meaning* ,char* , char*);
void del_word(char *);
void add_to_file(char* ,char* );
void delete_trie(struct trienode *,char *);
int check(struct trienode *);
void search_pre(struct trienode * , char *);
char* search(struct trienode * , char *);
struct stack pop();
void push(struct trienode *,int );
void display(struct trienode *);
void file_to_dict(struct trienode* , struct meaning** );
void insert(struct trienode* , char *, char *);
void destroy(struct meaning** );
void destroy_trie(struct trienode** );