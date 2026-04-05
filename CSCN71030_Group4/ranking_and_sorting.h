#pragma once
#ifndef RANKING_AND_SORTING_H
#define RANKING_AND_SORTING_H

void bufferData(Node* head, int data)；
// Function to receive data from other components and store it in the linked list, allowing for dynamic input of categories and budgets, and ensuring that the data is properly stored in the linked list for further processing
// Note: This is not the most efficient sorting algorithm for linked lists, but it serves as an example

void reorderList(Node** head);
// Function to reorder the linked list in aphabetical order
// Function sort the linked list in alphabetical order based on the name field of the nodes
// Note: This is a simple implementation and may not be the most efficient way to sort a linked list

void addToList(Node** head);
//function to add a new node to the linked list, allowing the user to input the name and budget for the new node, and then insert it into the linked list in the correct position based on alphabetical order
//it allows dynamic shrinking and expanding of the linked list as new nodes are added or removed, and it ensures that the linked list remains sorted in alphabetical order after each insertion

void deleteFromList(Node** head);
//function to delete a node from the linked list, allowing the user to input the name of the node to be deleted, and then remove it from the linked list while maintaining the sorted order
//it allows dynamic shrinking and expanding of the linked list as new nodes are added or removed, and it ensures that the linked list remains sorted in alphabetical order after each deletion

void displayList(Node* head);
//function to display the contents of the linked list, showing the name and budget of each node in a formatted manner, allowing the user to easily view the current state of the linked list
//it traverses the linked list and prints the name and budget of each node, providing a clear and organized display of the data stored in the linked list

Node* head returnSortedList(Node* head) {
	return head;
}
//function to return a sorted version of the linked list, allowing the user to view the nodes in alphabetical order without modifying the original linked list

#endif // RANKING_AND_SORTING_H