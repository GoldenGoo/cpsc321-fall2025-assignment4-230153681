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

#define NUMBER_OF_CUSTOMERS
#define NUMBER_OF_RESOURCES
/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/*
The assignment description here:
The program dynamically takes input for the number of customers, number of resource types, available instances,
maximum demand, current allocation, and a new resource request. Each section of input represents a distinct part of the
Banker's Algorithm system model.
Completely doesn't work with the provided code above... I guess I am supposed to just redesign that? Weird.
*/



int main() {
    int num_resources;
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    return 0;
}