# Python Modules Guide: OS, Datetime, JSON, NumPy, and Pandas

## 1. OS Module 🗂️

### What is the OS Module?
The OS module helps you work with your computer's files and folders, just like you would in File Explorer or Finder:
- Create and delete folders
- List files in directories
- Get file information
- Work with system paths
- Access environment variables

### Example 1: File and Directory Management
```python
import os

def explore_directory(path):
    # List everything in the directory
    print("Contents of directory:")
    for item in os.listdir(path):
        # Get full path
        full_path = os.path.join(path, item)
        # Check if it's a file or directory
        if os.path.isfile(full_path):
            print(f"📄 File: {item}")
        else:
            print(f"📁 Folder: {item}")

# Usage
explore_directory("./my_documents")
```

### Example 2: Creating a Project Directory Structure
```python
import os

def create_project_structure(project_name):
    # Main project directory
    os.makedirs(project_name, exist_ok=True)
    
    # Create subdirectories
    folders = ['data', 'docs', 'src', 'tests']
    for folder in folders:
        folder_path = os.path.join(project_name, folder)
        os.makedirs(folder_path, exist_ok=True)
        print(f"Created: {folder_path}")
    
    # Create initial files
    files = {
        'README.md': '# ' + project_name,
        'requirements.txt': 'python>=3.8',
        'src/__init__.py': ''
    }
    
    for file_path, content in files.items():
        full_path = os.path.join(project_name, file_path)
        with open(full_path, 'w') as f:
            f.write(content)
        print(f"Created: {full_path}")

# Usage
create_project_structure("my_cool_project")
```

### Example 3: File Information and Environment Variables
```python
import os
from datetime import datetime

def get_file_info(filename):
    try:
        # Get file stats
        stats = os.stat(filename)
        
        print(f"File Information for: {filename}")
        print(f"Size: {stats.st_size} bytes")
        print(f"Created: {datetime.fromtimestamp(stats.st_ctime)}")
        print(f"Last modified: {datetime.fromtimestamp(stats.st_mtime)}")
        
        # Get environment variables
        print("\nEnvironment Variables:")
        print(f"Python Path: {os.getenv('PYTHONPATH')}")
        print(f"User Home: {os.getenv('HOME')}")
        
    except FileNotFoundError:
        print(f"File {filename} not found!")

# Usage
get_file_info("example.txt")
```

## 2. Datetime Module 📅

### What is the Datetime Module?
The Datetime module helps you work with dates and times:
- Get current date and time
- Create specific dates
- Calculate time differences
- Format dates for display

### Example 1: Basic Date Operations
```python
from datetime import datetime, timedelta

def date_calculator():
    # Get current date and time
    now = datetime.now()
    print(f"Current date and time: {now}")
    
    # Add 7 days
    next_week = now + timedelta(days=7)
    print(f"Next week: {next_week}")
    
    # Subtract 30 days
    last_month = now - timedelta(days=30)
    print(f"30 days ago: {last_month}")
    
    # Format dates nicely
    print(f"Today is: {now.strftime('%A, %B %d, %Y')}")
    print(f"Time now: {now.strftime('%I:%M %p')}")

# Usage
date_calculator()
```

### Example 2: Event Countdown Timer
```python
from datetime import datetime

def countdown_to_event(event_name, event_date_str):
    try:
        # Convert string to date
        event_date = datetime.strptime(event_date_str, '%Y-%m-%d')
        
        # Calculate days remaining
        days_left = (event_date - datetime.now()).days
        
        if days_left > 0:
            print(f"📅 {days_left} days until {event_name}!")
        elif days_left == 0:
            print(f"🎉 {event_name} is today!")
        else:
            print(f"⏰ {event_name} was {abs(days_left)} days ago!")
            
    except ValueError:
        print("Please use YYYY-MM-DD format for the date!")

# Usage
countdown_to_event("Birthday Party", "2024-12-31")
countdown_to_event("Summer Vacation", "2024-06-15")
```

### Example 3: Age Calculator
```python
from datetime import datetime

def calculate_age(birthdate_str):
    try:
        # Parse birthdate
        birthdate = datetime.strptime(birthdate_str, '%Y-%m-%d')
        today = datetime.now()
        
        # Calculate age
        age = today.year - birthdate.year - ((today.month, today.day) < 
                                           (birthdate.month, birthdate.day))
        
        # Calculate next birthday
        next_birthday = datetime(today.year, birthdate.month, birthdate.day)
        if next_birthday < today:
            next_birthday = datetime(today.year + 1, birthdate.month, birthdate.day)
            
        days_to_birthday = (next_birthday - today).days
        
        print(f"You are {age} years old")
        print(f"Your next birthday is in {days_to_birthday} days!")
        
    except ValueError:
        print("Please use YYYY-MM-DD format!")

# Usage
calculate_age("2005-06-15")
```

## 3. JSON Module 📋

### What is JSON?
JSON is like a universal language for storing and sharing data:
- Save data in a readable format
- Share data between different programs
- Store settings and configurations

### Example 1: Basic JSON Operations
```python
import json

def work_with_json():
    # Create a dictionary
    student = {
        "name": "Alex",
        "age": 16,
        "grades": {
            "math": 95,
            "science": 88,
            "history": 92
        },
        "activities": ["soccer", "chess club"]
    }
    
    # Convert to JSON string
    json_string = json.dumps(student, indent=2)
    print("JSON string:")
    print(json_string)
    
    # Save to file
    with open('student.json', 'w') as f:
        json.dump(student, f, indent=2)
    
    # Read from file
    with open('student.json', 'r') as f:
        loaded_student = json.load(f)
    
    print("\nLoaded from file:")
    print(f"Name: {loaded_student['name']}")
    print(f"Math grade: {loaded_student['grades']['math']}")

# Usage
work_with_json()
```

### Example 2: Game Save System
```python
import json
from datetime import datetime

def save_game_state(player_name, level, score):
    game_state = {
        "player": player_name,
        "level": level,
        "score": score,
        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    }
    
    # Save to file
    filename = f"save_{player_name.lower()}.json"
    with open(filename, 'w') as f:
        json.dump(game_state, f, indent=2)
    print("Game saved!")

def load_game_state(player_name):
    try:
        filename = f"save_{player_name.lower()}.json"
        with open(filename, 'r') as f:
            game_state = json.load(f)
            
        print(f"Welcome back, {game_state['player']}!")
        print(f"Level: {game_state['level']}")
        print(f"Score: {game_state['score']}")
        print(f"Last played: {game_state['timestamp']}")
        
        return game_state
    except FileNotFoundError:
        print("No saved game found!")
        return None

# Usage
save_game_state("Alex", 5, 1000)
loaded_game = load_game_state("Alex")
```

## 4. NumPy 🔢

### What is NumPy?
NumPy is a powerful library for working with numbers and arrays:
- Fast mathematical operations
- Work with large sets of numbers
- Perform calculations on entire arrays at once

### Example 1: Basic Array Operations
```python
import numpy as np

def numpy_basics():
    # Create arrays
    numbers = np.array([1, 2, 3, 4, 5])
    print("Basic array:", numbers)
    
    # Create 2D array (matrix)
    matrix = np.array([[1, 2, 3],
                      [4, 5, 6],
                      [7, 8, 9]])
    print("\nMatrix:")
    print(matrix)
    
    # Basic operations
    print("\nAdd 2 to all elements:", numbers + 2)
    print("Multiply all elements by 3:", numbers * 3)
    print("Square all elements:", numbers ** 2)
    
    # Statistics
    print("\nStatistics:")
    print(f"Average: {np.mean(numbers)}")
    print(f"Maximum: {np.max(numbers)}")
    print(f"Minimum: {np.min(numbers)}")
    print(f"Sum: {np.sum(numbers)}")

# Usage
numpy_basics()
```

### Example 2: Grade Calculator
```python
import numpy as np

def analyze_grades(grades):
    grades_array = np.array(grades)
    
    print("Grade Analysis:")
    print(f"Average: {np.mean(grades_array):.2f}")
    print(f"Highest: {np.max(grades_array)}")
    print(f"Lowest: {np.min(grades_array)}")
    
    # Calculate letter grades
    def get_letter_grade(score):
        if score >= 90: return 'A'
        elif score >= 80: return 'B'
        elif score >= 70: return 'C'
        elif score >= 60: return 'D'
        else: return 'F'
    
    letter_grades = [get_letter_grade(grade) for grade in grades_array]
    unique, counts = np.unique(letter_grades, return_counts=True)
    
    print("\nGrade Distribution:")
    for grade, count in zip(unique, counts):
        print(f"{grade}: {count} students")

# Usage
class_grades = [85, 92, 78, 95, 89, 70, 88, 94, 93, 77]
analyze_grades(class_grades)
```

## 5. Pandas 🐼

### What is Pandas?
Pandas is like Excel for Python:
- Work with data in tables (DataFrames)
- Read and write Excel/CSV files
- Analyze and manipulate data easily

### Example 1: Basic DataFrame Operations
```python
import pandas as pd

def pandas_basics():
    # Create a simple DataFrame
    data = {
        'Name': ['Alex', 'Emma', 'Jack', 'Sophia'],
        'Age': [16, 15, 16, 15],
        'Math': [95, 88, 92, 90],
        'Science': [88, 95, 85, 92]
    }
    
    df = pd.DataFrame(data)
    print("Student Data:")
    print(df)
    
    # Calculate average grades
    df['Average'] = df[['Math', 'Science']].mean(axis=1)
    print("\nWith Averages:")
    print(df)
    
    # Sort by average grade
    print("\nSorted by Average:")
    print(df.sort_values('Average', ascending=False))

# Usage
pandas_basics()
```

### Example 2: Reading and Analyzing CSV Data
```python
import pandas as pd

def analyze_student_data(csv_file):
    try:
        # Read CSV file
        df = pd.read_csv(csv_file)
        
        print("Class Summary:")
        print("==============")
        
        # Basic statistics
        print("\nAverage Grades:")
        print(df[['Math', 'Science', 'History']].mean())
        
        # Find top students
        print("\nTop Student in Each Subject:")
        for subject in ['Math', 'Science', 'History']:
            top_student = df.loc[df[subject].idxmax()]
            print(f"{subject}: {top_student['Name']} ({top_student[subject]})")
        
        # Create grade summary
        print("\nGrade Distribution:")
        grade_ranges = [0, 60, 70, 80, 90, 100]
        labels = ['F', 'D', 'C', 'B', 'A']
        
        for subject in ['Math', 'Science', 'History']:
            grades = pd.cut(df[subject], bins=grade_ranges, labels=labels)
            print(f"\n{subject}:")
            print(grades.value_counts().sort_index())
            
    except FileNotFoundError:
        print(f"File {csv_file} not found!")
    except Exception as e:
        print(f"Error: {e}")

# Usage (assuming students.csv exists)
analyze_student_data('students.csv')
```

### Example 3: Data Visualization with Pandas
```python
import pandas as pd
import matplotlib.pyplot as plt

def visualize_grades(csv_file):
    try:
        # Read data
        df = pd.read_csv(csv_file)
        
        # Create plots
        plt.figure(figsize=(15, 5))
        
        # Bar plot of average grades
        plt.subplot(1, 2, 1)
        df[['Math', 'Science', 'History']].mean().plot(kind='bar')
        plt.title('Average Grades by Subject')
        plt.ylabel('Grade')
        
        # Box plot of grade distribution
        plt.subplot(1, 2, 2)
        df[['Math', 'Science', 'History']].boxplot()
        plt.title('Grade Distribution by Subject')
        
        plt.tight_layout()
        plt.show()
        
    except FileNotFoundError:
        print(f"File {csv_file} not found!")

# Usage
visualize_grades('students.csv')
```

## Practice Projects 🎯

1. **School Management System**
   - Store student data in JSON
   - Calculate grades using NumPy
   - Generate reports with Pandas
   - Track attendance with datetime

2. **Personal Finance Tracker**
   - Record expenses in CSV
   - Analyze spending with Pandas
   - Create budget visualizations
   - Track payment dates

3. **File Organization Tool**
   - Use OS module to scan directories
   - Organize files by date
   - Generate JSON reports
   - Create data summaries with Pandas

These examples and projects will help you understand these powerful Python modules. Try modifying them and creating your own versions!
