#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    struct Node{
        T dataValue; //Data we will store
        Node *next; //Pointer to next node
        Node(const T& the_data, Node* next_val = NULL) : dataValue(the_data) {next = next_val;}
    };

    Node* head;
    int num_items;
    T data;

public:

//--------------------------------Constructor/Destructor-------------------------------------
	LinkedList(void) {
        //cout << "Called constructor" << endl;

        head = NULL;
		num_items = 0;
    }
	~LinkedList(void) {
        //cout << "Called destructor" << endl;

        clear();
    }

//--------------------------------------Methods---------------------------------------------
	//Inserts node at head
    void insertHead(T value) {
        //cout << "Called insertHead" << endl;

        //Check for duplicates if list isn't empty
        if (num_items != 0) {
            if (alreadyInList(value)) { //My function - defined at end of .h file
                return;
            }
        }

        Node *newNode = new Node(value, NULL); //Create the node we will be inserting
        newNode->next = head;
        head = newNode;
        num_items++;
    }

    //Inserts node at end of list
	void insertTail(T value) {
        //cout << "Called insertTail" << endl;

        Node *ptr = head; //Start at head of the list

        if (ptr == NULL) { //Special case: if there is no head in the list yet
            insertHead(value);
            return;
        }

        //Check for duplicates
        if (alreadyInList(value)) {
            return;
        }

        ptr = head; //reset
        while (ptr != NULL) {
            if (ptr->next == NULL) {//Seek the end of the list
                ptr->next = new Node(value, NULL); 
                num_items++;
                return;
            }
            else {
                ptr = ptr->next;
            }
        }
    }

    //Inserts node after the node specified (second parameter)
	void insertAfter(T value, T insertionNode) {
        //cout << "Called insertAfter" << endl;

        Node *ptr = head; //Start at head of the list

        //Check for duplicates
        if (alreadyInList(value)) {
            return;
        }

        ptr = head; //reset
        Node *newNode = new Node(value, NULL); //Create the node we will be inserting
        
        //Traverse the list
        while (ptr != NULL) {
            if (ptr->dataValue == insertionNode) {

                newNode->next = ptr->next; //The newNode should point to the next item
                ptr->next = newNode; //The previous node should point to newNode
                num_items++;

                return;
            }
            else {
                ptr = ptr->next;
            }
        }

        //If we've reached this point and haven't used the new node, we need to delete it.
        delete newNode;
        return;
    }

    //Removes the node containing the given value
	void remove(T value) {
        //cout << "Called remove" << endl;

		Node *ptr = head; //Start at head of the list
        if (head == NULL) { //Don't remove anything if this is an empty list
            return;
        }

        if (ptr->dataValue == value) { //Special case if the value is located at the head of the list
            head = head->next;
			delete ptr;
            num_items--;
            return;
        } else {
            while (ptr->next != NULL) {
                if ((ptr->next)->dataValue == value) { //We want to stop at the node right before the one we will delete
                    Node *current = ptr->next; 
                    ptr->next = ptr->next->next;
		  			delete current;
		  			num_items--;
                    return;
                }
                else {
                    ptr = ptr->next;
                }
            }
            return;
        }

        return;
    }

    //Deletes all nodes in the list
	void clear() {
        //cout << "Called clear" << endl;

        for(int i = 0; i < num_items; i++) {
            Node *ptr = head;
            head = head->next;
            delete ptr;
		}

        num_items = 0;

        return;
    }

    //Returns the element at the given index
	T at(int index) {
        //cout << "Called at" << endl;

        if((index < 0) || (index >= num_items)) {
			throw std::out_of_range("At Error");
		} else {
			Node *ptr = head;
			for(int i = 0; i <= index; i++) {
		  		if(i == (index)) { 
		  			return(ptr->dataValue);
		  		}else {
		  			ptr = ptr->next;
		  		}
			}
		}

        return head->dataValue;
    }

    //Returns size
	int size() {
        //cout << "Called size" << endl;

        return num_items;
    }

    //Returns list items, separated by spaces, no trailing space
	string toString() {
        //cout << "Called toString" << endl;

        stringstream ss;
        for(Node *ptr = head; ptr != NULL; ptr = ptr->next){
			ss << ptr->dataValue;
            if (ptr->next != NULL) {
                ss << " ";
            }
		}

        string listString = ss.str();

        return listString;
    }

    bool alreadyInList(T value) {
        Node *ptr = head;
        while (ptr != NULL) {
            if (ptr->dataValue == value) {
                return true; //Yes, exists
            }
            else {
                ptr = ptr->next;
            }
        }

        return false; //No, we didn't find that value
    }

};
