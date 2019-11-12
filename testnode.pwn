Test:GetLast() {
    new Node:first = Node_New(1), Node:second = Node_New(2), Node:third = Node_New(3),Node:last = Node_New(4);

    Node_SetNext(first, second), Node_SetPrev(second, first);
    Node_SetNext(second, third), Node_SetPrev(third, second);
    Node_SetNext(third, last), Node_SetPrev(last, third);

    new count;
    new Node:node = Node_Last(first, count);

    ASSERT(node == last && count == 4);
}