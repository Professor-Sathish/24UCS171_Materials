/*
 * Version 02: File Operations for Bank Account System
 * 
 * Learning Objectives:
 * 1. Understand file I/O operations in C
 * 2. Learn the difference between text and binary files
 * 3. Master file positioning and seeking
 * 4. Implement proper error handling for file operations
 * 5. Practice persistent data storage concepts
 * 
 * New Concepts Covered:
 * - fopen(), fclose(), fread(), fwrite()
 * - File modes: "r", "w", "rb", "wb", "rb+"
 * - fseek(), ftell(), rewind()
 * - Error handling and file validation
 * - Binary file structure and layout
 * 
 * Prerequisites: Complete Version 01 (Basic Structures)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reuse the client_data structure from Version 01 */
struct client_data {
    unsigned int acct_num;  // Account number (1-100)
    char last_name[15];     // Last name (14 chars + \0)
    char first_name[10];    // First name (9 chars + \0)
    double balance;         // Account balance
};

/* Constants for file operations */
#define DATA_FILE "accounts.dat"        // Binary data file
#define TEXT_FILE "accounts.txt"        // Text output file
#define MAX_ACCOUNTS 100                // Maximum number of accounts
#define RECORD_SIZE sizeof(struct client_data)

/* Function Prototypes */
/* File Operations */
FILE* open_data_file(const char* mode);
int close_data_file(FILE* file_ptr);
int write_client_to_file(FILE* file_ptr, const struct client_data* client, int position);
int read_client_from_file(FILE* file_ptr, struct client_data* client, int position);

/* Data Management */
void initialize_data_file(void);
void display_file_contents(void);
void create_text_report(void);
long get_file_size(FILE* file_ptr);
int count_records(FILE* file_ptr);

/* Utility Functions */
void display_client(const struct client_data* client);
void initialize_client(struct client_data* client, unsigned int acct_num,
                      const char* last_name, const char* first_name, double balance);

/* Test Functions */
int test_file_creation(void);
int test_file_writing(void);
int test_file_reading(void);
int test_file_positioning(void);
void run_all_tests(void);

/* Demo Functions */
void demonstrate_file_concepts(void);

/*
 * MAIN FUNCTION
 * Entry point for Version 02 - File Operations
 */
int main(void) {
    printf("=== Bank Account System - Version 02: File Operations ===\n\n");
    
    // Initialize data file if it doesn't exist
    printf("Initializing data file...\n");
    initialize_data_file();
    
    // Run tests (TDD approach)
    printf("\nRunning File Operation Tests...\n");
    run_all_tests();
    
    // Demonstrate file concepts
    printf("\n=== File Operations Demonstration ===\n");
    demonstrate_file_concepts();
    
    return 0;
}

/*
 * OPEN DATA FILE
 * 
 * Purpose: Safely open the binary data file
 * Parameters: mode - file opening mode ("rb", "wb", "rb+", etc.)
 * Returns: File pointer or NULL on failure
 * 
 * File Modes Explained:
 * - "rb": Read binary (file must exist)
 * - "wb": Write binary (creates new file, overwrites existing)
 * - "rb+": Read/Write binary (file must exist)
 * - "wb+": Read/Write binary (creates new file)
 */
FILE* open_data_file(const char* mode) {
    FILE* file_ptr = fopen(DATA_FILE, mode);
    
    if (file_ptr == NULL) {
        printf("Error: Could not open file '%s' in mode '%s'\n", DATA_FILE, mode);
        printf("Possible reasons:\n");
        printf("- File doesn't exist (for read modes)\n");
        printf("- No write permission (for write modes)\n");
        printf("- Disk full or I/O error\n");
    } else {
        printf("Successfully opened '%s' in mode '%s'\n", DATA_FILE, mode);
    }
    
    return file_ptr;
}

/*
 * CLOSE DATA FILE
 * 
 * Purpose: Safely close file and handle errors
 * Parameters: file_ptr - pointer to open file
 * Returns: 0 on success, -1 on failure
 */
int close_data_file(FILE* file_ptr) {
    if (file_ptr == NULL) {
        printf("Warning: Attempting to close null file pointer\n");
        return -1;
    }
    
    int result = fclose(file_ptr);
    if (result == 0) {
        printf("File closed successfully\n");
    } else {
        printf("Error: Failed to close file properly\n");
    }
    
    return result;
}

/*
 * WRITE CLIENT TO FILE
 * 
 * Purpose: Write a client record to a specific position in the binary file
 * Parameters: 
 *   - file_ptr: Open file pointer
 *   - client: Pointer to client data to write
 *   - position: Record position (0-based)
 * Returns: 1 on success, 0 on failure
 * 
 * Key Concepts:
 * - Binary file positioning with fseek()
 * - SEEK_SET: Position from beginning of file
 * - Record-based file structure
 * - Error checking with fwrite() return value
 */
int write_client_to_file(FILE* file_ptr, const struct client_data* client, int position) {
    if (file_ptr == NULL || client == NULL) {
        printf("Error: Invalid parameters for write_client_to_file\n");
        return 0;
    }
    
    if (position < 0 || position >= MAX_ACCOUNTS) {
        printf("Error: Invalid position %d (must be 0-%d)\n", position, MAX_ACCOUNTS-1);
        return 0;
    }
    
    // Calculate file position: position * size_of_one_record
    long file_position = position * RECORD_SIZE;
    
    // Move file pointer to the desired position
    if (fseek(file_ptr, file_position, SEEK_SET) != 0) {
        printf("Error: Could not seek to position %d\n", position);
        return 0;
    }
    
    // Write the client data
    size_t written = fwrite(client, RECORD_SIZE, 1, file_ptr);
    
    if (written == 1) {
        printf("Successfully wrote client %u to position %d\n", client->acct_num, position);
        return 1;
    } else {
        printf("Error: Could not write client data to file\n");
        return 0;
    }
}

/*
 * READ CLIENT FROM FILE
 * 
 * Purpose: Read a client record from a specific position in the binary file
 * Parameters:
 *   - file_ptr: Open file pointer
 *   - client: Pointer to structure to store read data
 *   - position: Record position (0-based)
 * Returns: 1 on success, 0 on failure
 */
int read_client_from_file(FILE* file_ptr, struct client_data* client, int position) {
    if (file_ptr == NULL || client == NULL) {
        printf("Error: Invalid parameters for read_client_from_file\n");
        return 0;
    }
    
    if (position < 0 || position >= MAX_ACCOUNTS) {
        printf("Error: Invalid position %d (must be 0-%d)\n", position, MAX_ACCOUNTS-1);
        return 0;
    }
    
    // Calculate and seek to file position
    long file_position = position * RECORD_SIZE;
    if (fseek(file_ptr, file_position, SEEK_SET) != 0) {
        printf("Error: Could not seek to position %d\n", position);
        return 0;
    }
    
    // Read the client data
    size_t read_count = fread(client, RECORD_SIZE, 1, file_ptr);
    
    if (read_count == 1) {
        printf("Successfully read client from position %d\n", position);
        return 1;
    } else {
        printf("Warning: Could not read client data from position %d\n", position);
        // Initialize empty client for consistency
        memset(client, 0, sizeof(struct client_data));
        return 0;
    }
}

/*
 * INITIALIZE DATA FILE
 * 
 * Purpose: Create and initialize the binary data file with empty records
 * This creates a file with MAX_ACCOUNTS empty records for random access
 */
void initialize_data_file(void) {
    FILE* file_ptr = fopen(DATA_FILE, "wb");  // Create new binary file
    
    if (file_ptr == NULL) {
        printf("Error: Could not create data file\n");
        return;
    }
    
    // Create empty client record (all zeros)
    struct client_data empty_client = {0, "", "", 0.0};
    
    // Write MAX_ACCOUNTS empty records
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (fwrite(&empty_client, RECORD_SIZE, 1, file_ptr) != 1) {
            printf("Error: Could not initialize record %d\n", i);
            break;
        }
    }
    
    printf("Data file initialized with %d empty records\n", MAX_ACCOUNTS);
    printf("File size: %ld bytes\n", MAX_ACCOUNTS * RECORD_SIZE);
    
    fclose(file_ptr);
}

/*
 * DISPLAY FILE CONTENTS
 * 
 * Purpose: Read and display all non-empty records from the file
 * Demonstrates sequential file reading
 */
void display_file_contents(void) {
    FILE* file_ptr = open_data_file("rb");
    if (file_ptr == NULL) return;
    
    printf("\n=== Current File Contents ===\n");
    printf("%-6s %-15s %-10s %10s\n", "Acct#", "Last Name", "First Name", "Balance");
    printf("------------------------------------------------\n");
    
    struct client_data client;
    int records_found = 0;
    
    rewind(file_ptr);  // Start from beginning of file
    
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (read_client_from_file(file_ptr, &client, i)) {
            // Only display non-empty records
            if (client.acct_num != 0) {
                printf("%-6u %-15s %-10s %10.2f\n", 
                       client.acct_num, client.last_name, 
                       client.first_name, client.balance);
                records_found++;
            }
        }
    }
    
    printf("\nTotal records found: %d\n", records_found);
    close_data_file(file_ptr);
}

/*
 * CREATE TEXT REPORT
 * 
 * Purpose: Convert binary file to formatted text file for printing
 * Demonstrates binary-to-text file conversion
 */
void create_text_report(void) {
    FILE* read_ptr = open_data_file("rb");
    FILE* write_ptr = fopen(TEXT_FILE, "w");
    
    if (read_ptr == NULL || write_ptr == NULL) {
        printf("Error: Could not open files for text report\n");
        if (read_ptr) fclose(read_ptr);
        if (write_ptr) fclose(write_ptr);
        return;
    }
    
    // Write header to text file
    fprintf(write_ptr, "BANK ACCOUNT REPORT\n");
    fprintf(write_ptr, "Generated from binary data file\n\n");
    fprintf(write_ptr, "%-6s %-15s %-10s %12s\n", "Acct#", "Last Name", "First Name", "Balance");
    fprintf(write_ptr, "=================================================\n");
    
    struct client_data client;
    double total_balance = 0.0;
    int record_count = 0;
    
    rewind(read_ptr);
    
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (read_client_from_file(read_ptr, &client, i) && client.acct_num != 0) {
            fprintf(write_ptr, "%-6u %-15s %-10s %12.2f\n",
                   client.acct_num, client.last_name, 
                   client.first_name, client.balance);
            total_balance += client.balance;
            record_count++;
        }
    }
    
    // Write summary
    fprintf(write_ptr, "=================================================\n");
    fprintf(write_ptr, "Total Accounts: %d\n", record_count);
    fprintf(write_ptr, "Total Balance: $%.2f\n", total_balance);
    
    fclose(read_ptr);
    fclose(write_ptr);
    
    printf("Text report created: %s\n", TEXT_FILE);
}

/*
 * GET FILE SIZE
 * 
 * Purpose: Determine the size of a file in bytes
 * Parameters: file_ptr - open file pointer
 * Returns: file size in bytes, or -1 on error
 */
long get_file_size(FILE* file_ptr) {
    if (file_ptr == NULL) {
        return -1;
    }
    
    // Save current position
    long current_pos = ftell(file_ptr);
    
    // Seek to end of file
    if (fseek(file_ptr, 0, SEEK_END) != 0) {
        return -1;
    }
    
    // Get position (which is the file size)
    long file_size = ftell(file_ptr);
    
    // Restore original position
    fseek(file_ptr, current_pos, SEEK_SET);
    
    return file_size;
}

/*
 * COUNT RECORDS
 * 
 * Purpose: Count non-empty records in the file
 * Parameters: file_ptr - open file pointer
 * Returns: number of valid records
 */
int count_records(FILE* file_ptr) {
    if (file_ptr == NULL) {
        return -1;
    }
    
    struct client_data client;
    int count = 0;
    
    rewind(file_ptr);
    
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (fread(&client, RECORD_SIZE, 1, file_ptr) == 1) {
            if (client.acct_num != 0) {
                count++;
            }
        }
    }
    
    return count;
}

/*
 * UTILITY FUNCTIONS (from Version 01)
 */
void display_client(const struct client_data* client) {
    if (client == NULL) {
        printf("Error: Null pointer provided to display_client\n");
        return;
    }
    
    printf("Account Number: %u\n", client->acct_num);
    printf("Name: %s, %s\n", client->last_name, client->first_name);
    printf("Balance: $%.2f\n", client->balance);
    printf("-----------------------------------\n");
}

void initialize_client(struct client_data* client, unsigned int acct_num,
                      const char* last_name, const char* first_name, double balance) {
    if (client == NULL) return;
    
    client->acct_num = acct_num;
    client->balance = balance;
    
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

/*
 * DEMONSTRATION FUNCTION
 * 
 * Purpose: Show various file operations in action
 */
void demonstrate_file_concepts(void) {
    printf("\n1. File Creation and Initialization:\n");
    printf("   - Created binary file: %s\n", DATA_FILE);
    printf("   - File size: %ld bytes\n", MAX_ACCOUNTS * RECORD_SIZE);
    printf("   - Records capacity: %d\n", MAX_ACCOUNTS);
    
    printf("\n2. Adding Sample Data:\n");
    FILE* file_ptr = open_data_file("rb+");  // Read/Write mode
    if (file_ptr == NULL) return;
    
    // Add some sample clients
    struct client_data sample_clients[] = {
        {1, "Smith", "John", 1500.75},
        {5, "Johnson", "Mary", -250.50},
        {10, "Williams", "Bob", 3200.00},
        {25, "Davis", "Alice", 1000.00}
    };
    
    int num_samples = sizeof(sample_clients) / sizeof(sample_clients[0]);
    
    for (int i = 0; i < num_samples; i++) {
        // Write to position based on account number - 1
        int position = sample_clients[i].acct_num - 1;
        write_client_to_file(file_ptr, &sample_clients[i], position);
    }
    
    printf("\n3. File Statistics:\n");
    long file_size = get_file_size(file_ptr);
    int record_count = count_records(file_ptr);
    printf("   - Current file size: %ld bytes\n", file_size);
    printf("   - Active records: %d\n", record_count);
    printf("   - Empty slots: %d\n", MAX_ACCOUNTS - record_count);
    
    close_data_file(file_ptr);
    
    printf("\n4. Displaying File Contents:\n");
    display_file_contents();
    
    printf("\n5. Creating Text Report:\n");
    create_text_report();
    
    printf("\n6. File Position Demonstration:\n");
    file_ptr = open_data_file("rb");
    if (file_ptr != NULL) {
        struct client_data client;
        
        printf("   Reading specific positions:\n");
        
        // Read position 0 (account 1)
        if (read_client_from_file(file_ptr, &client, 0) && client.acct_num != 0) {
            printf("   Position 0: Account %u - %s %s\n", 
                   client.acct_num, client.first_name, client.last_name);
        }
        
        // Read position 24 (account 25)
        if (read_client_from_file(file_ptr, &client, 24) && client.acct_num != 0) {
            printf("   Position 24: Account %u - %s %s\n", 
                   client.acct_num, client.first_name, client.last_name);
        }
        
        close_data_file(file_ptr);
    }
}

/*
 * TESTING FUNCTIONS
 * Unit tests for file operations
 */

int test_file_creation(void) {
    printf("Test 1: File Creation... ");
    
    // Try to create a test file
    FILE* test_file = fopen("test_file.dat", "wb");
    if (test_file == NULL) {
        printf("FAILED - Could not create file\n");
        return 0;
    }
    
    fclose(test_file);
    
    // Check if file exists by opening for reading
    test_file = fopen("test_file.dat", "rb");
    if (test_file == NULL) {
        printf("FAILED - File was not created\n");
        return 0;
    }
    
    fclose(test_file);
    remove("test_file.dat");  // Clean up
    
    printf("PASSED\n");
    return 1;
}

int test_file_writing(void) {
    printf("Test 2: File Writing... ");
    
    FILE* file_ptr = open_data_file("wb+");
    if (file_ptr == NULL) {
        printf("FAILED - Could not open file\n");
        return 0;
    }
    
    struct client_data test_client = {99, "TestLast", "TestFirst", 123.45};
    
    if (!write_client_to_file(file_ptr, &test_client, 10)) {
        printf("FAILED - Could not write to file\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    close_data_file(file_ptr);
    printf("PASSED\n");
    return 1;
}

int test_file_reading(void) {
    printf("Test 3: File Reading... ");
    
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("FAILED - Could not open file\n");
        return 0;
    }
    
    // First write a test record
    struct client_data write_client = {88, "ReadTest", "User", 555.55};
    write_client_to_file(file_ptr, &write_client, 20);
    
    // Now read it back
    struct client_data read_client;
    if (!read_client_from_file(file_ptr, &read_client, 20)) {
        printf("FAILED - Could not read from file\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    // Verify data matches
    if (read_client.acct_num == 88 && 
        strcmp(read_client.last_name, "ReadTest") == 0 &&
        read_client.balance == 555.55) {
        printf("PASSED\n");
        close_data_file(file_ptr);
        return 1;
    } else {
        printf("FAILED - Data mismatch\n");
        close_data_file(file_ptr);
        return 0;
    }
}

int test_file_positioning(void) {
    printf("Test 4: File Positioning... ");
    
    FILE* file_ptr = open_data_file("rb+");
    if (file_ptr == NULL) {
        printf("FAILED - Could not open file\n");
        return 0;
    }
    
    // Write to different positions
    struct client_data client1 = {11, "First", "Client", 100.0};
    struct client_data client2 = {22, "Second", "Client", 200.0};
    
    write_client_to_file(file_ptr, &client1, 5);
    write_client_to_file(file_ptr, &client2, 15);
    
    // Read them back in reverse order
    struct client_data read_client;
    
    read_client_from_file(file_ptr, &read_client, 15);
    if (read_client.acct_num != 22) {
        printf("FAILED - Position 15 incorrect\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    read_client_from_file(file_ptr, &read_client, 5);
    if (read_client.acct_num != 11) {
        printf("FAILED - Position 5 incorrect\n");
        close_data_file(file_ptr);
        return 0;
    }
    
    close_data_file(file_ptr);
    printf("PASSED\n");
    return 1;
}

void run_all_tests(void) {
    int total_tests = 0;
    int passed_tests = 0;
    
    total_tests++; passed_tests += test_file_creation();
    total_tests++; passed_tests += test_file_writing();
    total_tests++; passed_tests += test_file_reading();
    total_tests++; passed_tests += test_file_positioning();
    
    printf("\nTest Results: %d/%d tests passed\n", passed_tests, total_tests);
    
    if (passed_tests == total_tests) {
        printf("✅ All file operation tests passed! Ready for Version 03.\n");
    } else {
        printf("❌ Some tests failed. Review file operations before proceeding.\n");
    }
}

/*
 * LEARNING EXERCISES FOR STUDENTS:
 * 
 * 1. Easy Level:
 *    - Modify create_text_report() to include account creation dates
 *    - Add a function to backup the data file
 *    - Create a function to calculate average account balance
 * 
 * 2. Medium Level:
 *    - Implement file compression for the text report
 *    - Add file locking to prevent concurrent access
 *    - Create a function to merge two data files
 * 
 * 3. Advanced Level:
 *    - Implement a transaction log system
 *    - Add data integrity checks (checksums)
 *    - Create an indexing system for faster searches
 * 
 * DEBUGGING TIPS:
 * - Always check return values of file operations
 * - Use ftell() to debug file positioning
 * - Print file sizes to verify write operations
 * - Use hexdump or binary editors to examine file contents
 * 
 * NEXT VERSION PREVIEW:
 * In Version 03, we'll learn:
 * - CRUD operations (Create, Read, Update, Delete)
 * - User input validation and sanitization
 * - Interactive record management
 * - Advanced error handling and recovery
 */