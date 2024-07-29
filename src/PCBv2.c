#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

// Define Process Control Block (PCB) structure
typedef struct PCB {
    int parent;
    int first_child;
    int younger_sibling;
    int older_sibling;
} PCB;

// Define size of PCB_TABLE array
#define SIZE 1000
// Assume PCB[0] is initial process
PCB PCB_TABLE[SIZE];

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
            PCB_TABLE[q].first_child = -2;
            PCB_TABLE[q].younger_sibling = -2;
            PCB_TABLE[q].older_sibling = -2;
        }
        
        // If first child is empty, set [q] as first child
        int current = PCB_TABLE[p].first_child;
        if (current == -2) {
            PCB_TABLE[p].first_child = q;
        } else {
            // Else, add [q] to end of children
            while (PCB_TABLE[current].younger_sibling != -2) {
                current = PCB_TABLE[current].younger_sibling;
            }
            // Connect children as siblings
            PCB_TABLE[current].younger_sibling = q;
            PCB_TABLE[q].older_sibling = current;
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
        // Else, recursively destroy all progenies
        int current = PCB_TABLE[p].first_child;
        while (current != -2) {
            int next = PCB_TABLE[current].younger_sibling;
            destroy(current);
            current = next;
        }
        // Free PCB[q]
        int p_parent = PCB_TABLE[p].parent;
        int p_young_sib = PCB_TABLE[p].younger_sibling;
        if (p_parent != -2) {
            PCB_TABLE[p_parent].first_child = p_young_sib;
            if (p_young_sib != -2) {
                PCB_TABLE[p_young_sib].older_sibling = -2;
            }
            PCB_TABLE[p].parent = -2;
            PCB_TABLE[p].first_child = -2;
            PCB_TABLE[p].younger_sibling = -2;
            PCB_TABLE[p].older_sibling = -2;
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
        int current = PCB_TABLE[p].first_child;
        printf("Children of process PCB[%d]: ", p);
        while (current != -2) {
            printf("%d ", current);
            current = PCB_TABLE[current].younger_sibling;
        }
    }
    printf("\n");
}

int main() {
    // Declare variables for time tracker
    double start, finish, elapsed;
    GET_TIME(start);

    // Confirm table elements are initialized
    for (int i = 0; i < SIZE; i++) {
        PCB_TABLE[i].parent = -2;
        PCB_TABLE[i].first_child = -2;
        PCB_TABLE[i].younger_sibling = -2;
        PCB_TABLE[i].older_sibling = -2;
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
    printf("List2 before destroy(0): \n");
    printList(0);  // prints children of PCB[0]
    printList(1);  // prints children of PCB[1]
    printList(2);  // prints children of PCB[2]
    printf("\n");

    // Destroy child PCB processes
    destroy(0);  // destroys all children of PCB[0]

    // Print PCB child processes
    printf("List2 after destroy(0): \n");
    printList(0);  // prints children of PCB[0]
    printList(1);  // prints children of PCB[1]
    printList(2);  // prints children of PCB[2]

    // Print elapsed time
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds \n\n", elapsed);
    return 0;
}