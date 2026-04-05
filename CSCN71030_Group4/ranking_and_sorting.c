#include "ranking_and_sorting.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node* deepCopyList(const Node* head) {
    if (!head) return NULL;
    Node* newHead = NULL;
    Node* newTail = NULL;
    const Node* cur = head;
    while (cur) {
        Node* n = (Node*)malloc(sizeof(Node));
        if (!n) {
            // allocation failure: free what we created
            Node* t = newHead;
            while (t) {
                Node* nxt = t->next;
                free(t);
                t = nxt;
            }
            return NULL;
        }
        // deep copy fields
        strncpy(n->name, cur->name, sizeof(n->name));
        n->name[sizeof(n->name)-1] = '\0';
        strncpy(n->category, cur->category ? cur->category : "", sizeof(n->category));
        n->category[sizeof(n->category)-1] = '\0';
        n->budget = cur->budget;
        n->next = NULL;

        if (!newHead) newHead = n;
        else newTail->next = n;
        newTail = n;

        cur = cur->next;
    }
    return newHead;
}

void splitIntoCategoryLists(const Node* head, Node** outOthersHead, Sushi** outSushiHead) {
    if (outOthersHead) *outOthersHead = NULL;
    if (outSushiHead) *outSushiHead = NULL;
    if (!head) return;

    Node* othersTail = NULL;
    Sushi* sushiTail = NULL;

    const Node* cur = head;
    while (cur) {
        if (cur->category && strcasecmp(cur->category, "sushi") == 0) {
            // add to sushi list (as Sushi node)
            Sushi* s = (Sushi*)malloc(sizeof(Sushi));
            if (!s) break; // stop on allocation failure
            strncpy(s->name, cur->name, sizeof(s->name));
            s->name[sizeof(s->name)-1] = '\0';
            s->budget = cur->budget;
            s->next = NULL;
            if (!(*outSushiHead)) *outSushiHead = s;
            else sushiTail->next = s;
            sushiTail = s;
        } else {
            // copy into Node list for others
            Node* n = (Node*)malloc(sizeof(Node));
            if (!n) break;
            strncpy(n->name, cur->name, sizeof(n->name));
            n->name[sizeof(n->name)-1] = '\0';
            strncpy(n->category, cur->category ? cur->category : "", sizeof(n->category));
            n->category[sizeof(n->category)-1] = '\0';
            n->budget = cur->budget;
            n->next = NULL;
            if (!(*outOthersHead)) *outOthersHead = n;
            else othersTail->next = n;
            othersTail = n;
        }
        cur = cur->next;
    }
}

// Simple utility functions for debugging - not part of the original header but useful.
void displayList(Node* head) {
    Node* cur = head;
    while (cur) {
        printf("Name: %s | Category: %s | Budget: %.2f\n", cur->name, cur->category, cur->budget);
        cur = cur->next;
    }
}

void displaySushiList(Sushi* head) {
    Sushi* cur = head;
    while (cur) {
        printf("Sushi Name: %s | Budget: %.2f\n", cur->name, cur->budget);
        cur = cur->next;
    }
}
