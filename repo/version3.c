/*
 * Version 03: CRUD Operations for Bank Account System
 * 
 * Learning Objectives:
 * 1. Implement Create, Read, Update, Delete operations
 * 2. Master interactive user input handling
 * 3. Learn data validation and sanitization techniques
 * 4. Practice error handling and user feedback
 * 5. Understand record management in binary files
 * 
 * New Concepts Covered:
 * - Interactive menu systems
 * - Input validation and sanitization
 * - Record searching and management
 * - User-friendly error messages
 * - Data integrity checks
 * - Transaction-like operations
 * 
 * Prerequisites: Complete Version 01 (Structures) and Version 02 (File Operations)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Client data structure (from previous versions) */
struct client_data {
    unsigned int acct_num;  // Account number (1-100)
    char last_name[15];     // Last name (14 chars + \0)
    char first_name[10];    // First name (9 chars + \0)
    double balance;         // Account balance
};

/* Constants */
#define DATA_FILE "accounts.dat"
#define MAX_ACCOUNTS 100
#define RECORD_SIZE sizeof(struct client_data)
#define MIN_ACCOUNT_NUM 1
#define MAX_ACCOUNT_NUM 100

/* Function Prototypes */
/* CRUD Operations */
int create_account(void);
int read_account(void);
int update_account(void);
int delete_account(void);

/* Core File Operations */
FILE* open_data_file(const char* mode);
int close_data_file(FILE* file_ptr);
int write_client_to_file(FILE* file_ptr, const struct client_data* client, int position);
int read_client_from_file(FILE* file_ptr, struct client_data* client, int position);
int account_exists(unsigned int acct_num);

/* Input Validation */
unsigned int get_account_number(const char* prompt);
double get_balance_input(const char* prompt);
void get_name_input(char* buffer, int max_length, const char* prompt);
void clear_input_buffer(void);
int validate_account_number(unsigned int acct_num);
int validate_name(const char* name);

/* Display Functions */
void display_client(const struct client_data* client);
void display_all_accounts(void);
void print_account_header(void);
void print_account_row(const struct client_data* client);

/* Utility Functions */
void initialize_client(struct client_data* client, unsigned int acct_num,
                      const char* last_name, const char* first_name, double balance);
void initialize_data_file_if_needed(void);

/* Test Functions */
int test_crud_operations(void);
int test_input_validation(void);
int test_account_management(void);
void run_all_tests(void);
void demonstrate_crud_operations(void);

/*
 * MAIN FUNCTION
 * Entry point for Version 03 - CRUD Operations
 */
int main(void) {
    printf("=== Bank Account System - Version 03: CRUD Operations ===\n\n");
    
    // Initialize data file if needed
    initialize_data_file_if_needed();
    
    // Run tests (TDD approach)
    printf("Running CRUD Tests...\n");
    run_all_tests();
    
    // Demonstrate CRUD operations
    printf("\n=== CRUD Operations Demonstration ===\n");
    demonstrate_crud_operations();
    
    return 0;
}

/*
 * CREATE ACCOUNT (C in CRUD)
 * 
 * Purpose: Create a new bank account with user input
 * Returns: 1 on success, 0 on failure
 * 
 * Process:
 * 1. Get and validate account number
 * 2. Check if account already exists
 * 3. Get customer information
 * 4. Validate all inputs
 * 5. Write to file
 * 6. Confirm success
 */
int create_account(void) {
    printf("\n=== CREATE NEW ACCOUNT ===\n");
    
    // Get account number
    unsigned int acct_num = get_account_number("Enter new account number (1-100): ");
    if (acct_num == 0) {
        printf("Invalid account number. Operation cancelled.\n");
        return 0;
    }
    
    // Check if account already exists
    if (account_exists(acct_num)) {
        printf("Error: Account #%u already exists!\n", acct_num);
        printf("Use UPDATE operation to modify existing accounts.\n");
        return 0;
    }
    
    // Get customer information
    char last_name[15], first_name[10];
    double initial_balance;
    
    get_name_input(last_name, sizeof(last_name), "Enter last name: ");
    get_name_input(first_name, sizeof(first_name), "Enter first name: ");
    initial_balance = get_balance_input("Enter initial balance: ");
    
    // Validate all inputs
    if (!validate_name(last_name) || !validate_name(first_name)) {
        printf("Error: Invalid name format. Names cannot be empty.\n");
        return 0;
    }
    
    // Create client structure
    struct client_data new_client;
    initialize_client(&new_client, acct_num, last_name, first_name, initial_balance);
    
    // Write to file
    FILE* file_ptr = open_data_file("rb");
    if (file_ptr == NULL) return 0;
    
    struct client_data client;
    int position = acct_num - 1;
    int success = read_client_from_file(file_ptr, &client, position);
    close_data_file(file_ptr);
    
    return (success && client.acct_num != 0);
}

/*
 * INPUT VALIDATION FUNCTIONS
 * 
 * These functions handle user input safely and validate data
 */

/*
 * GET_ACCOUNT_NUMBER
 * 
 * Purpose: Get and validate account number from user
 * Parameters: prompt - message to display to user
 * Returns: valid account number (1-100) or 0 on error
 */
unsigned int get_account_number(const char* prompt) {
    unsigned int acct_num;
    
    printf("%s", prompt);
    
    if (scanf("%u", &acct_num) != 1) {
        printf("Error: Please enter a valid number.\n");
        clear_input_buffer();
        return 0;
    }
    clear_input_buffer();
    
    if (!validate_account_number(acct_num)) {
        printf("Error: Account number must be between %d and %d.\n", 
               MIN_ACCOUNT_NUM, MAX_ACCOUNT_NUM);
        return 0;
    }
    
    return acct_num;
}

/*
 * GET_BALANCE_INPUT
 * 
 * Purpose: Get and validate balance/transaction amount from user
 * Parameters: prompt - message to display to user
 * Returns: entered balance amount
 */
double get_balance_input(const char* prompt) {
    double amount;
    
    printf("%s", prompt);
    
    if (scanf("%lf", &amount) != 1) {
        printf("Error: Please enter a valid amount.\n");
        clear_input_buffer();
        return 0.0;
    }
    clear_input_buffer();
    
    return amount;
}

/*
 * GET_NAME_INPUT
 * 
 * Purpose: Get and validate name input from user
 * Parameters: 
 *   - buffer: where to store the input
 *   - max_length: maximum length of input
 *   - prompt: message to display
 */
void get_name_input(char* buffer, int max_length, const char* prompt) {
    printf("%s", prompt);
    
    if (fgets(buffer, max_length, stdin) != NULL) {
        // Remove newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Trim leading and trailing spaces
        char* start = buffer;
        while (isspace(*start)) start++;
        
        char* end = start + strlen(start) - 1;
        while (end > start && isspace(*end)) end--;
        end[1] = '\0';
        
        // Move trimmed string to beginning of buffer
        if (start != buffer) {
            memmove(buffer, start, strlen(start) + 1);
        }
    } else {
        buffer[0] = '\0';  // Empty string on error
    }
}

/*
 * CLEAR_INPUT_BUFFER
 * 
 * Purpose: Clear any remaining characters from input buffer
 * This prevents issues with subsequent input operations
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * VALIDATE_ACCOUNT_NUMBER
 * 
 * Purpose: Check if account number is in valid range
 * Parameters: acct_num - account number to validate
 * Returns: 1 if valid, 0 if invalid
 */
int validate_account_number(unsigned int acct_num) {
    return (acct_num >= MIN_ACCOUNT_NUM && acct_num <= MAX_ACCOUNT_NUM);
}

/*
 * VALIDATE_NAME
 * 
 * Purpose: Check if name is valid (not empty, reasonable length)
 * Parameters: name - string to validate
 * Returns: 1 if valid, 0 if invalid
 */
int validate_name(const char* name) {
    if (name == NULL) return 0;
    
    size_t len = strlen(name);
    
    // Check if empty or too short
    if (len == 0) return 0;
    
    // Check for valid characters (letters, spaces, hyphens, apostrophes)
    for (size_t i = 0; i < len; i++) {
        char c = name[i];
        if (!isalpha(c) && c != ' ' && c != '-' && c != '\'') {
            return 0;
        }
    }
    
    return 1;
}

/*
 * DISPLAY FUNCTIONS
 * 
 * Functions for formatting and displaying account information
 */

void display_client(const struct client_data* client) {
    if (client == NULL) {
        printf("Error: Cannot display null client data.\n");
        return;
    }
    
    printf("Account Number: %u\n", client->acct_num);
    printf("Customer Name:  %s, %s\n", client->last_name, client->first_name);
    printf("Account Balance: $%.2f\n", client->balance);
    
    // Additional status information
    if (client->balance < 0) {
        printf("Status: OVERDRAWN (%.2f)\n", -client->balance);
    } else if (client->balance == 0) {
        printf("Status: ZERO BALANCE\n");
    } else {
        printf("Status: ACTIVE\n");
    }
    
    printf("-------------------------------------------\n");
}

void display_all_accounts(void) {
    printf("\n=== ALL ACCOUNTS REPORT ===\n");
    
    FILE* file_ptr = open_data_file("rb");
    if (file_ptr == NULL) {
        printf("Error: Could not open data file for reading.\n");
        return;
    }
    
    print_account_header();
    
    struct client_data client;
    int total_accounts = 0;
    double total_balance = 0.0;
    int overdrawn_accounts = 0;
    
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (read_client_from_file(file_ptr, &client, i) && client.acct_num != 0) {
            print_account_row(&client);
            total_accounts++;
            total_balance += client.balance;
            if (client.balance < 0) overdrawn_accounts++;
        }
    }
    
    close_data_file(file_ptr);
    
    // Summary statistics
    printf("=======================================================\n");
    printf("Total Accounts: %d\n", total_accounts);
    printf("Total Balance:  $%.2f\n", total_balance);
    printf("Overdrawn:      %d accounts\n", overdrawn_accounts);
    if (total_accounts > 0) {
        printf("Average Balance: $%.2f\n", total_balance / total_accounts);
    }
}

void print_account_header(void) {
    printf("%-6s %-15s %-10s %12s %10s\n", 
           "Acct#", "Last Name", "First Name", "Balance", "Status");
    printf("=======================================================\n");
}

void print_account_row(const struct client_data* client) {
    if (client == NULL) return;
    
    const char* status;
    if (client->balance < 0) {
        status = "OVERDRAWN";
    } else if (client->balance == 0) {
        status = "ZERO";
    } else {
        status = "ACTIVE";
    }
    
    printf("%-6u %-15s %-10s %12.2f %10s\n",
           client->acct_num, client->last_name, client->first_name,
           client->balance, status);
}

/*
 * UTILITY FUNCTIONS
 */

void initialize_client(struct client_data* client, unsigned int acct_num,
                      const char* last_name, const char* first_name, double balance) {
    if (client == NULL) return;
    
    client->acct_num = acct_num;
    client->balance = balance;
    
    // Safe string copying
    if (last_name != NULL) {
        strncpy(client->last_name, last_name, sizeof(client->last_name) - 1);
        client->last_name[sizeof(client->last_name) - 1] = '\0';
    } else {
        client->last_name[0] = '\0';
    }
    
    if (first_name != NULL) {
        strncpy(client->first_name, first_name, sizeof(client->first_name) - 1);
        client->first_name[sizeof(client->first_name) - 1] = '\0';
    } else {
        client->first_name[0] = '\0';
    }
}

void initialize_data_file_if_needed(void) {
    // Check if file exists
    FILE* test_file = fopen(DATA_FILE, "rb");
    if (test_file != NULL) {
        fclose(test_file);
        printf("Data file '%s' found.\n", DATA_FILE);
        return;
    }
    
    // Create new file
    printf("Creating new data file '%s'...\n", DATA_FILE);
    FILE* file_ptr = fopen(DATA_FILE, "wb");
    if (file_ptr == NULL) {
        printf("Error: Could not create data file.\n");
        return;
    }
    
    // Initialize with empty records
    struct client_data empty_client = {0, "", "", 0.0};
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        fwrite(&empty_client, RECORD_SIZE, 1, file_ptr);
    }
    
    fclose(file_ptr);
    printf("Data file initialized with %d empty slots.\n", MAX_ACCOUNTS);
}

/*
 * DEMONSTRATION FUNCTION
 * 
 * Purpose: Show CRUD operations in action with sample data
 */
void demonstrate_crud_operations(void) {
    printf("\n1. Creating Sample Accounts (CREATE):\n");
    
    // Sample data for demonstration
    struct sample_account {
        unsigned int acct_num;
        const char* last_name;
        const char* first_name;
        double balance;
    } samples[] = {
        {1, "Smith", "John", 1500.75},
        {5, "Johnson", "Mary", -250.50},
        {10, "Williams", "Bob", 3200.00},
        {25, "Davis", "Alice", 0.00}
    };
    
    int num_samples = sizeof(samples) / sizeof(samples[0]);
    
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) return;
    
    for (int i = 0; i < num_samples; i++) {
        struct client_data client;
        initialize_client(&client, samples[i].acct_num, samples[i].last_name,
                         samples[i].first_name, samples[i].balance);
        
        int position = samples[i].acct_num - 1;
        if (write_client_to_file(file_ptr, &client, position)) {
            printf("✅ Created account #%u for %s %s\n", 
                   client.acct_num, client.first_name, client.last_name);
        }
    }
    
    close_data_file(file_ptr);
    
    printf("\n2. Reading Account Information (READ):\n");
    file_ptr = open_data_file("rb");
    if (file_ptr != NULL) {
        struct client_data client;
        if (read_client_from_file(file_ptr, &client, 0) && client.acct_num != 0) {
            printf("Account #1 details:\n");
            display_client(&client);
        }
        close_data_file(file_ptr);
    }
    
    printf("\n3. Updating Account Balance (UPDATE):\n");
    file_ptr = open_data_file("rb+");
    if (file_ptr != NULL) {
        struct client_data client;
        if (read_client_from_file(file_ptr, &client, 4) && client.acct_num != 0) {
            printf("Before update:\n");
            display_client(&client);
            
            // Simulate a deposit
            client.balance += 500.0;
            
            if (write_client_to_file(file_ptr, &client, 4)) {
                printf("After $500 deposit:\n");
                display_client(&client);
            }
        }
        close_data_file(file_ptr);
    }
    
    printf("\n4. Displaying All Accounts:\n");
    display_all_accounts();
    
    printf("\n5. Account Existence Check:\n");
    printf("Account #1 exists: %s\n", account_exists(1) ? "Yes" : "No");
    printf("Account #50 exists: %s\n", account_exists(50) ? "Yes" : "No");
}

/*
 * TESTING FUNCTIONS
 * Unit tests for CRUD operations
 */

int test_crud_operations(void) {
    printf("Test 1: CRUD Operations... ");
    
    // Test CREATE
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("FAILED - Could not open file\n");
        return 0;
    }
    
    struct client_data test_client;
    initialize_client(&test_client, 99, "TestLast", "TestFirst", 100.0);
    
    if (!write_client_to_file(file_ptr, &test_client, 98)) {
        printf("FAILED - Could not create record\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    // Test READ
    struct client_data read_client;
    if (!read_client_from_file(file_ptr, &read_client, 98)) {
        printf("FAILED - Could not read record\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    // Test UPDATE
    read_client.balance += 50.0;
    if (!write_client_to_file(file_ptr, &read_client, 98)) {
        printf("FAILED - Could not update record\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    // Test DELETE (write empty record)
    struct client_data empty_client = {0, "", "", 0.0};
    if (!write_client_to_file(file_ptr, &empty_client, 98)) {
        printf("FAILED - Could not delete record\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    close_data_file(file_ptr);
    printf("PASSED\n");
    return 1;
}

int test_input_validation(void) {
    printf("Test 2: Input Validation... ");
    
    // Test account number validation
    if (!validate_account_number(50) || validate_account_number(0) || validate_account_number(101)) {
        printf("FAILED - Account number validation\n");
        return 0;
    }
    
    // Test name validation
    if (!validate_name("Smith") || validate_name("") || validate_name("123")) {
        printf("FAILED - Name validation\n");
        return 0;
    }
    
    printf("PASSED\n");
    return 1;
}

int test_account_management(void) {
    printf("Test 3: Account Management... ");
    
    // Create test account
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("FAILED - Could not open file\n");
        return 0;
    }
    
    struct client_data test_account = {77, "Manager", "Test", 200.0};
    write_client_to_file(file_ptr, &test_account, 76);
    close_data_file(file_ptr);
    
    // Test account_exists function
    if (!account_exists(77)) {
        printf("FAILED - account_exists returned false for existing account\n");
        return 0;
    }
    
    if (account_exists(88)) {  // Should not exist
        printf("FAILED - account_exists returned true for non-existing account\n");
        return 0;
    }
    
    printf("PASSED\n");
    return 1;
}

void run_all_tests(void) {
    int total_tests = 0;
    int passed_tests = 0;
    
    total_tests++; passed_tests += test_crud_operations();
    total_tests++; passed_tests += test_input_validation();
    total_tests++; passed_tests += test_account_management();
    
    printf("\nTest Results: %d/%d tests passed\n", passed_tests, total_tests);
    
    if (passed_tests == total_tests) {
        printf("✅ All CRUD tests passed! Ready for Version 04.\n");
    } else {
        printf("❌ Some tests failed. Review CRUD operations before proceeding.\n");
    }
}

/*
 * LEARNING EXERCISES FOR STUDENTS:
 * 
 * 1. Easy Level:
 *    - Add a search function to find accounts by name
 *    - Implement account number auto-generation
 *    - Add input validation for minimum balance requirements
 * 
 * 2. Medium Level:
 *    - Add transaction history logging
 *    - Implement account transfer functionality
 *    - Create batch operations (create multiple accounts from file)
 * 
 * 3. Advanced Level:
 *    - Add account locking/unlocking features
 *    - Implement data backup and restore
 *    - Create audit trail for all operations
 * 
 * DEBUGGING TIPS:
 * - Always validate input before processing
 * - Check return values of all file operations
 * - Use meaningful error messages for users
 * - Test edge cases (empty names, zero balances, etc.)
 * 
 * NEXT VERSION PREVIEW:
 * In Version 04, we'll learn:
 * - Interactive menu systems
 * - Program flow control
 * - User experience design
 * - Complete application integration
 */_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("Error: Could not open data file for writing.\n");
        return 0;
    }
    
    int position = acct_num - 1;  // Convert to 0-based index
    int success = write_client_to_file(file_ptr, &new_client, position);
    close_data_file(file_ptr);
    
    if (success) {
        printf("\n✅ Account created successfully!\n");
        printf("Account Details:\n");
        display_client(&new_client);
        return 1;
    } else {
        printf("❌ Error: Could not create account. Please try again.\n");
        return 0;
    }
}

/*
 * CORE FILE OPERATIONS
 * (Simplified versions from Version 02)
 */

FILE* open_data_file(const char* mode) {
    FILE* file_ptr = fopen(DATA_FILE, mode);
    if (file_ptr == NULL) {
        printf("Error: Could not open file '%s' in mode '%s'\n", DATA_FILE, mode);
    }
    return file_ptr;
}

int close_data_file(FILE* file_ptr) {
    if (file_ptr == NULL) return -1;
    return fclose(file_ptr);
}

int write_client_to_file(FILE* file_ptr, const struct client_data* client, int position) {
    if (file_ptr == NULL || client == NULL || position < 0 || position >= MAX_ACCOUNTS) {
        return 0;
    }
    
    long file_position = position * RECORD_SIZE;
    if (fseek(file_ptr, file_position, SEEK_SET) != 0) return 0;
    
    return (fwrite(client, RECORD_SIZE, 1, file_ptr) == 1);
}

int read_client_from_file(FILE* file_ptr, struct client_data* client, int position) {
    if (file_ptr == NULL || client == NULL || position < 0 || position >= MAX_ACCOUNTS) {
        return 0;
    }
    
    long file_position = position * RECORD_SIZE;
    if (fseek(file_ptr, file_position, SEEK_SET) != 0) return 0;
    
    return (fread(client, RECORD_SIZE, 1, file_ptr) == 1);
}

/*
 * ACCOUNT_EXISTS
 * 
 * Purpose: Check if an account number is already in use
 * Parameters: acct_num - account number to check
 * Returns: 1 if exists, 0 if not exists or error
 */
int account_exists(unsigned int acct_num) {
    if (!validate_account_number(acct_num)) return 0;
    
    FILE* file

/*
 * READ ACCOUNT (R in CRUD)
 * 
 * Purpose: Display account information for a specific account
 * Returns: 1 on success, 0 on failure
 */
int read_account(void) {
    printf("\n=== READ ACCOUNT INFORMATION ===\n");
    
    unsigned int acct_num = get_account_number("Enter account number to view (1-100): ");
    if (acct_num == 0) {
        printf("Invalid account number. Operation cancelled.\n");
        return 0;
    }
    
    FILE* file_ptr = open_data_file("rb");
    if (file_ptr == NULL) {
        printf("Error: Could not open data file for reading.\n");
        return 0;
    }
    
    struct client_data client;
    int position = acct_num - 1;
    int success = read_client_from_file(file_ptr, &client, position);
    close_data_file(file_ptr);
    
    if (success && client.acct_num != 0) {
        printf("\n✅ Account found!\n");
        display_client(&client);
        return 1;
    } else {
        printf("❌ Account #%u not found or is empty.\n", acct_num);
        return 0;
    }
}

/*
 * UPDATE ACCOUNT (U in CRUD)
 * 
 * Purpose: Modify existing account information
 * Returns: 1 on success, 0 on failure
 * 
 * Update Options:
 * 1. Add/subtract from balance (transactions)
 * 2. Update customer names
 * 3. Complete account information update
 */
int update_account(void) {
    printf("\n=== UPDATE ACCOUNT ===\n");
    
    unsigned int acct_num = get_account_number("Enter account number to update (1-100): ");
    if (acct_num == 0) {
        printf("Invalid account number. Operation cancelled.\n");
        return 0;
    }
    
    // Read existing account
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("Error: Could not open data file for updating.\n");
        return 0;
    }
    
    struct client_data client;
    int position = acct_num - 1;
    int success = read_client_from_file(file_ptr, &client, position);
    
    if (!success || client.acct_num == 0) {
        printf("❌ Account #%u not found. Use CREATE to add new accounts.\n", acct_num);
        close_data_file(file_ptr);
        return 0;
    }
    
    printf("\nCurrent Account Information:\n");
    display_client(&client);
    
    // Update menu
    printf("\nUpdate Options:\n");
    printf("1. Update balance (add/subtract transaction)\n");
    printf("2. Update customer names\n");
    printf("3. Update all information\n");
    printf("Enter choice (1-3): ");
    
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Operation cancelled.\n");
        clear_input_buffer();
        close_data_file(file_ptr);
        return 0;
    }
    clear_input_buffer();
    
    switch (choice) {
        case 1: {
            // Balance update (transaction)
            double transaction = get_balance_input("Enter transaction amount (+credit/-debit): ");
            double old_balance = client.balance;
            client.balance += transaction;
            
            printf("\nTransaction Summary:\n");
            printf("Previous Balance: $%.2f\n", old_balance);
            printf("Transaction:      $%.2f\n", transaction);
            printf("New Balance:      $%.2f\n", client.balance);
            break;
        }
        case 2: {
            // Name update
            printf("Current: %s, %s\n", client.last_name, client.first_name);
            get_name_input(client.last_name, sizeof(client.last_name), "Enter new last name: ");
            get_name_input(client.first_name, sizeof(client.first_name), "Enter new first name: ");
            
            if (!validate_name(client.last_name) || !validate_name(client.first_name)) {
                printf("Error: Invalid name format. Update cancelled.\n");
                close_data_file(file_ptr);
                return 0;
            }
            break;
        }
        case 3: {
            // Complete update
            get_name_input(client.last_name, sizeof(client.last_name), "Enter new last name: ");
            get_name_input(client.first_name, sizeof(client.first_name), "Enter new first name: ");
            client.balance = get_balance_input("Enter new balance: ");
            
            if (!validate_name(client.last_name) || !validate_name(client.first_name)) {
                printf("Error: Invalid name format. Update cancelled.\n");
                close_data_file(file_ptr);
                return 0;
            }
            break;
        }
        default:
            printf("Invalid choice. Operation cancelled.\n");
            close_data_file(file_ptr);
            return 0;
    }
    
    // Write updated record
    success = write_client_to_file(file_ptr, &client, position);
    close_data_file(file_ptr);
    
    if (success) {
        printf("\n✅ Account updated successfully!\n");
        printf("Updated Account Information:\n");
        display_client(&client);
        return 1;
    } else {
        printf("❌ Error: Could not update account. Changes not saved.\n");
        return 0;
    }
}

/*
 * DELETE ACCOUNT (D in CRUD)
 * 
 * Purpose: Remove an account from the system
 * Returns: 1 on success, 0 on failure
 * 
 * Safety Features:
 * - Shows account before deletion
 * - Requires confirmation
 * - Warns about balance if non-zero
 */
int delete_account(void) {
    printf("\n=== DELETE ACCOUNT ===\n");
    
    unsigned int acct_num = get_account_number("Enter account number to delete (1-100): ");
    if (acct_num == 0) {
        printf("Invalid account number. Operation cancelled.\n");
        return 0;
    }
    
    // Read existing account
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("Error: Could not open data file for deletion.\n");
        return 0;
    }
    
    struct client_data client;
    int position = acct_num - 1;
    int success = read_client_from_file(file_ptr, &client, position);
    
    if (!success || client.acct_num == 0) {
        printf("❌ Account #%u not found or already empty.\n", acct_num);
        close_data_file(file_ptr);
        return 0;
    }
    
    printf("\nAccount to be deleted:\n");
    display_client(&client);
    
    // Warning for non-zero balance
    if (client.balance != 0.0) {
        printf("⚠️  WARNING: This account has a balance of $%.2f\n", client.balance);
        printf("Deleting will remove this balance permanently.\n");
    }
    
    // Confirmation
    printf("\nAre you sure you want to delete this account? (y/N): ");
    char confirmation;
    if (scanf(" %c", &confirmation) != 1) {
        printf("Invalid input. Deletion cancelled.\n");
        clear_input_buffer();
        close_data_file(file_ptr);
        return 0;
    }
    clear_input_buffer();
    
    if (tolower(confirmation) != 'y') {
        printf("Deletion cancelled by user.\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    // Create empty record for deletion
    struct client_data empty_client = {0, "", "", 0.0};
    success = write_client_to_file(file_ptr, &empty_client, position);
    close_data_file(file_ptr);
    
    if (success) {
        printf("\n✅ Account #%u deleted successfully!\n", acct_num);
        return 1;
    } else {
        printf("❌ Error: Could not delete account. Please try again.\n");
        return 0;
    }
}