#include "list.h"

/* ---- PRIMITIVE ---- */

list emptyList() {

	return NULL;
}

Bool empty(list l) {

	if (l == NULL) {

		return true;
	}
	else {

		return false;
	}
}

element head(list l) {

	if (empty(l)) {

		exit(1);
	}
	else {

		return l->value;
	}
}

list tail(list l) {

	if (empty(l)) {

		exit(1);
	}
	else {

		return l->next;
	}
}

list cons(element e, list l) {

	list t;

	if ((t = (list)malloc(sizeof(node))) == NULL) {

		printf("Allocation Error!\n");
		exit(1);
	}

	t->value = e;
	t->next = l;

	return t;
}


/* ---- NON PRIMITIVE ---- */

int length(list l) {

	if (empty(l)) {

		return 0;
	}
	else {

		return 1 + length(tail(l));
	}
}

void freelist(list l) {

	if (empty(l)) {

		return;
	}
	else {

		freelist(tail(l));
		free(l);
	}
}