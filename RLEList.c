#include "RLEList.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

#define NEWLINE "\n"

struct RLEList_t{
    char character;
    int occur;
    RLEList next;
    RLEList prev;
};

//implement the functions here

RLEList RLEListCreate(){
    RLEList ptr = malloc(sizeof(*ptr));

    if(!ptr)
    {
        return NULL;
    }

    ptr->character = '\0';
    ptr->occur = 0;
    ptr->next = NULL;
    ptr->prev = NULL;

    return ptr;
}

void RLEListDestroy(RLEList list){
    while(list){
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEList get_last_node(RLEList list){
    RLEList helper = list;
    while(helper->next != NULL){
        helper = helper->next;
    }
    return helper;
}

RLEListResult RLEListAppend(RLEList list, char value){
    if(!list || value == '\0'){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(list->character == '\0'){
        list->character = value;
        list->occur++;
        return RLE_LIST_SUCCESS;
    }

    RLEList last_node = get_last_node(list);

    if(last_node->character == value){
        last_node->occur++;
        return RLE_LIST_SUCCESS;
    }

    RLEList newList = RLEListCreate();
    if(!newList){
        return RLE_LIST_OUT_OF_MEMORY;
    }

    newList->character = value;
    newList->occur++;
    newList->prev = last_node;
    last_node->next = newList;
    return RLE_LIST_SUCCESS;
    }

int RLEListSize(RLEList list){
if(!list){
    return -1;
}
RLEList helper = list;
int size = 0;
while (helper)
{
    size += helper->occur;
    helper = helper->next;
}
free(helper);
return size;
}

void remove_node(RLEList node){
    RLEList toDelete = node;
    if(node->prev == NULL){
        node = node->next;
        return;
    }
    RLEList _next_node = node->next;
    RLEList _prev_node = node->prev;
    _next_node->prev = _prev_node;
    _prev_node->next = _next_node;
    free(toDelete);
    }

RLEList get_node(RLEList list, int index){
    assert(index >= 0);
    assert(index < RLEListSize(list));
    RLEList helper = list;
    int curr_size = helper->occur;
    while (index >= curr_size)
    {
        helper = helper->next;
        curr_size += helper->occur;
    }
    return helper;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(!list){
        assert(list);
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index > RLEListSize(list) || index < 0){ 
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList node = get_node(list, index);

    if(node->occur == 1){
        remove_node(node);
        return RLE_LIST_SUCCESS;
    }
    node->occur-=1;
    free(node);
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    
    int size = RLEListSize(list);
    if(index < 0 || index > size){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    RLEList node = get_node(list, index);
    assert(node);
    char ch = node->character;
    return ch;
}

int nodes_count(RLEList list){
    assert(list);
    int count = 0;
    RLEList helper = list;
    while(helper){
        count++;
        helper = helper->next;
    }
    free(helper);
    return count;
}

void give_init_val(char *s, int len)
{
    int i = 0;
    while(i < len)
    {
        s[i++] = '\0';
    }
}
char* RLEListExportToString(RLEList list, RLEListResult* result){
    int len = nodes_count(list);
    char *minimized = (char*)malloc((*minimized)*sizeof(char)*len*3);
    give_init_val(minimized, len);
    char _occur, _character;
    RLEList helper = list;
    while(helper != NULL){
        _character = (char)helper->character;
        _occur = helper->occur + '0';
        strcat(minimized, _character);
        strcat(minimized, _occur);
        //strcat(minimized, "\n");
        helper = helper->next;
    }
    return minimized;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList helper = list;
    char new_char;
    while(helper){
        new_char = map_function(helper->character);
        helper->character = new_char;
        helper = helper->next;
    }
    free(helper);
    return RLE_LIST_SUCCESS;
}

