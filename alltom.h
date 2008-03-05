typedef struct Dict Dict;

Dict *get_query_dict(char *query_string);
void free_dict(Dict *d);
char *get_value(Dict *dictionary, char *key);

char *unencode(char *str);
