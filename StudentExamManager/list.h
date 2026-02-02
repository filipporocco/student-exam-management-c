#pragma once

#ifndef LIST_H
#define LIST_H

#include "element.h"

typedef struct list_element {

	element value;
	struct list_element* next;

} node;
typedef node* list;

/* ---- PRIMITIVE ---- */

list emptyList();
Bool empty(list l);
element head(list l);
list tail(list l);
list cons(element e, list l);


/* ---- NON PRIMITIVE ---- */

int length(list l);
void freelist(list l);

#endif