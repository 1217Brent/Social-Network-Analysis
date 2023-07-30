#include "List.h"
#include <stdexcept>
using namespace std;

typedef struct *ListADT List;

//=============Constructors & Destructors============//

ListADT::List() { //creates new list
    frontDummy = new NodeObj();
    backDummy = new NodeObj();
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    position = 0;
    index = 0;
}

ListADT::ListADT(const ListADT& L) {
    List newList = List(); // Creates a new List (object of ListADT)

    Node pointer = L.frontDummy->next;
    while (pointer != L.backDummy) {
        newList.insertAfter(pointer->data); // Inserts elements into the new list
        pointer = pointer->next;
        moveNext(); //this should move the before and after cursors
    }

    newList.moveFront(); // Moves the cursor to the front of the new list
}

ListADT::newList() {
    //calloc when allocates memory sets all bytes to 0 initially

    List();

    IDNode ID = new IDNodeObj();
    NameNode Name = new NameNodeObj();
    AgeNode Age = new AgeNodeObj();
    LocationNode Location = new LocationNodeObj();
    FriendsList Friendslist = new FriendsListNodeObj();
    InterestsList Interestslist = new InterestsListNodeObj();    
    
    ID->prev = nullptr
    ID->next = Name;
    Name->prev = ID;
    //finished connecting ID and Name
    Name->next = Age;
    Age->prev = Name;
    //finished connecting Name to Age
    Age->next = Location;
    Location->prev = Age;
    //finished connecting Age to Location
    Location->next = Friendslist;
    FriendsList->prev = Location;
    //finished connecting Location to Friends
    Friendslist->next = Interestslist;
    Interestslist->prev = Friendslist;
    //finished connecting Friends to Interests
    Interestslist->next = nullptr;
    //we will use this function in a different function by calling then storing information one by one
    return this;
}