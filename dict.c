#include <stdlib.h>
#include <string.h>
#include "alltom.h"

typedef struct Pair {
	char *key, *value;
	struct Pair *next;
} Pair;

struct Dict {
	Pair *head;
};

static char *parse_pair(char *qs, Dict *d);
static char *copy_str(char *start, char *end);
static void add_pair(Dict *d, char *key, char *value);
static void make_upper(char *str);
static char *strcp(char *str);

static char *blank = "";

/* builds a dictionary from a query string */
Dict *
get_query_dict(char *qs) {
	Dict *d;

	d = (Dict *) malloc(sizeof(Dict));
	if(d == NULL)
		return NULL;
	d->head = NULL;

	if(qs == NULL) return d;

	qs = parse_pair(qs, d);
	while(qs != NULL && *qs != '\0')
		qs = parse_pair(qs + 1, d);

	return d;
}

void
free_dict(Dict *d) {
	Pair *p = d->head, *pb;
	while(p != NULL) {
		pb = p;
		p = p->next;
		free(pb->key);
		if(pb->value != blank)
			free(pb->value);
		free(pb);
	}
	free(d);
}

char *
get_value(Dict *dictionary, char *key) {
	Pair *p = dictionary->head;
	char *mykey = strcp(key);
	if(mykey == NULL) return NULL;

	make_upper(mykey);

	for(; p != NULL; p = p->next) {
		if(strcmp(p->key, mykey) == 0) {
			free(mykey);
			return p->value;
		}
	}
	free(mykey);
	return NULL;
}

/* pulls off the first key/value pair from a query string */
/* adds the pair to the given dictionary */
/* returns character just after last character of value */
static char *
parse_pair(char *qs, Dict *d) {
	char *key, *next, *equals;
	key = next = equals = NULL;

	if(qs == NULL || *qs == '\0') return NULL;

	next = strchr(qs, '&');
	if(next == NULL) next = qs + strlen(qs);

	equals = strchr(qs, '=');
	if(equals == NULL || equals > next) {
		if(next != qs)
			add_pair(d, copy_str(qs, next), blank);
		return next;
	}

	add_pair(d, copy_str(qs, equals), copy_str(equals + 1, next));

	return next;
}

static void
add_pair(Dict *d, char *key, char *value) {
	Pair *p = (Pair *) malloc(sizeof(Pair));
	if(p == NULL) return; /* what can you do? */

	p->key = key;
	p->value = value;
	p->next = d->head;
	d->head = p;

	make_upper(p->key);
}

static char *
copy_str(char *start, char *end) {
	char *new = (char *) malloc(end - start + 1);
	char *cur = new;
	if(new == NULL) return NULL;
	while(start != end)
		*cur++ = *start++;
	*cur = '\0';
	return new;
}

static void
make_upper(char *str) {
	/* oh god such a hack */
	do {
		if(*str >= 'a' && *str <= 'z')
			*str += 'A' - 'a';
		str++;
	} while(*str != '\0');
}

static char *
strcp(char *str) {
	char *new = (char *) malloc(strlen(str) + 1);
	char *front = new;
	if(new == NULL) return NULL;
	while((*new++ = *str++) != '\0');
	return front;
}
