# Python Functions: A Comprehensive Guide

## 1. Functions Fundamentals 🎯

### What is a Function?
A function is a reusable block of code that performs a specific task. Functions help in:
- Organizing code into manageable chunks
- Avoiding code repetition (DRY - Don't Repeat Yourself)
- Making code more readable and maintainable

### Important Concepts:
1. **Function Definition**: Using the `def` keyword
2. **Parameters**: Input values the function accepts
3. **Return Values**: Output the function provides
4. **Docstrings**: Documentation strings explaining the function
5. **Scope**: Where variables can be accessed

### Notes on Scope:
- **Local Scope**: Variables defined inside a function
- **Global Scope**: Variables defined outside functions
- **LEGB Rule**: Local → Enclosing → Global → Built-in

```python
# Example demonstrating scope
global_var = "I'm global"

def scope_example():
    local_var = "I'm local"
    print(local_var)    # Accessible
    print(global_var)   # Accessible

# print(local_var)      # Would raise Error - local_var not accessible here
print(global_var)       # Accessible

# Best Practices for Function Definitions:
def calculate_area(length: float, width: float) -> float:
    """
    Calculate the area of a rectangle.
    
    Args:
        length (float): The length of the rectangle
        width (float): The width of the rectangle
    
    Returns:
        float: The area of the rectangle
    """
    return length * width
```

### Common Pitfalls:
1. Forgetting to return a value
2. Modifying global variables (avoid this)
3. Using mutable default arguments
4. Not handling edge cases

## 2. Default and Keyword Arguments 🔑

### Understanding Parameter Types:
1. **Required Parameters**: Must be provided
2. **Default Parameters**: Have preset values
3. **Keyword Arguments**: Specified by name
4. **Positional Arguments**: Specified by position

### Important Notes:
- Default parameters must come after required parameters
- Default values are evaluated only once at function definition
- Mutable default values can cause unexpected behavior

```python
# Good Practice
def create_user(name, age, city="Unknown", active=True):
    return {"name": name, "age": age, "city": city, "active": active}

# Bad Practice - Mutable Default Argument
def add_to_list(item, my_list=[]):  # Don't do this!
    my_list.append(item)
    return my_list

# Better Practice
def add_to_list(item, my_list=None):
    if my_list is None:
        my_list = []
    my_list.append(item)
    return my_list
```

## 3. Variable-Length Arguments 📚

### Understanding *args and **kwargs:
1. **args**: Collects positional arguments into a tuple
2. **kwargs**: Collects keyword arguments into a dictionary

### When to Use:
- *args: When number of positional arguments is unknown
- **kwargs: When number of keyword arguments is unknown
- Both: For creating flexible function interfaces

```python
def flexible_function(*args, **kwargs):
    """
    Example of flexible function arguments.
    
    Args:
        *args: Variable positional arguments
        **kwargs: Variable keyword arguments
    """
    print("Positional arguments:", args)
    print("Keyword arguments:", kwargs)

# Different ways to use
flexible_function(1, 2, 3, name="John", age=25)
flexible_function()  # Both args and kwargs can be empty
```

### Best Practices:
1. Use meaningful parameter names
2. Document expected arguments
3. Validate argument types when necessary
4. Keep the number of parameters manageable

## 4. Lambda Functions (Anonymous Functions) 🎯

### What are Lambda Functions?
- Single-expression functions
- Anonymous (unnamed) functions
- Useful for short operations

### When to Use Lambda Functions:
1. As arguments to higher-order functions
2. For simple operations
3. In list comprehensions and map/filter operations

### When NOT to Use Lambda Functions:
1. For complex operations
2. When function needs documentation
3. When function is reused multiple times

```python
# Good Lambda Use
sorted_names = sorted(names, key=lambda x: x.lower())

# Bad Lambda Use (Should be a regular function)
complex_operation = lambda x, y: (x**2 + y**2) * sum([i for i in range(x)])
```

## 5. Functional Programming Tools 🛠️

### Map, Filter, and Reduce:
1. **map()**: Transform each element
2. **filter()**: Select elements based on condition
3. **reduce()**: Aggregate elements to single value

### Important Notes:
- map() and filter() return iterators
- Performance considerations vs. list comprehensions
- Consider readability when choosing approach

```python
# Map Examples with Explanation
numbers = [1, 2, 3, 4, 5]

# Using map
squared_map = map(lambda x: x**2, numbers)

# Equivalent list comprehension (often more readable)
squared_comp = [x**2 for x in numbers]

# Filter Examples
evens_filter = filter(lambda x: x % 2 == 0, numbers)

# Equivalent list comprehension
evens_comp = [x for x in numbers if x % 2 == 0]
```

## 6. Iterators and Generators ⚡

### Understanding Iteration:
1. **Iterator Protocol**: __iter__ and __next__ methods
2. **Generator Functions**: Using yield statement
3. **Generator Expressions**: Inline generators

### Benefits:
- Memory efficient
- Lazy evaluation
- Perfect for large datasets

```python
# Generator Function Example
def number_generator(start, end):
    """
    Generate numbers from start to end.
    Memory efficient as it yields one value at a time.
    """
    current = start
    while current <= end:
        yield current
        current += 1

# Generator Expression
squares = (x**2 for x in range(1000000))  # Memory efficient
```

### Best Practices:
1. Use generators for large sequences
2. Consider memory usage
3. Handle StopIteration appropriately

## 7. List Comprehensions 📝

### Understanding List Comprehensions:
- Concise way to create lists
- More readable than loops
- Can include conditions

### Syntax Patterns:
1. Basic: [expression for item in iterable]
2. Filtered: [expression for item in iterable if condition]
3. Nested: [expression for x in iterable1 for y in iterable2]

```python
# Simple List Comprehension
squares = [x**2 for x in range(10)]

# With Condition
even_squares = [x**2 for x in range(10) if x % 2 == 0]

# Nested Comprehension
matrix = [[i+j for j in range(3)] for i in range(3)]
```

### When to Use:
1. Simple transformations
2. Filtering elements
3. Creating new lists from existing ones

### When NOT to Use:
1. Complex operations
2. Multiple conditions
3. Side effects needed

## Common Pitfalls and Solutions 🚫

1. **Mutable Default Arguments**
```python
# Problem
def add_user(name, users=[]):  # DON'T DO THIS
    users.append(name)
    return users

# Solution
def add_user(name, users=None):
    if users is None:
        users = []
    users.append(name)
    return users
```

2. **Variable Scope Issues**
```python
# Problem
total = 0
def add_to_total(value):
    total += value  # UnboundLocalError

# Solution
def add_to_total(value):
    global total
    total += value
```

3. **Generator Exhaustion**
```python
# Problem
gen = (x for x in range(3))
list(gen)  # [0, 1, 2]
list(gen)  # [] - Generator is exhausted

# Solution
def get_generator():
    return (x for x in range(3))

gen1 = get_generator()
gen2 = get_generator()
```

## Best Practices Summary 📌

1. **Function Design**
   - Keep functions small and focused
   - Use clear, descriptive names
   - Document with docstrings
   - Handle edge cases

2. **Parameters**
   - Limit number of parameters
   - Use type hints
   - Validate inputs
   - Use default values appropriately

3. **Returns**
   - Be consistent with return types
   - Document return values
   - Consider using named tuples for multiple returns

4. **Error Handling**
   - Use try/except appropriately
   - Raise specific exceptions
   - Document possible exceptions

5. **General Tips**
   - Follow PEP 8 style guide
   - Write testable functions
   - Avoid side effects
   - Use meaningful variable names

## Practice Exercises 🎯

1. **Basic Function Practice**
```python
def calculate_statistics(numbers):
    """
    Calculate basic statistics for a list of numbers.
    Practice: Add median, mode, and range calculations.
    """
    pass  # Your implementation here
```

2. **Advanced Parameter Handling**
```python
def process_data(*args, **kwargs):
    """
    Process different types of data based on input.
    Practice: Add type checking and validation.
    """
    pass  # Your implementation here
```

3. **Generator Practice**
```python
def fibonacci_generator(n):
    """
    Generate Fibonacci sequence.
    Practice: Add error handling and validation.
    """
    pass  # Your implementation here
```

