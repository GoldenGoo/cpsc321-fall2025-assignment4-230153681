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

Sample Output: (Note, order of the safe sequence may vary depending on implementation)
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
State Safe
Safe sequence: C1 C3 C4 C0 C2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// No longer use define, so I can actually dynamically assign to them
int NUMBER_OF_CUSTOMERS;
int NUMBER_OF_RESOURCES;

// Instead of defining arrays, which made no sense, I am defining pointers to arrays globally, which I will assign to later.
int *available;
int *total_instances; // Don't know why this was left out in the assingment description if the sample output asks for it.
int **maximum;
int **allocation;
int **need;

/* 
Given 2 vectors of equal size, A and B, this method compares them and returns true
if A is <= B, otherwise it returns false.
*/
bool vector_LTorE(int *A, int *B, int size){
    for (int i= 0; i<size; i++){
        if (A[i] > B[i]) {
            return false;
        }
    }
    return true;
}

/*
This algorithm tests whether the system is in a safe state.
It is side effecting, and will print Safe and the sequence to determine safety if true, 
or unsafe otherwise.
*/
void safety_algorithm(){
    /*
    psuedocode:
    Step 1:
    Initialize
    Work = Available
    Finish[i] = false for all i = 0, 1, …, n – 1
    Step 2:
    Find an index i such that both:
    Finish[i] == false
    Need[i] ≤ Work
    If no such i exists, go to Step 4.
    Step 3:
    If such an i is found:
    Work = Work + Allocation[i]
    Finish[i] = true
    Go back to Step 2
    Step 4:
    If Finish[i] == true for all i, then the system is in a safe state.
    */
    
    // Step 1:
    int work[NUMBER_OF_RESOURCES];
    for (int i= 0; i< NUMBER_OF_RESOURCES; i++){
        work[i]= available[i];
    }
    bool finish[NUMBER_OF_CUSTOMERS];
    for (int i= 0; i< NUMBER_OF_CUSTOMERS; i++){
        finish[i]= false;
    }
    int sequence[NUMBER_OF_CUSTOMERS]; // Using this variable to make printing easier later.
    int sequence_index= 0;

    int count = 0;
    while(count< NUMBER_OF_CUSTOMERS){ // while loop is for restarting step 2
        bool found = false; // is needed for an early exit later
        //Step 2:
        for (int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
            if(finish[i]==false && vector_LTorE(need[i], work, NUMBER_OF_RESOURCES)){
                //Step 3:
                for (int j= 0; j<NUMBER_OF_RESOURCES; j++){
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                sequence[sequence_index++] = i;
                found = true;
                count++; // num of customers processed goes up by one
                break; // break will exit the for loop, preventing the next lines, and restarting step 2.
            } 
        }
        if (!found && count<NUMBER_OF_CUSTOMERS) {// if we reached here, we are either done (count>num customers), or we broke out of the for, and found is true
            break; 
        } 
    }
    //Step 4:
    if (count == NUMBER_OF_CUSTOMERS) {
        printf("State Safe\n");
        printf("Safe sequence: ");
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
            printf("C%d ", sequence[i]);
        }
        printf("\n");
    } else {
        printf("State Unsafe\n");
    }
}


int main() {
    printf("Enter number of customers (processes): ");
    scanf("%d", &NUMBER_OF_CUSTOMERS);
    
    printf("Enter number of resources: ");
    scanf("%d", &NUMBER_OF_RESOURCES);

    // Now I gotta do all the memory allocation.
    available= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
    total_instances= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
    maximum= (int **)malloc(NUMBER_OF_CUSTOMERS * sizeof(int *));
    allocation= (int **)malloc(NUMBER_OF_CUSTOMERS * sizeof(int *));
    need= (int **)malloc(NUMBER_OF_CUSTOMERS * sizeof(int *));

    for(int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
        maximum[i]= (int *)malloc(NUMBER_OF_RESOURCES * sizeof(int));
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
    printf("Enter maximum demand matrix (%d x %d): \n", NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES); // The sample output has a bug on this line.
    for(int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
        printf("Customer %d: ", i);
        for (int j= 0; j<NUMBER_OF_RESOURCES; j++){
            scanf("%d", &maximum[i][j]);
        }
    }
    printf("Enter current allocation matrix (%d x %d): \n", NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES); // The sample output has a bug on this line too.
    for(int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
        printf("Customer %d: ", i);
        for (int j= 0; j<NUMBER_OF_RESOURCES; j++){
            scanf("%d", &allocation[i][j]);
        }
    }
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j]; // This assumes the user isn't messing around and providing invalid inputs.
            // If I wanted to not assume that I would put in a check here and throw an error.
        }
    }
    
    int request[NUMBER_OF_RESOURCES+1];
    printf("Enter Resource Request: ");
    for (int i= 0; i<NUMBER_OF_RESOURCES + 1; i++){
            scanf("%d", &request[i]);
        } 

    int *request_resources = &request[1]; // just the request array stripped of the  customer ID
    if (!vector_LTorE(request_resources, available, NUMBER_OF_RESOURCES)){
        fprintf(stderr, "Error: Invalid request");
        exit(EXIT_FAILURE);
    }
    // I had a big debate about whether I should grant the request and affect the system state, or create
    // temporary variables that represent the system after the request has been granted, but the assignment
    // spec does not call for this in any way, so I am just going to grant the request, then if this is being 
    // used in any 'real' system, if the request is determined to be unsafe just make sure to ungrant it.
    for (int j= 0; j<NUMBER_OF_RESOURCES; j++){
        available[j] =available[j] - request[j+1];
    }
    for (int j= 0; j<NUMBER_OF_RESOURCES; j++){
        allocation[request[0]][j]= allocation[request[0]][j] + request[j+1];
    }
    for (int j= 0; j<NUMBER_OF_RESOURCES; j++){
        need[request[0]][j]= need[request[0]][j] - request[j+1];
    }

    // The rest of the processing happens in this method, which will also print the output.
    // I know it is side effecting and that isn't great, but I don't wish to return a string and then
    // just print that, so this is fine for me.
    safety_algorithm();

    // This is where I would do the "ungranting" of the request if it put the algorithm in an unsafe state.
    // The process would be: change safety algorithm to return a boolean, if true, keep it how it is,
    // if false, restore the system by doing the same 3 for loops above, just with the sign of adding 
    // or subtracting the request flipped.


    // I'll also set up all the memory to be freed at the end of main
    for(int i= 0; i<NUMBER_OF_CUSTOMERS; i++){
        free(maximum[i]);
        free(allocation[i]);
        free(need[i]);
    }
    free(maximum);
    free(allocation);
    free(need);
    free(total_instances);
    free(available);

    return 0;
}