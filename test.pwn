#define RUN_TESTS
#define YSI_NO_HEAP_MALLOC
#include <a_samp>
#include "linkedlist.inc"
#include <YSI_Core\y_testing>
#include "testnode.pwn"

Test:New() {
    new Llist:list = Llist_New();
    ASSERT(Vec_IsValid(Vec:list));
    ASSERT(Llist_First(list) == INVALID_NODE);
    ASSERT(Llist_Last(list) == INVALID_NODE);
    ASSERT(Llist_Count(list) == 0);
    Llist_Delete(list);
}

Test:AddNodeFirst() {
    new Llist:list = Llist_New();
    new Node:node1 = Node_New(1);
    Llist_AddNodeFirst(list, node1);
    ASSERT(Llist_First(list) == node1 && Llist_Count(list) == 1);
    new Node:node2 = Node_New(1);
    Llist_AddNodeFirst(list, node2);
    ASSERT(Llist_Last(list) == node1 && Llist_First(list) == node2 && Llist_Count(list) == 2);

    Llist_Delete(list);
}

Test:AddNodeLast() {
    new Llist:list = Llist_New();
    new Node:node1 = Node_New(1);
    Llist_AddNodeLast(list, node1);
    ASSERT(Llist_Last(list) == node1 && Llist_Count(list) == 1);
    new Node:node2 = Node_New(1);
    Llist_AddNodeLast(list, node2);
    ASSERT(Llist_First(list) == node1 && Llist_Last(list) == node2 && Llist_Count(list) == 2);
    Llist_Delete(list);
}

Test:NewFromVector() {
    new Vec:vector = Vec_NewFromArray({1, 2, 3, 4, 5});
    new Llist:list = Llist_NewFromVector(vector);
    ASSERT(Llist_Count(list) == Vec_GetLength(vector));
    new Node:node = Llist_First(list), bool:pass = true, i = 0;
    while(node != INVALID_NODE) {
        if(Node_Value(node) != Vec_GetValue(vector, i)) {
            pass = false;
        }
        node = Node_Next(node);
        i++;
    }
    ASSERT(pass);
    Vec_Delete(vector);
    Llist_Delete(list);
}

Test:NewFromNodeChain() {
    new Node:nodes[4];
    nodes[0] = Node_New(1), nodes[1] = Node_New(2), nodes[2] = Node_New(3), nodes[3] = Node_New(4);
    Node_SetNext(nodes[0], nodes[1]), Node_SetPrev(nodes[1], nodes[0]);
    Node_SetNext(nodes[1], nodes[2]), Node_SetPrev(nodes[2], nodes[1]);
    Node_SetNext(nodes[2], nodes[3]), Node_SetPrev(nodes[3], nodes[2]);

    new Llist:list = Llist_New(nodes[0]), bool:pass = true, i = 0, Node:node;
    ASSERT(Llist_Count(list) == 4);
    node = Llist_First(list);

    while(node != INVALID_NODE) {
        if(node != nodes[i]) {
            pass = false;
        }
        i++;
        node = Node_Next(node);
    }

    ASSERT(pass);
    Llist_Delete(list);
}

Test:AddNodeAfter() {
    new Node:nodes[5];
    nodes[0] = Node_New(1), nodes[1] = Node_New(2), nodes[2] = Node_New(3), nodes[4] = Node_New(4);
    Node_SetNext(nodes[0], nodes[1]), Node_SetPrev(nodes[1], nodes[0]);
    Node_SetNext(nodes[1], nodes[2]), Node_SetPrev(nodes[2], nodes[1]);
    Node_SetNext(nodes[2], nodes[4]), Node_SetPrev(nodes[4], nodes[2]);

    new Llist:list = Llist_New(nodes[0]), bool:pass = true, i = 0, Node:node;
    nodes[3] = Node_New(5);
    Llist_AddNodeAfter(list, nodes[2], nodes[3]);

    node = Llist_First(list);
    while(node != INVALID_NODE) {
        if(node != nodes[i]) {
            pass = false;
        }
        i++;
        node = Node_Next(node);
    }
    ASSERT(pass);
    Llist_Delete(list);
}

Test:AddNodeBefore() {
    new Node:nodes[5];
    nodes[0] = Node_New(1), nodes[1] = Node_New(2), nodes[2] = Node_New(3), nodes[4] = Node_New(4);
    Node_SetNext(nodes[0], nodes[1]), Node_SetPrev(nodes[1], nodes[0]);
    Node_SetNext(nodes[1], nodes[2]), Node_SetPrev(nodes[2], nodes[1]);
    Node_SetNext(nodes[2], nodes[4]), Node_SetPrev(nodes[4], nodes[2]);

    new Llist:list = Llist_New(nodes[0]), bool:pass = true, i = 0, Node:node;
    nodes[3] = Node_New(5);
    Llist_AddNodeBefore(list, nodes[4], nodes[3]);

    node = Llist_First(list);
    while(node != INVALID_NODE) {
        if(node != nodes[i]) {
            pass = false;
        }
        i++;
        node = Node_Next(node);
    }
    ASSERT(pass);
    Llist_Delete(list);
}

Test:Remove() {
    new Node:nodes[3];
    new Node:toRemove = Node_New(3);
    nodes[0] = Node_New(1), nodes[1] = Node_New(2), nodes[2] = Node_New(4);
    Node_SetNext(nodes[0], nodes[1]), Node_SetPrev(nodes[1], nodes[0]);
    Node_SetNext(nodes[1], toRemove), Node_SetPrev(toRemove, nodes[1]);
    Node_SetNext(toRemove, nodes[2]), Node_SetPrev(nodes[2], toRemove);

    new Llist:list = Llist_New(nodes[0]), bool:pass = true, i = 0, Node:node;
    Llist_Remove(list, toRemove);

    node = Llist_First(list);
    while(node != INVALID_NODE) {
        if(node != nodes[i]) {
            pass = false;
        }
        i++;
        node = Node_Next(node);
    }
    ASSERT(pass);
    Llist_Delete(list);
}

Test:RemoveValue() {
    new Node:nodes[3];
    new Node:toRemove = Node_New(3);
    nodes[0] = Node_New(1), nodes[1] = Node_New(2), nodes[2] = Node_New(4);
    Node_SetNext(nodes[0], nodes[1]), Node_SetPrev(nodes[1], nodes[0]);
    Node_SetNext(nodes[1], toRemove), Node_SetPrev(toRemove, nodes[1]);
    Node_SetNext(toRemove, nodes[2]), Node_SetPrev(nodes[2], toRemove);

    new Llist:list = Llist_New(nodes[0]), bool:pass = true, i = 0, Node:node;
    Llist_RemoveValue(list, 3);

    node = Llist_First(list);
    while(node != INVALID_NODE) {
        if(node != nodes[i]) {
            pass = false;
        }
        i++;
        node = Node_Next(node);
    }
    ASSERT(pass);
    Llist_Delete(list);
}

Test:Contains() {
    new Vec:vector = Vec_NewFromArray({1, 2, 3, 4, 5});
    new Llist:list = Llist_NewFromVector(vector);

    ASSERT(Llist_Contains(list, 3) && Llist_Contains(list, 1) && Llist_Contains(list, 5));
    ASSERT(!Llist_Contains(list, 10));

    Vec_Delete(vector);
    Llist_Delete(list);
}

Test:Find() {
    new Node:nodes[4];
    nodes[0] = Node_New(1), nodes[1] = Node_New(2), nodes[2] = Node_New(3), nodes[3] = Node_New(4);
    Node_SetNext(nodes[0], nodes[1]), Node_SetPrev(nodes[1], nodes[0]);
    Node_SetNext(nodes[1], nodes[2]), Node_SetPrev(nodes[2], nodes[1]);
    Node_SetNext(nodes[2], nodes[3]), Node_SetPrev(nodes[3], nodes[2]);

    new Llist:list = Llist_New(nodes[0]);

    ASSERT(Llist_Find(list, 3) == nodes[2]);

    Llist_Delete(list);
}