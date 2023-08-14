#include "List.h"
#include <stdexcept>
using namespace std;


//=============Constructors & Destructors============//
ListADT::List() { //creates new list
    frontDummy = new frontDummyNodeObj;
    backDummy = new backDummyNodeObj;
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

ListADT ListADT::newList() {
    ListADT newList;

    IDNode ID = new IDNodeObj();
    NameNode Name = new NameNodeObj();
    AgeNode Age = new AgeNodeObj();
    LocationNode Location = new LocationNodeObj();
    FriendsList Friendslist = new FriendsListNodeObj();
    InterestsList Interestslist = new InterestsListNodeObj();

    // Connecting frontDummy to ID
    frontDummy->next = ID;
    ID->prev = frontDummy;

    // Connecting ID to Name
    ID->next = Name;
    Name->prev = ID;

    // Connecting Name to Age
    Name->next = Age;
    Age->prev = Name;

    // Connecting Age to Location
    Age->next = Location;
    Location->prev = Age;

    // Connecting Location to Friends
    Location->next = Friendslist;
    Friendslist->prev = Location;

    // Connecting Friends to Interests
    Friendslist->next = Interestslist;
    Interestslist->prev = Friendslist;

    // Connecting Interests to backDummy
    Interestslist->next = backDummy;
    backDummy->prev = Interestslist;

    // Set beforeCursor and afterCursor
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;

    return newList;
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
        std::cout << "peekNext() Error: The pointer is nullptr." << std::endl;
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

EverythingNode ListADT::peekPrev() const {
    //lets first get a pointer that points to where afterCursor is pointing to then return that
    //but before that we need to include constraints
    if (this->beforeCursor == nullptr) {
        std::cout << "peekPrev() Error: The pointer is nullptr." << std::endl;
    }
    if (this->position <= 0) {
       std::cout << "peekPrev() Error: position is less or equal to 0" << std::endl; 
    }
    Node pointer = this->beforeCursor;
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

void ListADT::clear() {
    this->moveFront();
    while(this->length > 0) {
        this->eraseAfter();
    }
}