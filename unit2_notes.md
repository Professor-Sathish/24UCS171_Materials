# Control Structures and Data Processing in Python 🐍

## 1. Boolean Values and Comparisons 🎯

### Understanding Boolean Logic
Boolean values are the foundation of program control flow. They represent:
- `True`: Represents truth, success, or existence
- `False`: Represents falsehood, failure, or non-existence

### Key Concepts:
1. Everything in Python has a truth value
2. Zero values are generally False
3. Non-zero values are generally True
4. Empty containers are False

```python
# 👉 Interactive Example 1: Truth Values
def explore_truth_values():
    # Let's test different values
    test_values = [
        0,          # False
        1,          # True
        -1,         # True
        [],         # False (empty list)
        [1, 2],     # True (non-empty list)
        "",         # False (empty string)
        "hello",    # True (non-empty string)
        None,       # False
    ]
    
    for value in test_values:
        print(f"Value: {value:10} | Type: {type(value).__name__:10} | Boolean: {bool(value)}")

# 🎮 Try this!
explore_truth_values()
```

### Comparison Operators

```python
# 👉 Interactive Example 2: Comparison Operations
def comparison_demo():
    x = 5
    y = 10
    
    print("Given: x =", x, "and y =", y)
    print("\nComparison Results:")
    print(f"x == y: {x == y}  # Equal to")
    print(f"x != y: {x != y}  # Not equal to")
    print(f"x < y:  {x < y}   # Less than")
    print(f"x > y:  {x > y}   # Greater than")
    print(f"x <= y: {x <= y}  # Less than or equal to")
    print(f"x >= y: {x >= y}  # Greater than or equal to")
    
    # Chained comparisons
    print("\nChained Comparison:")
    z = 15
    print(f"Is {y} between {x} and {z}?")
    print(f"{x} < {y} < {z}: {x < y < z}")

# 🎮 Try this!
comparison_demo()
```

### Common Pitfalls and Best Practices
```python
# ⚠️ Common Mistakes:
# 1. Using = instead of ==
x = 5       # Assignment
x == 5      # Comparison

# 2. Comparing floating-point numbers directly
0.1 + 0.2 == 0.3    # False! Due to floating-point precision
abs((0.1 + 0.2) - 0.3) < 1e-10  # Better approach

# 3. Not understanding short-circuit evaluation
result = False and print("This won't print")
result = True or print("This won't print")
```

## 2. Conditional Execution 🔀

### Understanding Control Flow
Conditional statements allow your program to make decisions and execute different code based on conditions.

### Key Concepts:
1. Indentation is crucial
2. Conditions are evaluated top to bottom
3. Only the first true condition is executed
4. else is optional

```python
# 👉 Interactive Example 3: Grade Calculator
def calculate_grade(score):
    print(f"\nCalculating grade for score: {score}")
    print("Checking conditions:")
    
    if score >= 90:
        print("✓ Score is 90 or above")
        print("Result: A")
        return 'A'
    elif score >= 80:
        print("✓ Score is 80-89")
        print("Result: B")
        return 'B'
    elif score >= 70:
        print("✓ Score is 70-79")
        print("Result: C")
        return 'C'
    else:
        print("✗ Score is below 70")
        print("Result: F")
        return 'F'

# 🎮 Try these scores!
scores = [95, 85, 75, 65]
for score in scores:
    calculate_grade(score)
```

### Nested Conditions
```python
# 👉 Interactive Example 4: User Authentication
def check_access(username, age, is_admin):
    print(f"\nChecking access for user: {username}")
    print("Verifying credentials...")
    
    if age >= 18:
        print("✓ Age verification passed")
        if is_admin:
            print("✓ Admin status confirmed")
            print("Result: Full access granted")
            return "Full access"
        else:
            print("ℹ Regular user status")
            print("Result: Limited access granted")
            return "Limited access"
    else:
        print("✗ Age verification failed")
        print("Result: Access denied")
        return "No access"

# 🎮 Try different combinations!
test_cases = [
    ("Alice", 25, True),
    ("Bob", 20, False),
    ("Charlie", 16, False)
]

for username, age, is_admin in test_cases:
    check_access(username, age, is_admin)
```

## 3. Loops and Iterations 🔄

### Understanding Loops
Loops allow you to repeat code blocks efficiently. Python provides two main types:
1. for loops: Iterate over sequences
2. while loops: Continue while a condition is true

### Key Concepts:
1. Iteration variables
2. Loop control statements (break, continue)
3. Loop else clause
4. Nested loops

```python
# 👉 Interactive Example 5: Number Pattern
def print_pattern(rows):
    print(f"\nGenerating pattern for {rows} rows:")
    
    for i in range(1, rows + 1):
        # Print spaces
        print("  " * (rows - i), end="")
        
        # Print numbers
        for j in range(1, i + 1):
            print(f"{j:2}", end=" ")
            
        print()  # New line

# 🎮 Try different numbers of rows!
print_pattern(5)
```

### While Loop with Animation
```python
# 👉 Interactive Example 6: Loading Animation
import time

def loading_animation(duration):
    animation = "|/-\\"
    idx = 0
    start_time = time.time()
    
    while time.time() - start_time < duration:
        print(f"\rLoading {animation[idx % len(animation)]}", end="")
        idx += 1
        time.sleep(0.1)
    
    print("\rComplete!   ")

# 🎮 Try different durations!
loading_animation(3)  # 3 seconds
```

## 4. List Processing 📝

### Understanding Lists
Lists are versatile containers that can:
1. Hold multiple data types
2. Change in size
3. Be modified (mutable)
4. Be nested

### Key Concepts:
1. Indexing (positive and negative)
2. Slicing [start:end:step]
3. List methods
4. List comprehensions

```python
# 👉 Interactive Example 7: List Operations Visualizer
def visualize_list_operations():
    # Create a sample list
    numbers = [1, 2, 3, 4, 5]
    
    print("Original list:", numbers)
    print("\nList Operations:")
    
    # Append
    numbers.append(6)
    print("After append(6):", numbers)
    
    # Insert
    numbers.insert(0, 0)
    print("After insert(0, 0):", numbers)
    
    # Extend
    numbers.extend([7, 8])
    print("After extend([7, 8]):", numbers)
    
    # Remove
    numbers.remove(4)
    print("After remove(4):", numbers)
    
    # Pop
    popped = numbers.pop()
    print(f"After pop(): {numbers} (popped value: {popped})")
    
    # Slicing
    print("\nSlicing Examples:")
    print("First three:", numbers[:3])
    print("Last three:", numbers[-3:])
    print("Every second element:", numbers[::2])
    print("Reversed:", numbers[::-1])

# 🎮 Try it!
visualize_list_operations()
```

### Advanced List Processing
```python
# 👉 Interactive Example 8: List Comprehension Visualizer
def explain_list_comprehension():
    numbers = range(1, 11)
    
    # Different types of list comprehensions
    examples = [
        ("Basic", [x for x in numbers]),
        ("Squares", [x**2 for x in numbers]),
        ("Even numbers", [x for x in numbers if x % 2 == 0]),
        ("Even squares", [x**2 for x in numbers if x % 2 == 0]),
        ("Number pairs", [(x, y) for x in range(2) for y in range(2)]),
    ]
    
    print("List Comprehension Examples:")
    for name, result in examples:
        print(f"\n{name}:")
        print(f"Result: {result}")
        if name == "Number pairs":
            print("This creates all combinations of 0 and 1")

# 🎮 Try it!
explain_list_comprehension()
```

## 5. Logical and Bitwise Operations 🔣

### Understanding Bitwise Operations
Bitwise operations work with numbers at the bit level, useful for:
1. Flag operations
2. Memory efficient calculations
3. Hardware interaction
4. Optimization

```python
# 👉 Interactive Example 9: Bitwise Operations Visualizer
def visualize_bitwise_ops():
    a = 60  # 60 = 0011 1100
    b = 13  # 13 = 0000 1101
    
    print(f"a = {a} ({bin(a)[2:].zfill(8)})")
    print(f"b = {b} ({bin(b)[2:].zfill(8)})")
    print("\nBitwise Operations:")
    
    # AND
    result = a & b
    print(f"a & b  = {result} ({bin(result)[2:].zfill(8)})")
    
    # OR
    result = a | b
    print(f"a | b  = {result} ({bin(result)[2:].zfill(8)})")
    
    # XOR
    result = a ^ b
    print(f"a ^ b  = {result} ({bin(result)[2:].zfill(8)})")
    
    # NOT
    result = ~a
    print(f"~a     = {result} ({bin(result & 0xFF)[2:].zfill(8)})")
    
    # Left shift
    result = a << 2
    print(f"a << 2 = {result} ({bin(result)[2:].zfill(8)})")
    
    # Right shift
    result = a >> 2
    print(f"a >> 2 = {result} ({bin(result)[2:].zfill(8)})")

# 🎮 Try it!
visualize_bitwise_ops()
```

## Practice Exercises 🎯

1. **Grade Calculator with Validation**
```python
def advanced_grade_calculator():
    try:
        score = float(input("Enter score (0-100): "))
        if not 0 <= score <= 100:
            raise ValueError("Score must be between 0 and 100")
        
        # Calculate grade (implement this)
        # Add curve calculation
        # Add grade statistics
            
    except ValueError as e:
        print(f"Error: {e}")

# 🎮 Try it!
advanced_grade_calculator()
```

2. **Pattern Generator**
```python
def create_custom_pattern():
    size = int(input("Enter pattern size: "))
    pattern_type = input("Choose pattern type (triangle/square/diamond): ")
    
    # Implement different patterns based on input
    # Add color options
    # Add pattern variations

# 🎮 Try it!
create_custom_pattern()
```

3. **List Processor**
```python
def process_list():
    numbers = input("Enter numbers separated by spaces: ").split()
    numbers = [int(n) for n in numbers]
    
    # Add different processing options
    # Calculate statistics
    # Find patterns
    # Sort in different ways

# 🎮 Try it!
process_list()
```

## Common Pitfalls and Best Practices ⚠️

1. **Loop Control**
   - Always have a way to exit while loops
   - Be careful with infinite loops
   - Consider using enumerate() for counters

2. **List Operations**
   - Be aware of shallow vs deep copy
   - Use appropriate methods for modifications
   - Consider memory usage for large lists

3. **Conditional Statements**
   - Keep conditions simple and readable
   - Use compound conditions carefully
   - Consider edge cases
