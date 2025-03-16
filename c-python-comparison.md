# C vs Python Syntax Comparison

| Feature | C | Python |
|---------|---|--------|
| **Program Structure** | Requires main() function, includes headers | No main() required, uses modules/imports |
| **Line Ending** | Semicolon `;` required | No semicolon needed |
| **Code Blocks** | Curly braces `{ }` | Indentation (whitespace) |
| **Comments** | `// Single line` or `/* Multi-line */` | `# Single line` or `''' Multi-line '''` |
| **Variables** | Static typing (must declare type) | Dynamic typing (type inferred) |
| **Variable Declaration** | `int x = 5;` | `x = 5` |
| **Constants** | `const int MAX = 100;` | `MAX = 100` (by convention uppercase) |
| **Output** | `printf("Hello %d\n", num);` | `print(f"Hello {num}")` |
| **Input** | `scanf("%d", &num);` | `num = input()` or `num = int(input())` |

## Data Types

| C | Python |
|---|--------|
| `int x = 5;` | `x = 5` |
| `float y = 3.14;` | `y = 3.14` |
| `char c = 'A';` | `c = 'A'` |
| `char str[10] = "hello";` | `s = "hello"` |
| `int arr[5] = {1, 2, 3, 4, 5};` | `arr = [1, 2, 3, 4, 5]` |
| No direct equivalent | `my_tuple = (1, 2, 3)` |
| No direct equivalent | `my_dict = {"key": "value"}` |
| No direct equivalent | `my_set = {1, 2, 3}` |

## Control Structures

### Conditionals

**C:**
```c
if (x > 0) {
    printf("Positive");
} else if (x < 0) {
    printf("Negative");
} else {
    printf("Zero");
}
```

**Python:**
```python
if x > 0:
    print("Positive")
elif x < 0:
    print("Negative")
else:
    print("Zero")
```

### Loops

**C For Loop:**
```c
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}
```

**Python For Loop:**
```python
for i in range(10):
    print(i, end=" ")
```

**C While Loop:**
```c
int i = 0;
while (i < 10) {
    printf("%d ", i);
    i++;
}
```

**Python While Loop:**
```python
i = 0
while i < 10:
    print(i, end=" ")
    i += 1
```

**C Do-While Loop:**
```c
int i = 0;
do {
    printf("%d ", i);
    i++;
} while (i < 10);
```

**Python (No Do-While):**
```python
i = 0
while True:
    print(i, end=" ")
    i += 1
    if i >= 10:
        break
```

## Functions

**C:**
```c
int add(int a, int b) {
    return a + b;
}

// Call
int result = add(5, 3);
```

**Python:**
```python
def add(a, b):
    return a + b

# Call
result = add(5, 3)
```

## Memory Management

**C:**
```c
// Manual memory allocation
int *arr = (int*) malloc(10 * sizeof(int));
// Use array
// ...
// Must free memory
free(arr);
```

**Python:**
```python
# Automatic memory management
arr = [0] * 10
# Use array
# ...
# Garbage collector handles memory
```

## Error Handling

**C:**
```c
if (file == NULL) {
    fprintf(stderr, "Error opening file\n");
    return 1;
}
```

**Python:**
```python
try:
    file = open("filename.txt", "r")
    # Process file
except FileNotFoundError:
    print("Error opening file")
finally:
    file.close()
```

## Structs vs Classes

**C:**
```c
struct Point {
    int x;
    int y;
};

struct Point p1 = {10, 20};
printf("%d, %d\n", p1.x, p1.y);
```

**Python:**
```python
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

p1 = Point(10, 20)
print(f"{p1.x}, {p1.y}")
```

## String Handling

**C:**
```c
char str[20] = "Hello";
strcat(str, " World");  // Concatenate
printf("%s\n", str);
printf("Length: %d\n", strlen(str));
```

**Python:**
```python
s = "Hello"
s += " World"  # Concatenate
print(s)
print(f"Length: {len(s)}")
```

## File Operations

**C:**
```c
FILE *file = fopen("data.txt", "r");
if (file != NULL) {
    char buffer[100];
    while (fgets(buffer, 100, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}
```

**Python:**
```python
with open("data.txt", "r") as file:
    for line in file:
        print(line, end="")
```
