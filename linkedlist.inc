#if defined _inc_linkedlist
    #undef _inc_linkedlist
#endif

#if defined _linkedList_included
    #endinput
#endif

#define _linkedList_included

#include <a_samp>
#include <vector>
#include "listnode.inc"


#define LLIST_FIRST_INDEX   (0)
#define LLIST_LAST_INDEX    (1)
#define LLIST_COUNT_INDEX   (2)

#define INVALID_LINKEDLIST  (Llist:-1)

/*
    internal
*/

static stock Llist_SetCount(Llist:list, count) {
    return Vec_SetValue(Vec:list, LLIST_COUNT_INDEX, count);
}

static stock Llist_SetFirst(Llist:list, Node:node) {
    return Vec_SetValue(Vec:list, LLIST_FIRST_INDEX, _:node);
}

static stock Llist_SetLast(Llist:list, Node:node) {
    return Vec_SetValue(Vec:list, LLIST_LAST_INDEX, _:node);
}


/*
    api
*/

stock Llist:Llist_New(Node:first = INVALID_NODE) {
    new Vec:list = Vec_New(3), Node:last, count;
    if(list == INVALID_VECTOR_ID) {
        return INVALID_LINKEDLIST;
    }
    Vec_ToggleFixedSize(list, true);

    if(first != INVALID_NODE) {
        last = Node_FindLast(first, count);
    } else {
        last = INVALID_NODE;
    }

    Vec_SetValue(list, LLIST_FIRST_INDEX, _:first);
    Vec_SetValue(list, LLIST_LAST_INDEX, _:last);
    Vec_SetValue(list, LLIST_COUNT_INDEX, count);

    return Llist:list;
}

stock Llist:Llist_NewFromVector(Vec:vector) {
    new Llist:list = Llist_New();
    for(new  i = 0, j = Vec_GetLength(vector); i < j; i++) {
        Llist_AddLast(list, Vec_GetValue(vector, i));
    }
    return list;
}

stock Llist_Count(Llist:list) {
    return Vec_GetValue(Vec:list, LLIST_COUNT_INDEX);
}

stock Node:Llist_First(Llist:list) {
    return Node:Vec_GetValue(Vec:list, LLIST_FIRST_INDEX);
}

stock Node:Llist_Last(Llist:list) {
    return Node:Vec_GetValue(Vec:list, LLIST_LAST_INDEX);
}

stock Llist_AddNodeAfter(Llist:list, Node:node, Node:newNode) {
    new Node:next = Node_Next(node);

    Node_SetNext(node, newNode);
    Node_SetPrev(newNode, node);
    if(next != INVALID_NODE) {
        Node_SetPrev(next, newNode);
        Node_SetNext(newNode, next);
    } else {
        Llist_SetLast(list, newNode);
    }

    Llist_SetCount(list, Llist_Count(list)+1);
}

stock Llist_AddAfter(Llist:list, Node:node, value) {
    new Node:newNode = Node_New(value);

    if(newNode == INVALID_NODE) {
        return 1;
    }

    Llist_AddNodeAfter(list, node, newNode);
    return 0;
}

stock Llist_Remove(Llist:list, Node:node, bool:delete = true) {
    new Node:prev = Node_Prev(node), Node:next = Node_Next(node);

    if(prev != INVALID_NODE) {
        Node_SetNext(prev, next);
    } else {
        Llist_SetFirst(list, next);
    }

    if(next != INVALID_NODE) {
        Node_SetPrev(next, prev);
    } else {
        Llist_SetLast(list, node);
    }

    if(delete) {
        Vec_Delete(Vec:node);
    }

    Llist_SetCount(list, Llist_Count(list)-1);

}

stock Llist_RemoveFirst(Llist:list, bool:delete = true) {
    Llist_Remove(list, Llist_First(list), delete);
}

stock Llist_RemoveLast(Llist:list, bool:delete = true) {
    Llist_Remove(list, Llist_Last(list), delete);
}

stock Llist_RemoveValue(Llist:list, value) {
    new Node:node = Llist_First(list);

    while(node != INVALID_NODE) {
        if(Node_Value(node) == value) {
            Llist_Remove(list, node);
            return 0;
        }
        node = Node_Next(node);
    }
    return 0;
}

stock Llist_AddNodeBefore(Llist:list, Node:node, Node:newNode) {
    new Node:prev = Node_Prev(node);

    Node_SetPrev(node, newNode);
    Node_SetNext(newNode, node);
    if(prev != INVALID_NODE) {
        Node_SetNext(prev, newNode);
        Node_SetPrev(newNode, prev);
    } else {
        Llist_SetFirst(list, newNode);
    }

    Llist_SetCount(list, Llist_Count(list)+1);
}

stock Llist_AddBefore(Llist:list, Node:node, value) {
    new Node:newNode = Node_New(value);

    if(newNode == INVALID_NODE) {
        return 1;
    }

    Llist_AddNodeBefore(list, node, newNode);
    return 0;
}

stock Llist_AddNodeFirst(Llist:list, Node:node) {
    new Node:first = Llist_First(list);

    Node_SetPrev(first, node);
    Node_SetPrev(node, INVALID_NODE);
    Node_SetNext(node, first);
    Llist_SetFirst(list, node);
    new count = Llist_Count(list);
    if(count == 0) {
        Llist_SetLast(list,node);
    }
    Llist_SetCount(list, count+1);
}

stock Llist_AddFirst(Llist:list, value) {
    new Node:node = Node_New(value);
    if(node == INVALID_NODE) {
        return 1;
    }

    Llist_AddNodeFirst(list, node);
    return 0;
}

stock Llist_AddNodeLast(Llist:list, Node:node) {
    new Node:last = Llist_Last(list);

    Node_SetPrev(node, last);
    Node_SetNext(last, node);
    Node_SetNext(node, INVALID_NODE);
    Llist_SetLast(list, node);
    new count = Llist_Count(list);
    if(count == 0) {
        Llist_SetFirst(list,node);
    }
    Llist_SetCount(list, count+1);
}

stock Llist_AddLast(Llist:list, value) {
    new Node:node = Node_New(value);
    if(node == INVALID_NODE) {
        return 1;
    }

    Llist_AddNodeLast(list, node);
    return 0;
}

stock Llist_Clear(Llist:list, bool:delete = true) {
    if(delete) {
        new Node:node = Llist_First(list), Node:lastNode;

        while(node != INVALID_NODE) {
            lastNode = node;
            node = Node_Next(node);
            Vec_Delete(Vec:lastNode);
        }
    }

    Llist_SetCount(list, 0);
    Llist_SetFirst(list, INVALID_NODE);
    Llist_SetLast(list, INVALID_NODE);
}

stock bool:Llist_Contains(Llist:list, value) {
    new Node:node = Llist_First(list);

    while(node != INVALID_NODE) {
        if(Node_Value(node) == value) {
            return true;
        }
        node = Node_Next(node);
    }
    return false;
}

stock Node:Llist_Find(Llist:list, value) {
    new Node:node = Llist_First(list);

    while(node != INVALID_NODE) {
        if(Node_Value(node) == value) {
            return node;
        }
        node = Node_Next(node);
    }
    return INVALID_NODE;
}

stock Vec:Llist_ToVector(Llist:list) {
    new Node:node = Llist_First(list), Vec:vector = Vec_New(Llist_Count(list));
    while(node != INVALID_NODE) {
        Vec_Append(vector, Node_Value(node));
        node = Node_Next(node);
    }
    return vector;
}

stock Node:Llist_FindLast(Llist:list, value) {
    new Node:node = Llist_Last(list);

    while(node != INVALID_NODE) {
        if(Node_Value(node) == value) {
            return node;
        }
        node = Node_Prev(node);
    }
    return INVALID_NODE;
}

stock Node:Llist_Delete(Llist:list, bool:delete = true) {
    if(!delete) {
        new Node:first = Llist_First(list);
        Vec_Delete(Vec:list);
        return first;
    }
    Llist_Clear(list);
    Vec_Delete(Vec:list);
    return INVALID_NODE;
}