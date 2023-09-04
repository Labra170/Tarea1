#ifndef List_h
#define List_h

typedef struct List List;

List * createList(void); // Se crea lista

void * firstList(List * list); // Se apunta al inicio de la lista

void * nextList(List * list); // Se avanza en la lista

void * lastList(List * list); // Se apunta al final de la lista

void * prevList(List * list); // Se retrocede en la lista

void pushFront(List * list, void * data); // Se añade un nuevo nodo al inicio de la lista

void pushBack(List * list, void * data); // Se añade un nuevo nodo al final de la lista

void pushCurrent(List * list, void * data); // Se añade un nuevo nodo en la posición actual de la lista

void * popFront(List * list); // Se elimina el nodo al inicio de la lista

void * popBack(List * list); // Se elimina el nodo al final de la lista

void * popCurrent(List * list); // Se elimina el nodo actual de la lista

void cleanList(List * list); // Se libera la lista

#endif /* List_h */

