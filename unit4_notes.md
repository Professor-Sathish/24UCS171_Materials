# Python File Operations, Exceptions, and Modules

## 1. File Handling in Python

### Topic Overview
- Reading and writing text files
- Different file modes
- File operations and methods
- Context managers (with statement)

### Explanation
File handling in Python allows you to work with external files for reading and writing data. Files can be opened in different modes:
- 'r': Read (default)
- 'w': Write (overwrites)
- 'a': Append
- 'x': Exclusive creation
- 'b': Binary mode
- 't': Text mode (default)
- '+': Read and write

### Syntax and Examples

```python
# Reading a file
def read_file(filename):
    with open(filename, 'r') as file:
        content = file.read()
    return content

# Reading lines from a file
def read_lines(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    return lines

# Writing to a file
def write_file(filename, content):
    with open(filename, 'w') as file:
        file.write(content)

# Appending to a file
def append_to_file(filename, content):
    with open(filename, 'a') as file:
        file.write(content)

# Practical Example: Log File Creator
from datetime import datetime

def create_log_entry(message):
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    return f'[{timestamp}] {message}\n'

def add_log_entry(filename, message):
    log_entry = create_log_entry(message)
    try:
        with open(filename, 'a') as file:
            file.write(log_entry)
        return True
    except IOError as e:
        print(f"Error writing to log: {e}")
        return False

# Usage
add_log_entry('app.log', 'Server started')
add_log_entry('app.log', 'User login successful')
```

## 2. Working with Zip Files

### Topic Overview
- Compressing files and directories
- Extracting zip files
- Managing zip archive contents

### Explanation
Python's zipfile module provides tools for creating, reading, writing, and extracting zip files. This is useful for:
- Reducing file sizes
- Bundling multiple files together
- Creating backups
- Distributing applications

### Syntax and Examples

```python
import zipfile
import os
from datetime import datetime

# Create a zip file from a list of files
def create_zip(zip_filename, files_list):
    try:
        with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
            for file in files_list:
                if os.path.exists(file):
                    zipf.write(file)
        return True
    except Exception as e:
        print(f"Error creating zip: {e}")
        return False

# Extract all files from a zip
def extract_zip(zip_filename, extract_path):
    try:
        with zipfile.ZipFile(zip_filename, 'r') as zipf:
            zipf.extractall(extract_path)
        return True
    except Exception as e:
        print(f"Error extracting zip: {e}")
        return False

# Practical Example: Backup Creator
def create_backup(source_dir):
    timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    zip_filename = f'backup_{timestamp}.zip'
    
    try:
        with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
            for root, _, files in os.walk(source_dir):
                for file in files:
                    file_path = os.path.join(root, file)
                    arc_name = os.path.relpath(file_path, source_dir)
                    zipf.write(file_path, arc_name)
        return zip_filename
    except Exception as e:
        print(f"Backup failed: {e}")
        return None
```

## 3. Exception Handling

### Topic Overview
- Try-except blocks
- Multiple except clauses
- Else and finally blocks
- Raising exceptions
- Error handling patterns

### Explanation
Exception handling allows you to handle errors and unexpected situations in your code. Python provides a comprehensive try-except mechanism with additional else and finally blocks.

### Syntax and Examples

```python
# Basic exception handling
def divide_numbers(a, b):
    try:
        result = a / b
    except ZeroDivisionError:
        print("Error: Division by zero!")
        return None
    except TypeError:
        print("Error: Invalid number type!")
        return None
    else:
        return result
    finally:
        print("Division operation completed")

# Handling multiple exceptions
def process_data(filename):
    try:
        with open(filename, 'r') as file:
            data = file.read()
            numbers = [int(x) for x in data.split()]
            return sum(numbers) / len(numbers)
    except FileNotFoundError:
        print(f"Error: File {filename} not found")
    except ValueError:
        print("Error: File contains invalid numbers")
    except ZeroDivisionError:
        print("Error: File is empty")
    except Exception as e:
        print(f"Unexpected error: {e}")
    return None

# Raising exceptions
def validate_age(age):
    if not isinstance(age, (int, float)):
        raise TypeError("Age must be a number")
    if age < 0:
        raise ValueError("Age cannot be negative")
    if age > 150:
        raise ValueError("Age is unrealistic")
    return True
```

## 4. Modules and Packages

### Topic Overview
- Importing modules
- Creating packages
- Using __init__.py
- Standard library modules
- Package structure and organization

### Explanation
Modules and packages help organize code into reusable components. A module is a single file containing Python code, while a package is a directory containing multiple modules and an __init__.py file.

### Package Structure Example
```
data_processing/
    __init__.py
    file_handlers.py
    data_transform.py
    utils/
        __init__.py
        validators.py
```

### Syntax and Examples

```python
# file_handlers.py
def read_csv(filename):
    data = []
    with open(filename, 'r') as file:
        for line in file:
            data.append(line.strip().split(','))
    return data

def save_csv(filename, data):
    with open(filename, 'w') as file:
        for row in data:
            file.write(','.join(map(str, row)) + '\n')

# data_transform.py
def clean_data(data):
    return [row for row in data if all(cell.strip() for cell in row)]

def transform_numbers(data, column_index):
    return [[float(row[column_index]) if i == column_index else cell 
             for i, cell in enumerate(row)] for row in data]

# utils/validators.py
def is_valid_file(filename):
    return filename.endswith('.csv')

def is_valid_data(data):
    return all(len(row) == len(data[0]) for row in data)

# Using the package
from data_processing.file_handlers import read_csv, save_csv
from data_processing.data_transform import clean_data, transform_numbers
from data_processing.utils.validators import is_valid_file

def process_csv_file(input_file, output_file):
    if not is_valid_file(input_file):
        return "Invalid file format"
    
    data = read_csv(input_file)
    if not is_valid_data(data):
        return "Invalid data structure"
    
    cleaned_data = clean_data(data)
    transformed_data = transform_numbers(cleaned_data, 1)
    save_csv(output_file, transformed_data)
    return "Processing completed"
```

## Best Practices and Tips

1. File Handling:
   - Use context managers (with statements)
   - Handle file encodings properly
   - Close files explicitly if not using with
   - Use appropriate file modes

2. Zip Files:
   - Check available disk space before extracting
   - Use appropriate compression levels
   - Handle large files in chunks
   - Validate zip contents before extraction

3. Exception Handling:
   - Catch specific exceptions
   - Avoid bare except clauses
   - Use finally for cleanup
   - Raise appropriate exceptions

4. Modules and Packages:
   - Use meaningful function names
   - Keep functions focused and single-purpose
   - Document function usage
   - Use relative imports within packages
