typedef struct Dict Dict;

Dict *get_query_dict(char *query_string);
char *get_value(Dict *dictionary, char *key);

char *unencode(char *str);
