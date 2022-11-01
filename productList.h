typedef struct List List;
List* insertListNode(List* list, int key, char name[], float price, float qtt);
List* deleteListNode(List* list, int key);
void deleteList(List* list, Tree* root);
void printList(List* list);
void alfaSort(List* list);
int listSize(List* list);
