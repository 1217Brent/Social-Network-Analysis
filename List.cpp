#include "List.h"
#include <stdexcept>
using namespace std;


//=============Constructors & Destructors============//

ListADT::List() { //creates new list
    frontDummy = new NodeObj();
    backDummy = new NodeObj();
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}
//change this to EverythingNode and add constraints
ListADT::ListADT(const ListADT& L) {
    List newList = newList(); // Creates a new List (object of ListADT) fix this this isn't right

    Node pointer = L.frontDummy->next;
    while (pointer != L.backDummy) {
        newList.insertAfter(pointer->data); // Inserts elements into the new list
        pointer = pointer->next;
    }

    newList.moveFront(); // Moves the cursor to the front of the new list
}

ListADT* ListADT::newList() {
    //calloc when allocates memory sets all bytes to 0 initially

    ListADT newList = new List();

    IDNode ID = new IDNodeObj();
    NameNode Name = new NameNodeObj();
    AgeNode Age = new AgeNodeObj();
    LocationNode Location = new LocationNodeObj();
    FriendsList Friendslist = new FriendsListNodeObj();
    InterestsList Interestslist = new InterestsListNodeObj();    
    
    ID->prev = nullptr;
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

    newList->frontDummy->next = ID; //we need to change pointer type of frontDummy -> NodeObj -> Node to return type IDNode
    newList->backDummy->prev = Interestslist; //maybe use dynamic_cast because the prev is a pointer to a node and we need it to be pointing to ListADT
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    return this;
}

//=================Access Functions==============//

int ListADT::length() const{ //const means a particular value that cannot be changed after initialization
    return this->num_elements;
}

int ListADT::front() const {
    if (this->num_elements == 0) {
        throw length_error("front() Error: empty list");
    }
    return this->frontDummy->next->id;
}

InterestsList ListADT::back() const {
    if (this->num_elements == 0) {
        throw length_error("back() Error: empty list");
    }
    return this->backDummy->prev->interests_list;
}

int ListADT::position() const {
    if (this->num_elements == 0) {
        throw length_error("position() Error: empty list");
    }
    return this->pos_cursor;
}

EverythingNode ListADT::peekNext() const {
    //lets first get a pointer that points to where afterCursor is pointing to then return that
    //but before that we need to include constraints
    if (this->afterCursor == nullptr) {
        std::cout << "position() Error: The pointer is nullptr." << std::endl;
    }
    if (this->position <= 0) {
       std::cout << "peekNext() Error: position is less or equal to 0" << std::endl; 
    }
    Node pointer = this->afterCursor;
    if (IDNode idnode = dynamic_cast<IDNodeObj*>(pointer)) {
        return idnode->id;
    }
    else if (NameNode namenode = dynamic_cast<NameNodeObj*>(pointer)) {
        return namenode->name;
    }
    else if (AgeNode agenode = dynamic_cast<AgeNodeObj*>(pointer)) {
        return agenode->age;
    }
    else if (LocationNode locationnode = dynamic_cast<LocationNodeObj*>(pointer)) {
        return locationnode->location;
    }
    else if (FriendsList friendslist = dynamic_cast<FriendsListNodeObj*>(pointer)) {
        return friendslist->friends_list
    }
    else if (InterestsList interestslist = dynamic_cast<InterestsListNodeObj*>(pointer)) {
        return interestslist->interests_list;
    }
    return -1; //if everything fails
}