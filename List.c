#include "List.h"

typedef struct *NodeObj Node;

typedef struct NodeObj {
    int id;
    char *name;
    int age;
    char *location;
    List friends_list;
    List interests_list;
    Node next;
    Node prev;
}

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
}