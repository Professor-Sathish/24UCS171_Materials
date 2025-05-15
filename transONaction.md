# C Programming Concepts Using a Bank Account Program

## UNIT IV — Structures and Unions

### 1. Structure Declaration
A structure groups different data types under one name.
```c
struct client_data {
    unsigned int acct_num;
    char last_name[15];
    char first_name[10];
    double balance;
};
```

### 2. Nested Structures
A structure can contain another structure.
```c
struct full_name {
    char first[10];
    char last[15];
};

struct client_data {
    unsigned int acct_num;
    struct full_name name;
    double balance;
};
```

### 3. Pointer and Structures
Access structure members using pointers:
```c
struct client_data *ptr = &client;
printf("%s", ptr->first_name);
```
Used in file I/O:
```c
fread(&client, sizeof(struct client_data), 1, f_ptr);
```

### 4. Array of Structures
Used to manage multiple records:
```c
struct client_data clients[MAX_RECORDS];
```
Used in `sort_records()`.

### 5. Self-Referential Structures
Used for linked lists:
```c
struct Node {
    struct client_data client;
    struct Node *next;
};
```

### 6. Singly Linked List (Custom Implementation)
```c
struct Node* create_node(struct client_data c) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->client = c;
    new_node->next = NULL;
    return new_node;
}
```
Insert, search, and delete operations can be implemented on the list.

### 7. Union Example
```c
union mixed_data {
    int i;
    float f;
    char str[20];
};

union mixed_data data;
data.i = 10;
printf("%d", data.i);
```
Unions store only one of the members at a time.

### 8. Storage Classes
- `auto`: default for local vars
- `register`: suggests using CPU register
- `static`: retains value
- `extern`: global variable access

---

## UNIT V — File Processing

### 1. Files in C
```c
FILE *cf_ptr = fopen("credit.dat", "rb+");
```
- `rb+`: read/write binary

### 2. Types of File Access
- **Sequential**: one after another
- **Random**: jump to specific position

### 3. Sequential Access
Used in:
```c
text_file()
```
```c
while (!feof(read_ptr)) {
    fread(&client, sizeof(struct client_data), 1, read_ptr);
}
```

### 4. Average of Numbers (Example)
```c
FILE *fp = fopen("nums.txt", "r");
int num, total = 0, count = 0;
while (fscanf(fp, "%d", &num) != EOF) {
    total += num;
    count++;
}
printf("Average: %.2f\n", (float)total/count);
```

### 5. Random Access
```c
fseek(f_ptr, (account_num - 1) * sizeof(struct client_data), SEEK_SET);
```
Used in record creation, deletion, and updates.

### 6. Transaction Processing
In `update_record()`:
- Read
- Modify
- Write back

### 7. Command-Line Arguments
```c
int main(int argc, char *argv[])
```
Used to get program name:
```c
printf("%s: File could not be opened.\n", argv[0]);
```
Can be extended to use `argv[1]` as file name:
```c
FILE *cf_ptr = fopen(argv[1], "rb+");
```

---

## Summary Table

| Concept               | Example                     | Notes                             |
|----------------------|-----------------------------|-----------------------------------|
| `struct`             | `client_data`               | Groups account details            |
| Pointer to struct    | `&client`, `->`             | Used in file operations           |
| Array of structs     | `clients[MAX_RECORDS]`      | Used in sorting                   |
| File handling        | `fopen`, `fread`, `fseek`   | Binary and text files             |
| Random access        | `fseek()`                   | Direct file record manipulation   |
| Text output          | `accounts.txt`              | For formatted readable output     |
| Sorting              | `qsort()`                   | Sorted by balance                 |
| Command-line args    | `argv[0]`, `argv[1]`        | File selection at runtime         |
| Union                | `union mixed_data`          | Shared memory for efficiency      |
| Linked list          | `Node* next`                | Dynamic record structures         |

---

## Diagrams and Visual Aids

```
Memory Layout:
+-------------+-------------+-------------+-------------+
| Acct#      | Last Name   | First Name  | Balance     |
+-------------+-------------+-------------+-------------+

File Layout:
[Record 1][Record 2][Record 3] ... [Record N]

Linked List:
[client] -> [client] -> [client] -> NULL
```

---

## Assignments and Practice Tasks

1. **Add Union Support**:
   Modify the program to use a union for balance vs. status message.

2. **Implement Linked List**:
   Create an alternative structure to maintain accounts in memory.

3. **Enhance CLI**:
   Allow passing the filename via command-line instead of hardcoding.

4. **Export Sorted Data**:
   After sorting, write sorted data to a new file.

5. **Graphical View**:
   Display balance bar chart using external tools or libraries.
