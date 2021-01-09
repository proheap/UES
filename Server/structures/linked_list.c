#include "linked_list.h"

void llInit(LINKED_LIST *list){
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}

void llDispose(LINKED_LIST *list) {
    ITEM* curStart = list->first;
    ITEM* curEnd = list->last;

    while (list->size != 0) {
        curStart = curStart->next;
        itemDeleteData(list->first);
        list->first->prev = NULL;
        list->first->next = NULL;
        free(list->first);
        if (list->size != 1) {
            list->first = curStart;
        }
        list->size--;

        if (list->first != list->last) {
            curEnd = curEnd->prev;
            itemDeleteData(list->last);
            list->last->next = NULL;
            list->last->prev = NULL;
            free(list->last);
            list->last = curEnd;
            list->size--;
        }
    }

    list->first = NULL;
    list->last = NULL;
}

void llPrint(const LINKED_LIST *list) {
    ITEM* cur = list->first;
    while (cur != NULL)
    {
        itemPrint(cur);
        cur = cur->next;
    }
    printf("\n");
}

void llAdd(LINKED_LIST *list, const void* data, const enum type_tag type) {
    ITEM* newItem = malloc(sizeof(ITEM));
    newItem->type = type;

    itemAddData(newItem, data);

    newItem->next = NULL;
    if (list->first == NULL) {
        newItem->prev = NULL;
        list->first = newItem;
    } else {
        newItem->prev = list->last;
        list->last->next = newItem;
    }
    list->last = newItem;
    list->size++;
}

static ITEM* getItemAtIndex(const LINKED_LIST *list, const int index) {
    ITEM* curStart = list->first;
    ITEM* curEnd = list->last;

    int curStartIndex = 0;
    int curEndIndex = list->size - 1;

    while (curStartIndex != index && curEndIndex != index) {
        curStart = curStart->next;
        curEnd = curEnd->prev;
        curStartIndex++;
        curEndIndex--;
    }

    if (curStartIndex == index) {
        return curStart;
    } else {
        return curEnd;
    }
}

_Bool llTryInsert(LINKED_LIST *list, const void *data, const enum type_tag type, const int pos) {
    if (pos < 0 || pos > list->size) {
        return false;
    } else if (pos == list->size) {
        llAdd(list, data, type);
        return true;
    } else{
        ITEM* newItem = calloc(1, sizeof(ITEM));
        newItem->type = type;
        itemAddData(newItem, data);
        if (pos == 0) {
            newItem->next = list->first;
            newItem->prev = NULL;
            list->first = newItem;
        } else {
            ITEM* prevItem = getItemAtIndex(list, pos - 1);
            prevItem->next->prev = newItem;
            newItem->next = prevItem->next;
            newItem->prev = prevItem;
            prevItem->next = newItem;
        }
        list->size++;
        return true;
    }
}

_Bool llTrySet(LINKED_LIST *list, const int pos, const void *data) {
    if (pos >= 0 && pos < list->size) {
        ITEM* item = getItemAtIndex(list, pos);
        itemSetData(item->data, data, item->type);
        return true;
    } else {
        return false;
    }
}

_Bool llTryGet(const LINKED_LIST *list, const int pos, void **data) {
    if (pos >= 0 && pos < list->size) {
        ITEM* item = getItemAtIndex(list, pos);
        itemGetData(item, data);
        return true;
    } else {
        return false;
    }
}

_Bool llTrySwap(LINKED_LIST *list, int posItem1, int posItem2) {
    if (posItem1 < 0 && posItem1 >= list->size && posItem2 < 0 && posItem2 >= list->size && posItem1 == posItem2) {
        return false;
    }

    ITEM* item1 = getItemAtIndex(list, posItem1);
    ITEM* item2 = getItemAtIndex(list, posItem2);
    if (posItem1 > posItem2) {
        ITEM* tmpItem = item1;
        item1 = item2;
        item2 = tmpItem;
    }
    ITEM* prevItem1 = item1->prev;
    ITEM* nextItem1 = item1->next;
    ITEM* prevItem2 = item2->prev;
    ITEM* nextItem2 = item2->next;

    if (item1 == list->first) {
        list->first = item2;
    }
    if (item2 == list->last) {
        list->last = item1;
    }

    if (prevItem1 != NULL) {
        prevItem1->next = item2;
    }
    if (nextItem1 != NULL) {
        nextItem1->prev = item2;
    }
    if (prevItem2 != NULL) {
        prevItem2->next = item1;
    }
    if (nextItem2 != NULL) {
        nextItem2->prev = item1;
    }
    if (item1 == prevItem2) {
        item1->prev = item2;
        item2->next = item1;
    } else {
        item1->prev = prevItem2;
        item2->next = nextItem1;
    }
    item1->next = nextItem2;
    item2->prev = prevItem1;

    return true;
}

bool llTryRemove(LINKED_LIST *list, const int pos) {
    if (pos < 0 || pos >= list->size) {
        return false;
    } else {
        ITEM *delItem;
        if (pos == 0) {
            delItem = list->first;
            if (list->size != 1) {
                list->first = delItem->next;
                list->first->prev = NULL;
            } else {
                list->first = NULL;
                list->last = NULL;
            }
        } else {
            ITEM *prevItem = getItemAtIndex(list, pos - 1);
            delItem = prevItem->next;
            prevItem->next = delItem->next;
            delItem->next->prev = prevItem;
            if (delItem == list->last) {
                list->last = prevItem;
            }
        }
        itemDeleteData(delItem);
        free(delItem);
        delItem = NULL;
        list->size--;
        return true;
    }
}

_Bool llTryCopy(const LINKED_LIST *src, LINKED_LIST *dest) {
    if (dest->size > 0) {
        return false;
    } else {
        llInit(dest);
        dest->size = 0;
        ITEM* curStart = src->first;
        ITEM* curEnd = src->last;
        ITEM* prevStart;
        ITEM* prevEnd;
        while (dest->size != src->size) {
            ITEM* newStartItem = calloc(1, sizeof(ITEM));
            ITEM* newEndItem = calloc(1, sizeof(ITEM));
            if (curStart == src->first || curEnd == src->last) {
                dest->first = newStartItem;
                itemCopy(src->first, newStartItem, src->first->type);
                newStartItem->data = src->first->data;
                newStartItem->prev = NULL;
                prevStart = newStartItem;

                dest->last = newEndItem;
                itemCopy(src->last, newEndItem, src->last->type);
                newEndItem->data = src->last->data;
                newEndItem->next = NULL;
                prevEnd = newEndItem;
            } else {
                if (curStart == curEnd) {
                    itemCopy(src->first, newStartItem, src->first->type);
                    newStartItem->prev = prevStart;
                    prevStart->next = newStartItem;
                    prevStart = prevStart->next;
                    dest->size++;
                    break;
                }
                itemCopy(curStart, newStartItem, curStart->type);
                newStartItem->data = curStart->data;
                newStartItem->prev = prevStart;
                prevStart->next = newStartItem;

                itemCopy(curEnd, newEndItem, curEnd->type);
                newEndItem->data = curEnd->data;
                newEndItem->next = prevEnd;
                prevEnd->prev = newEndItem;

                prevStart = prevStart->next;
                prevEnd = prevEnd->prev;
            }
            curStart = curStart->next;
            curEnd = curEnd->prev;
            dest->size += 2;
        }
        prevStart->next = prevEnd;
        prevEnd->prev = prevStart;
        return true;
    }
}

void llReadFromTxt(LINKED_LIST *list, FILE *txtFile) {
    if (txtFile == NULL) {
        return;
    }

    llInit(list);

#define BUF_SIZE 100
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, txtFile) != NULL) {
        enum type_tag type;
        sscanf(buf, "%d", &type);
        char* pType = strchr(buf, ':');
        pType++;
        char* pData = strchr(pType, '\n');
        void* data;
        switch (type) {
            case INT_TYPE:
                sscanf(pType, "%d", (int*)data);
                break;
            case DOUBLE_TYPE:
                sscanf(pType, "%lf", (double*)data);
                break;
            case STRING_TYPE:
                sscanf(pType,"%[^\n]", (char*)data);
                break;
            case BOOL_TYPE:
                sscanf(pType, "%d", (_Bool*)data);
                break;
        }
        llAdd(list, data, type);
    }

    fclose(txtFile);
#undef BUF_SIZE
}

void llWriteToTxt(const LINKED_LIST *list, FILE *txtFile) {
    if (txtFile == NULL) {
        return;
    }

    ITEM* cur = list->first;
    while (cur != NULL) {
        itemFilePrint(cur, txtFile);
        cur = cur->next;
    }

    fclose(txtFile);
}
