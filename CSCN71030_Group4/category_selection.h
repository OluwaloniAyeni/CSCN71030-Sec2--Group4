#include"ranking_and_sorting.h"
#pragma once
#ifndef CATEGORY_SELECTION_H
#define CATEGORY_SELECTION_H

void receiveData(Node* head) {
	// Function to receive data from the user and store it in the linked list
	// It allows the user to input the name and budget for each category, and then creates a new node with this information and adds it to the linked list
	// The function continues to receive data until the user indicates that they are finished, allowing for dynamic input of categories and budgets
}

Node* head searchCategory(Node* head, char* name) {
	// Function to search for a specific category in the linked list based on the name field
	// It traverses the linked list and compares the name of each node with the input name, returning the node if a match is found or indicating that the category was not found if no match is found
	// This function allows the user to quickly find and access information about a specific category in the linked list
	//this funtion passes node under one specific category to the recommendation system for further processing
	return category;
}

void addCategory(Node** head) {
	// Function to add a new category to the linked list, allowing the user to input the name and budget for the new category, and then insert it into the linked list in the correct position based on alphabetical order
	// It allows dynamic shrinking and expanding of the linked list as new categories are added or removed, and it ensures that the linked list remains sorted in alphabetical order after each insertion
}

void deleteCategory(Node** head) {
	// Function to delete a category from the linked list, allowing the user to input the name of the category to be deleted, and then remove it from the linked list while maintaining the sorted order
	// It allows dynamic shrinking and expanding of the linked list as new categories are added or removed, and it ensures that the linked list remains sorted in alphabetical order after each deletion
}

void displayCategories(Node* head) {
	// Function to display the contents of the linked list, showing the name and budget of each category in a formatted manner, allowing the user to easily view the current state of the linked list
	// It traverses the linked list and prints the name and budget of each category, providing a clear and organized display of the data stored in the linked list
}


