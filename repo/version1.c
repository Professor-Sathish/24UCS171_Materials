/*
 * Version 01: Basic Data Structure for Bank Account System
 * 
 * Learning Objectives:
 * 1. Understand C structures and their memory layout
 * 2. Learn structure initialization techniques
 * 3. Practice member access and data manipulation
 * 4. Introduction to basic testing concepts
 * 
 * Concepts Covered:
 * - struct keyword and definition
 * - Structure member access (dot notation)
 * - Structure initialization methods
 * - Memory concepts (stack allocation)
 * - Basic input/output operations
 */

#include <stdio.h>
#include <string.h>

/* 
 * CLIENT DATA STRUCTURE
 * 
 * This structure represents a bank account record.
 * Each member serves a specific purpose:
 * 
 * - acct_num: Unique identifier for the account (1-100)
 * - last_name: Customer's surname (max 14 chars + null terminator)
 * - first_name: Customer's first name (max 9 chars + null terminator)
 * - balance: Account balance (supports decimal values)
 * 
 * Memory Layout (typical 64-bit system):
 * - acct_num: 4 bytes
 * - last_name: 15 bytes
 * - first_name: 10 bytes
 * - balance: 8 bytes
 * - Padding: may add extra bytes for alignment
 * Total: approximately 40-48 bytes per record
 */
struct client_data {
    unsigned int acct_num;  // Account number (1-100)
    char last_name[15];     // Last name (14 chars + \0)
    char first_name[10];    // First name (9 chars + \0)
    double balance;         // Account balance
};

/* Function Prototypes - Forward Declarations */
void display_client(const struct client_data *client);
void initialize_client(struct client_data *client, unsigned int acct_num, 
                      const char *last_name, const char *first_name, double balance);
int validate_client_data(const struct client_data *client);
void demonstrate_structure_concepts(void);

/* Test Functions - Simple Testing Framework */
int test_structure_initialization(void);
int test_structure_access(void);
int test_data_validation(void);
void run_all_tests(void);

/*
 * MAIN FUNCTION
 * Entry point for Version 01
 * Demonstrates basic structure operations and runs tests
 */
int main(void) {
    printf("=== Bank Account System - Version 01: Basic Structures ===\n\n");
    
    // Run tests first (TDD approach)
    printf("Running Tests...\n");
    run_all_tests();
    
    printf("\n=== Structure Concepts Demonstration ===\n");
    demonstrate_structure_concepts();
    
    return 0;
}

/*
 * DISPLAY CLIENT INFORMATION
 * 
 * Purpose: Print client data in a formatted way
 * Parameters: Pointer to client_data structure (const for safety)
 * 
 * Note: Using const pointer prevents accidental modification
 */
void display_client(const struct client_data *client) {
    if (client == NULL) {
        printf("Error: Null pointer provided to display_client\n");
        return;
    }
    
    printf("Account Number: %u\n", client->acct_num);
    printf("Name: %s, %s\n", client->last_name, client->first_name);
    printf("Balance: $%.2f\n", client->balance);
    printf("-----------------------------------\n");
}

/*
 * INITIALIZE CLIENT DATA
 * 
 * Purpose: Safely initialize a client_data structure
 * Parameters: 
 *   - client: Pointer to structure to initialize
 *   - acct_num: Account number to assign
 *   - last_name: Last name string
 *   - first_name: First name string
 *   - balance: Initial balance
 * 
 * Safety Features:
 *   - Null pointer checking
 *   - String length validation
 *   - Safe string copying with strncpy
 */
void initialize_client(struct client_data *client, unsigned int acct_num,
                      const char *last_name, const char *first_name, double balance) {
    if (client == NULL) {
        printf("Error: Cannot initialize null client pointer\n");
        return;
    }
    
    client->acct_num = acct_num;
    client->balance = balance;
    
    // Safe string copying - prevents buffer overflow
    if (last_name != NULL) {
        strncpy(client->last_name, last_name, sizeof(client->last_name) - 1);
        client->last_name[sizeof(client->last_name) - 1] = '\0';  // Ensure null termination
    } else {
        client->last_name[0] = '\0';  // Empty string
    }
    
    if (first_name != NULL) {
        strncpy(client->first_name, first_name, sizeof(client->first_name) - 1);
        client->first_name[sizeof(client->first_name) - 1] = '\0';  // Ensure null termination
    } else {
        client->first_name[0] = '\0';  // Empty string
    }
}

/*
 * VALIDATE CLIENT DATA
 * 
 * Purpose: Check if client data is valid
 * Parameters: Pointer to client_data structure
 * Returns: 1 if valid, 0 if invalid
 * 
 * Validation Rules:
 *   - Account number must be between 1 and 100
 *   - Names must not be empty
 *   - Balance can be negative (overdraft allowed)
 */
int validate_client_data(const struct client_data *client) {
    if (client == NULL) {
        return 0;  // Invalid: null pointer
    }
    
    // Check account number range
    if (client->acct_num < 1 || client->acct_num > 100) {
        return 0;  // Invalid: account number out of range
    }
    
    // Check if names are not empty
    if (strlen(client->last_name) == 0 || strlen(client->first_name) == 0) {
        return 0;  // Invalid: empty name
    }
    
    return 1;  // Valid data
}

/*
 * DEMONSTRATE STRUCTURE CONCEPTS
 * 
 * Purpose: Show different ways to work with structures
 * This function demonstrates various structure operations for learning
 */
void demonstrate_structure_concepts(void) {
    printf("\n1. Structure Declaration and Initialization Methods:\n");
    
    // Method 1: Direct initialization
    struct client_data client1 = {1, "Smith", "John", 1500.75};
    printf("Method 1 - Direct initialization:\n");
    display_client(&client1);
    
    // Method 2: Field-by-field assignment
    struct client_data client2;
    client2.acct_num = 2;
    strcpy(client2.last_name, "Johnson");
    strcpy(client2.first_name, "Mary");
    client2.balance = -250.50;  // Overdraft example
    printf("Method 2 - Field-by-field assignment:\n");
    display_client(&client2);
    
    // Method 3: Using initialization function
    struct client_data client3;
    initialize_client(&client3, 3, "Williams", "Bob", 3200.00);
    printf("Method 3 - Using initialization function:\n");
    display_client(&client3);
    
    // Method 4: Array of structures
    printf("\n2. Array of Structures:\n");
    struct client_data clients[3] = {
        {10, "Davis", "Alice", 1000.00},
        {20, "Brown", "Charlie", 2500.50},
        {30, "Miller", "Diana", 750.25}
    };
    
    for (int i = 0; i < 3; i++) {
        printf("Client %d:\n", i + 1);
        display_client(&clients[i]);
    }
    
    // Method 5: Pointer operations
    printf("\n3. Pointer Operations with Structures:\n");
    struct client_data *ptr = &client1;
    printf("Accessing via pointer (ptr->member):\n");
    printf("Account: %u, Name: %s %s, Balance: $%.2f\n",
           ptr->acct_num, ptr->first_name, ptr->last_name, ptr->balance);
    
    // Memory size demonstration
    printf("\n4. Memory Information:\n");
    printf("Size of client_data structure: %zu bytes\n", sizeof(struct client_data));
    printf("Size of unsigned int: %zu bytes\n", sizeof(unsigned int));
    printf("Size of char[15]: %zu bytes\n", sizeof(char[15]));
    printf("Size of char[10]: %zu bytes\n", sizeof(char[10]));
    printf("Size of double: %zu bytes\n", sizeof(double));
}

/*
 * TESTING FUNCTIONS
 * Simple unit tests to verify our code works correctly
 */

int test_structure_initialization(void) {
    printf("Test 1: Structure Initialization... ");
    
    struct client_data client;
    initialize_client(&client, 50, "TestLast", "TestFirst", 100.50);
    
    if (client.acct_num == 50 && 
        strcmp(client.last_name, "TestLast") == 0 &&
        strcmp(client.first_name, "TestFirst") == 0 &&
        client.balance == 100.50) {
        printf("PASSED\n");
        return 1;
    } else {
        printf("FAILED\n");
        return 0;
    }
}

int test_structure_access(void) {
    printf("Test 2: Structure Member Access... ");
    
    struct client_data client = {25, "AccessTest", "Demo", 500.00};
    
    // Test direct access
    if (client.acct_num == 25) {
        printf("PASSED\n");
        return 1;
    } else {
        printf("FAILED\n");
        return 0;
    }
}

int test_data_validation(void) {
    printf("Test 3: Data Validation... ");
    
    struct client_data valid_client = {50, "Valid", "User", 100.00};
    struct client_data invalid_client = {150, "Invalid", "User", 100.00};  // Account number too high
    
    if (validate_client_data(&valid_client) == 1 && 
        validate_client_data(&invalid_client) == 0) {
        printf("PASSED\n");
        return 1;
    } else {
        printf("FAILED\n");
        return 0;
    }
}

void run_all_tests(void) {
    int total_tests = 0;
    int passed_tests = 0;
    
    total_tests++; passed_tests += test_structure_initialization();
    total_tests++; passed_tests += test_structure_access();
    total_tests++; passed_tests += test_data_validation();
    
    printf("\nTest Results: %d/%d tests passed\n", passed_tests, total_tests);
    
    if (passed_tests == total_tests) {
        printf("✅ All tests passed! Ready to move to Version 02.\n");
    } else {
        printf("❌ Some tests failed. Review the code before proceeding.\n");
    }
}

/*
 * LEARNING EXERCISES FOR STUDENTS:
 * 
 * 1. Easy Level:
 *    - Modify the client_data structure to add an 'email' field
 *    - Create a function to calculate total balance for an array of clients
 *    - Add validation for negative account numbers
 * 
 * 2. Medium Level:
 *    - Implement a function to find a client by account number in an array
 *    - Create a function to copy one client structure to another
 *    - Add a field for account creation date and update all functions
 * 
 * 3. Advanced Level:
 *    - Implement a function to sort an array of clients by balance
 *    - Create a function to serialize client data to a string
 *    - Design a memory pool allocator for client structures
 * 
 * NEXT VERSION PREVIEW:
 * In Version 02, we'll learn:
 * - File I/O operations (fopen, fclose, fread, fwrite)
 * - Binary file handling
 * - Persistent data storage
 * - Error handling for file operations
 */