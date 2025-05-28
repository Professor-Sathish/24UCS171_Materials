// Bank-account program reads a random-access file sequentially,
// updates data already written to the file, creates new data to
// be placed in the file, and deletes data previously in the file.
#include <stdio.h>
#include <stdlib.h>
// client_data structure definition
struct client_data
{
    unsigned int acct_num; // account number
    char last_name[15];    // account last name
    char first_name[10];   // account first name
    double balance;       // account balance
};                        // end structure client_data

#define MAX_RECORDS 150

// prototypes
unsigned int enter_choice(void);
void text_file(FILE *read_ptr);
void update_record(FILE *f_ptr);
void new_record(FILE *f_ptr);
void delete_record(FILE *f_ptr);
void sort_records(FILE *f_ptr);
void display_client_data(const struct client_data clients[], int size);

int main(int argc, char *argv[])
{
    FILE *cf_ptr;         // credit.dat file pointer
    unsigned int choice; // user's choice

    // fopen opens the file; exits if file cannot be opened
    if ((cf_ptr = fopen("credit.dat", "rb+")) == NULL)
    {
        printf("%s: File could not be opened.\n", argv[0]);
        exit(-1);
    }

    // enable user to specify action
    while ((choice = enter_choice()) != 6)
    {
        switch (choice)
        {
        // create text file from record file
        case 1:
            text_file(cf_ptr);
            break;
        // update record
        case 2:
            update_record(cf_ptr);
            break;
        // create record
        case 3:
            new_record(cf_ptr);
            break;
        // delete existing record
        case 4:
            delete_record(cf_ptr);
            break;
        case 5:
            sort_records(cf_ptr);
            break;
        default:
            puts("Incorrect choice");
            break;
        } // end switch
    }     // end while

    fclose(cf_ptr); // fclose closes the file
} // end main

// create formatted text file for printing
void text_file(FILE *read_ptr)
{
    FILE *write_ptr; // accounts.txt file pointer
    int result;     // used to test whether fread read any bytes
    // create client_data with default information
    struct client_data client = {0, "", "", 0.0};

    // fopen opens the file; exits if file cannot be opened
    if ((write_ptr = fopen("accounts.txt", "w")) == NULL)
    {
        puts("File could not be opened.");
    } // end if
    else
    {
        rewind(read_ptr); // sets pointer to beginning of file
        fprintf(write_ptr, "%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

        // copy all records from random-access file into text file
        while (!feof(read_ptr))
        {
            result = fread(&client, sizeof(struct client_data), 1, read_ptr);

            // write single record to text file
            if (result != 0 && client.acct_num != 0)
            {
                fprintf(write_ptr, "%-6d%-16s%-11s%10.2f\n", client.acct_num, client.last_name, client.first_name,
                        client.balance);
            } // end if
        }     // end while

        fclose(write_ptr); // fclose closes the file
    }                     // end else
} // end function text_file

// update balance in record
void update_record(FILE *f_ptr)
{
    unsigned int account; // account number
    double transaction;   // transaction amount
    // create client_data with no information
    struct client_data client = {0, "", "", 0.0};

    // obtain number of account to update
    printf("%s", "Enter account to update ( 1 - 100 ): ");
    scanf("%d", &account);

    // move file pointer to correct record in file
    fseek(f_ptr, (account - 1) * sizeof(struct client_data), SEEK_SET);
    // read record from file
    fread(&client, sizeof(struct client_data), 1, f_ptr);
    // display error if account does not exist
    if (client.acct_num == 0)
    {
        printf("Account #%d has no information.\n", account);
    }
    else
    { // update record
        printf("%-6d%-16s%-11s%10.2f\n\n", client.acct_num, client.last_name, client.first_name, client.balance);

        // request transaction amount from user
        printf("%s", "Enter charge ( + ) or payment ( - ): ");
        scanf("%lf", &transaction);
        client.balance += transaction; // update record balance

        printf("%-6d%-16s%-11s%10.2f\n", client.acct_num, client.last_name, client.first_name, client.balance);

        // move file pointer to correct record in file
        // move back by 1 record length
        fseek(f_ptr, -sizeof(struct client_data), SEEK_CUR);
        // write updated record over old record in file
        fwrite(&client, sizeof(struct client_data), 1, f_ptr);
    } // end else
} // end function update_record

// delete an existing record
void delete_record(FILE *f_ptr)
{
    struct client_data client;                       // stores record read from file
    struct client_data blank_client = {0, "", "", 0}; // blank client
    unsigned int account_num;                        // account number

    // obtain number of account to delete
    printf("%s", "Enter account number to delete ( 1 - 100 ): ");
    scanf("%d", &account_num);

    // move file pointer to correct record in file
    fseek(f_ptr, (account_num - 1) * sizeof(struct client_data), SEEK_SET);
    // read record from file
    fread(&client, sizeof(struct client_data), 1, f_ptr);
    // display error if record does not exist
    if (client.acct_num == 0)
    {
        printf("Account %d does not exist.\n", account_num);
    } // end if
    else
    { // delete record
        // move file pointer to correct record in file
        fseek(f_ptr, (account_num - 1) * sizeof(struct client_data), SEEK_SET);
        // replace existing record with blank record
        fwrite(&blank_client, sizeof(struct client_data), 1, f_ptr);
    } // end else
} // end function delete_record

// create and insert record
void new_record(FILE *f_ptr)
{
    // create client_data with default information
    struct client_data client = {0, "", "", 0.0};
    unsigned int account_num; // account number

    // obtain number of account to create
    printf("%s", "Enter new account number ( 1 - 100 ): ");
    scanf("%d", &account_num);

    // move file pointer to correct record in file
    fseek(f_ptr, (account_num - 1) * sizeof(struct client_data), SEEK_SET);
    // read record from file
    fread(&client, sizeof(struct client_data), 1, f_ptr);
    // display error if account already exists
    if (client.acct_num != 0)
    {
        printf("Account #%d already contains information.\n", client.acct_num);
    } // end if
    else
    { // create record
        // user enters last name, first name and balance
        printf("%s", "Enter lastname, firstname, balance\n? ");
        scanf("%14s%9s%lf", client.last_name, client.first_name, &client.balance);

        client.acct_num = account_num;
        // move file pointer to correct record in file
        fseek(f_ptr, (client.acct_num - 1) * sizeof(struct client_data), SEEK_SET);
        // insert record in file
        fwrite(&client, sizeof(struct client_data), 1, f_ptr);
    } // end else
} // end function new_record

// display client data
void display_client_data(const struct client_data clients[], int size)
{
    printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");
    for (int i = 0; i < size; i++)
    {
        printf("%-6d%-16s%-11s%10.2f\n", clients[i].acct_num, clients[i].last_name, clients[i].first_name, clients[i].balance);
    }
} // end function display_client_data

// comparison function for qsort
int compare_accounts(const void *a, const void *b)
{
    struct client_data *client_a = (struct client_data *)a;
    struct client_data *client_b = (struct client_data *)b;
    return (client_b->balance - client_a->balance);
}

// sort records in file
void sort_records(FILE *f_ptr)
{
    struct client_data clients[MAX_RECORDS]; // assuming a maximum of 100 records
    struct client_data temp; // temporary struct for swapping
    int count = 0, result = 0;

    // read records into array
    rewind(f_ptr);
    while (!feof(f_ptr) && count < MAX_RECORDS)
    {
        result = fread(&clients[count], sizeof(struct client_data), 1, f_ptr);
        if (result && clients[count].acct_num != 0) // only count valid records
        {
            count++;
        }
    }
           
    // sort the array using qsort 
    if (count > 0) {
        // display records before sorting
        printf("\nRecords before sorting:\n");
        display_client_data(clients, count);

        // sort the array using qsort
        qsort(clients, count, sizeof(struct client_data), compare_accounts);

        // display records after sorting
        printf("\nRecords after sorting:\n");
        display_client_data(clients, count);
    }
    
    printf("Records sorted successfully.\n");
} // end function sortRecords


// function to prompt for user choice
unsigned int enter_choice(void)
{
    unsigned int menuChoice; // variable to store user's choice
    // display available options
    printf("%s", "\nEnter your choice\n"
                 "1 - store a formatted text file of accounts called\n"
                 "    \"accounts.txt\" for printing\n"
                 "2 - update an account\n"
                 "3 - add a new account\n"
                 "4 - delete an account\n"
                 "5 - sort records\n"
                 "6 - end program\n? ");
                
    scanf("%u", &menuChoice); // receive choice from user
    return menuChoice;
} // end function enterChoice