/*
Name: Josh Holuboch
Student Number: 230153681
GitHub Repository: https://github.com/GoldenGoo/cpsc321-fall2025-assignment4-230153681

Objective:
• Model resource allocation with available, maximum, allocation, and need.
• Implement the Safety Algorithm to test whether a state is safe.
• Implement request/release operations that simulate changes and approve them only if the resulting state is safe.
• Build an interactive command loop and perform robust input validation

Instructions:
Write a program that implements the Banker's algorithm. Customers request and release
resources from the bank. The banker will grant a request only if it leaves the system in a safe state. A request that leaves the
system in an unsafe state will be denied.

Sample Input 1:
Enter number of customers (processes): 5
Enter number of resources: 3
Enter number of instances of each resource type (3 values): 10 5 7
Enter available resources (3 values): 3 3 2
Enter maximum demand matrix (3 x 3):
Customer 0: 7 5 3
Customer 1: 3 2 2
Customer 2: 9 0 2
Customer 3: 2 2 2
Customer 4: 4 3 3
Enter current allocation matrix (3 x 3):
Customer 0: 0 1 0
Customer 1: 2 0 0
Customer 2: 3 0 2
Customer 3: 2 1 1
Customer 4: 0 0 2
Enter Resource Request: 1 1 0 2
Sample Output 1:
State Safe
Safe sequence: C1 C3 C4 C0 C2
*/

#include <stdio.h>

// No longer use define, so I can actually dynamically assign to them
int NUMBER_OF_CUSTOMERS;
int NUMBER_OF_RESOURCES;

// Instead of defining arrays, which made no sense, I am defining pointers to arrays globally, which I will assign to later.
int *available;
int *total_instances; // Don't know why this was left out in the assingment description if the sample output asks for it.
int **maximum_demand;
int **allocation;
int **need;

int main() {
    printf("Enter number of customers (processes): ");
    scanf("%d", &NUMBER_OF_CUSTOMERS);
    
    printf("Enter number of resources: ");
    scanf("%d", &NUMBER_OF_RESOURCES);

    // Now I gotta do all the memory allocation.
    available= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
    total_instances= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
    maximum_demand= (int **)malloc(NUMBER_OF_CUSTOMERS * sizeof(int *));
    allocation= (int **)malloc(NUMBER_OF_CUSTOMERS * sizeof(int *));
    need= (int **)malloc(NUMBER_OF_CUSTOMERS * sizeof(int *));

    for(int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
        maximum_demand[i]= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
        allocation[i]= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
        need[i]= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
    }

    printf("Enter number of instances of each resource type (%d values): ", NUMBER_OF_RESOURCES);
    for(int i= 0; i<NUMBER_OF_RESOURCES; i++){
        scanf("%d", &total_instances[i]);
    }
    printf("Enter available resources (%d values): ", NUMBER_OF_RESOURCES);
    for(int i= 0; i<NUMBER_OF_RESOURCES; i++){
        scanf("%d", &available[i]);
    }


    // I'll also set up all the memory to be freed at the end of main
    for(int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
        free(maximum_demand[i]);
        free(allocation[i]);
        free(need[i]);
    }
    free(maximum_demand);
    free(allocation);
    free(need);
    free(total_instances);
    free(available);

    return 0;
}