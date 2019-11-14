
#define NODE_VAL_INDEX      (0)
#define NODE_PREV_INDEX     (1)
#define NODE_NEXT_INDEX     (2)

#define INVALID_NODE        (Node:-1)

stock Node:Node_New(value = 0, Node:prev = INVALID_NODE, Node:next = INVALID_NODE) {
    new Vec:node = Vec_New(3);
    if(node == INVALID_VECTOR_ID) {
        return INVALID_NODE;
    }
    Vec_ToggleFixedSize(node, true);

    Vec_SetValue(node, NODE_VAL_INDEX, value);
    Vec_SetValue(node, NODE_PREV_INDEX, _:prev);
    Vec_SetValue(node, NODE_NEXT_INDEX, _:next);

    return Node:node;
}

stock Node_SetNext(Node:node, Node:next) {
    return Vec_SetValue(Vec:node, NODE_NEXT_INDEX, _:next);
}

stock Node_SetPrev(Node:node, Node:prev) {
    return Vec_SetValue(Vec:node, NODE_PREV_INDEX, _:prev);
}

stock Node_SetVal(Node:node, value) {
    return Vec_SetValue(Vec:node, NODE_VAL_INDEX, value);
}

stock Node:Node_Next(Node:node) {
    return Node:Vec_GetValue(Vec:node, NODE_NEXT_INDEX);
}

stock Node:Node_Prev(Node:node) {
    return Node:Vec_GetValue(Vec:node, NODE_PREV_INDEX);
}

stock Node_Value(Node:node) {
    return Vec_GetValue(Vec:node, NODE_VAL_INDEX);
}

stock Node:Node_FindLast(Node:first, &count) {
    new Node:node = first, Node:next = Node_Next(first);
    count = 1;
    while(next != INVALID_NODE) {
        count++;
        next = Node_Next(next);
        node = Node_Next(node);
    }
    return node;
}

stock Node:Node_FindFirst(Node:last, &count) {
    new Node:node = last, Node:prev = Node_Prev(last);
    count = 1;
    while(prev != INVALID_NODE) {
        count++;
        prev = Node_Prev(prev);
        node = Node_Prev(node);
    }
    return node;
}

