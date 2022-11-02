typedef struct List List;
List* insertListNode(List* list, int key, char name[], float price, float qtt);
List* deleteListNode(List* list, int key);
void deleteList(List* list);
void printList(List* list);
int printByPages(List* list, int page, char side);
void alfaSort(List* list);
int listSize(List* list);
float totalToPay(List* list);
