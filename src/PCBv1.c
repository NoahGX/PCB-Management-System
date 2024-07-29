#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

// Define Node structure for linked list
typedef struct Node {
    // PCB index of one child process
    int child;
    // Pointer to next node
    struct Node *nextNode;
} node_t;

// Define Process Control Block (PCB) structure
typedef struct PCB {
    // PCB index of process's creator
    int parent;
    // Pointer to linked list
    node_t *children;
} PCB;

// Define size of PCB_TABLE array
#define SIZE 1000
// Assume PCB[0] is initial process
PCB PCB_TABLE[SIZE] = {{-9999, NULL}};

// Function to create new child process [q] of [p]
void create(int p) {
    // Declare q
    int q;

    // Check if parameter is valid
    if (p < 0 || p >= SIZE) {
        printf("Error: Invalid parameter for PCB[%d].\n", p);
        exit(1);
    } else {
        // Allocate free PCB[q] by traversing array
        for (q = 1; q < SIZE; q++) {
            if (PCB_TABLE[q].parent == -2) {
                break;  // Stop after free PCB[q] index is found
            }
        }
        
        // Print error if no free PCB is found after list traversal
        if (q == SIZE) {
            printf("Error: No free PCB index was found.\n");
            exit(1);
        } else {
            // Else, record parent index [p] in PCB[q]
            PCB_TABLE[q].parent = p;
            // Initialize list of children of PCB[q] as empty
            PCB_TABLE[q].children = NULL;
        }
        
        // Create new link containing child index [q]
        node_t *childNode = (node_t*)malloc(sizeof(node_t));
        if (childNode == NULL) {
            printf("Error: Unable to allocate memory.\n");
            exit(1);
        } else {
            childNode->child = q;
            childNode->nextNode = NULL;
        }
        
        // Append link to linked list of PCB[p]
        node_t *current = PCB_TABLE[p].children;
        // If children list is empty, new node set as head
        if (current == NULL) {
            PCB_TABLE[p].children = childNode;
        } else {
            // Else, append to linked list
            while (current->nextNode != NULL) {
                current = current->nextNode;
            }
            current->nextNode = childNode;
        }
    }
}

// Function to recursively destroys all descendant processes
void destroy(int p) {
    // Check if parameter is valid
    if (p < 0 || p >= SIZE) {
        printf("Error: Invalid parameter for PCB[%d].\n", p);
        exit(1);
    } else {
        // Recursively destroy all progenies
        node_t *current = PCB_TABLE[p].children;
        while (current != NULL) {
            destroy(current->child);
            node_t *next = current->nextNode;
            free(current);  // deallocate element q from linked list
            current = next;
        }
        
        // Free PCB[q]
        int p_parent = PCB_TABLE[p].parent;
        if (p_parent != -2) {
            PCB_TABLE[p].parent = -2;
            PCB_TABLE[p].children = NULL;
        }
    }
}

// Print list based on parent index, handle empty list
void printList(int p) {
    // Check if parameter is valid
    if (p < 0 || p >= SIZE) {
        printf("Error: Invalid parameter for PCB[%d].\n", p);
        exit(1);
    } else {
        node_t *current = PCB_TABLE[p].children;
        printf("Children of process PCB[%d]: ", p);
        while (current != NULL) {
            printf("%d ", current->child);
            current = current->nextNode;
        }
    }
    printf("\n");
}

int main() {
    // Declare variables for time tracker
    double start, finish, elapsed;
    GET_TIME(start);
    
    // Confirm table elements are initialized
    for (int i = 1; i < SIZE; i++) {
        PCB_TABLE[i].parent = -2;
        PCB_TABLE[i].children = NULL;
    }

    // Create PCB child processes
    for (int i = 0; i < 100; i++) {
        create(0);  // creates child PCB[1] of PCB[0]
        create(0);  // creates child PCB[2] of PCB[0]
        create(1);  // creates child PCB[3] of PCB[1]
        create(2);  // creates child PCB[4] of PCB[2]
        create(1);  // creates child PCB[5] of PCB[1]
    }

    // Print PCB child processes
    printf("List1 before destroy(0): \n");
    printList(0);  // prints children of PCB[0]
    printList(1);  // prints children of PCB[1]
    printList(2);  // prints children of PCB[2]
    printf("\n");

    // Destroy child PCB processes
    destroy(0);  // destroys all children of PCB[0]

    // Print PCB child processes
    printf("List1 after destroy(0): \n");
    printList(0);  // prints children of PCB[0]
    printList(1);  // prints children of PCB[1]
    printList(2);  // prints children of PCB[2]

    // Print elapsed time
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds \n\n", elapsed);
    return 0;
}
