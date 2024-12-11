# Python Programming Guide: Files, Exceptions, and Modules

## 1. File Handling in Python 📁

### What is File Handling?
Think of file handling like working with digital notebooks. You can:
- Read what's written in them (reading files)
- Write new things (writing files)
- Add more information at the end (appending files)
- Create new notebooks (creating files)

### File Modes Made Simple
```
'r' - Just reading (like opening a book to read)
'w' - Writing (erases old content, starts fresh)
'a' - Adding at the end (like adding new pages)
'r+' - Reading and writing (like being able to both read and edit)
```

### Example 1: Reading Your Diary
```python
# Reading an entire file at once
def read_diary(filename):
    with open(filename, 'r') as diary:
        content = diary.read()
    return content

# Reading line by line (like reading page by page)
def read_diary_entries(filename):
    with open(filename, 'r') as diary:
        for line in diary:
            print(f"Entry: {line.strip()}")

# Usage
read_diary_entries('my_diary.txt')
```

### Example 2: Creating a To-Do List
```python
def add_todo(filename, task):
    with open(filename, 'a') as todo_list:
        todo_list.write(f"{task}\n")

def read_todos(filename):
    try:
        with open(filename, 'r') as todo_list:
            tasks = todo_list.readlines()
        for i, task in enumerate(tasks, 1):
            print(f"{i}. {task.strip()}")
    except FileNotFoundError:
        print("You haven't created your todo list yet!")

# Usage
add_todo('tasks.txt', 'Do homework')
add_todo('tasks.txt', 'Clean room')
read_todos('tasks.txt')
```

### Example 3: Making a Simple Note-Taking App
```python
from datetime import datetime

def create_note(filename, title, content):
    with open(filename, 'a') as notebook:
        date = datetime.now().strftime('%Y-%m-%d %H:%M')
        notebook.write(f"\n=== {title} ({date}) ===\n")
        notebook.write(f"{content}\n")
        notebook.write("="* 30 + "\n")

def read_notes(filename):
    try:
        with open(filename, 'r') as notebook:
            print(notebook.read())
    except FileNotFoundError:
        print("Notebook not found! Let's create one.")

# Usage
create_note('my_notes.txt', 'Python Learning', 'Today I learned about file handling!')
create_note('my_notes.txt', 'Math Notes', 'Algebra is interesting!')
read_notes('my_notes.txt')
```

## 2. Working with Zip Files 🗜️

### What are Zip Files?
Think of zip files like digital suitcases where you can:
- Pack multiple files together (compression)
- Make files smaller to save space
- Unpack files when needed (extraction)

### Example 1: Creating a Backup of Your Photos
```python
import zipfile
import os

def backup_photos(folder_path, zip_name):
    with zipfile.ZipFile(zip_name, 'w') as photo_archive:
        # Walk through the folder
        for folder_path, _, files in os.walk(folder_path):
            for photo in files:
                if photo.endswith(('.jpg', '.png', '.jpeg')):
                    photo_path = os.path.join(folder_path, photo)
                    photo_archive.write(photo_path)
                    print(f"Backed up: {photo}")

# Usage
backup_photos('my_photos', 'photos_backup.zip')
```

### Example 2: Making a School Project Archive
```python
def create_project_archive(project_name, files):
    zip_name = f"{project_name}_project.zip"
    try:
        with zipfile.ZipFile(zip_name, 'w') as project_zip:
            for file in files:
                if os.path.exists(file):
                    project_zip.write(file)
                    print(f"Added {file} to project archive")
        print(f"Project archived as {zip_name}")
    except Exception as e:
        print(f"Oops! Something went wrong: {e}")

# Usage
project_files = ['report.docx', 'presentation.pptx', 'data.xlsx']
create_project_archive('science_fair', project_files)
```

### Example 3: Extracting Files from a Zip
```python
def extract_homework(zip_file, extract_to):
    try:
        with zipfile.ZipFile(zip_file, 'r') as homework_zip:
            # List contents
            print("Files in the zip:")
            for file in homework_zip.namelist():
                print(f"- {file}")
            
            # Extract everything
            homework_zip.extractall(extract_to)
            print(f"\nAll files extracted to {extract_to}")
    except zipfile.BadZipFile:
        print("This isn't a valid zip file!")

# Usage
extract_homework('homework.zip', 'homework_folder')
```

## 3. Exception Handling 🛡️

### What are Exceptions?
Think of exceptions like safety nets in your code:
- They catch errors before they crash your program
- Help you handle unexpected situations
- Let you provide friendly error messages

### Example 1: Calculator with Error Handling
```python
def safe_calculator():
    try:
        num1 = float(input("Enter first number: "))
        num2 = float(input("Enter second number: "))
        operation = input("Choose operation (+, -, *, /): ")
        
        if operation == '+':
            result = num1 + num2
        elif operation == '-':
            result = num1 - num2
        elif operation == '*':
            result = num1 * num2
        elif operation == '/':
            result = num1 / num2
        else:
            print("Invalid operation!")
            return
            
        print(f"Result: {result}")
    except ValueError:
        print("Please enter valid numbers!")
    except ZeroDivisionError:
        print("Can't divide by zero!")
    except Exception as e:
        print(f"Something went wrong: {e}")

# Usage
safe_calculator()
```

### Example 2: File Score Keeper
```python
def update_score(player_name, score):
    try:
        # Read current scores
        with open('scores.txt', 'r') as file:
            scores = {}
            for line in file:
                name, points = line.strip().split(':')
                scores[name] = int(points)
    except FileNotFoundError:
        scores = {}
    
    # Update score
    scores[player_name] = score
    
    # Save back to file
    try:
        with open('scores.txt', 'w') as file:
            for name, points in scores.items():
                file.write(f"{name}:{points}\n")
        print("Score updated successfully!")
    except Exception as e:
        print(f"Couldn't save score: {e}")

# Usage
update_score("Alex", 100)
update_score("Sam", 95)
```

### Example 3: Safe File Reader
```python
def read_file_safely(filename):
    try:
        with open(filename, 'r') as file:
            content = file.read()
            print("File contents:")
            print(content)
    except FileNotFoundError:
        print(f"Sorry, {filename} doesn't exist!")
    except PermissionError:
        print("You don't have permission to read this file!")
    except Exception as e:
        print(f"An error occurred: {e}")
    else:
        print("File read successfully!")
    finally:
        print("Thank you for using safe file reader!")

# Usage
read_file_safely('my_diary.txt')
```

## 4. Modules and Packages 📦

### What are Modules and Packages?
Think of:
- Modules as tools in a toolbox
- Packages as organized toolboxes with different compartments
- Each tool (module) has specific uses

### Example 1: Creating a School Subjects Package
```
school_subjects/
    __init__.py
    math_tools.py
    science_tools.py
    language_tools.py
```

```python
# math_tools.py
def add_numbers(numbers):
    return sum(numbers)

def average(numbers):
    return sum(numbers) / len(numbers)

def calculate_grade(score, total):
    percentage = (score / total) * 100
    if percentage >= 90: return 'A'
    elif percentage >= 80: return 'B'
    elif percentage >= 70: return 'C'
    elif percentage >= 60: return 'D'
    else: return 'F'
```

### Example 2: Using Custom Modules
```python
# Import specific functions
from school_subjects.math_tools import calculate_grade
from school_subjects.science_tools import convert_units

# Using the imported functions
score = 85
total = 100
grade = calculate_grade(score, total)
print(f"Your grade is: {grade}")
```

### Example 3: Creating a Simple Game Package
```python
# game_package/player.py
def create_player(name, level=1):
    return {
        'name': name,
        'level': level,
        'health': 100,
        'score': 0
    }

def level_up(player):
    player['level'] += 1
    print(f"{player['name']} is now level {player['level']}!")

# game_package/scoring.py
def add_score(player, points):
    player['score'] += points
    print(f"{player['name']} earned {points} points!")

def display_score(player):
    print(f"Player: {player['name']}")
    print(f"Score: {player['score']}")
    print(f"Level: {player['level']}")
```

### Using the Game Package
```python
from game_package.player import create_player, level_up
from game_package.scoring import add_score, display_score

# Create a new player
player1 = create_player("Alex")

# Play the game
add_score(player1, 100)
level_up(player1)
display_score(player1)
```

## Practice Projects 🎯

1. **Personal Diary System**
   - Create new entries
   - Read past entries
   - Search entries by date
   - Backup entries to zip file

2. **Student Grade Manager**
   - Add student scores
   - Calculate averages
   - Generate report cards
   - Handle invalid grades with exceptions

3. **File Organization Tool**
   - Scan a folder
   - Organize files by type
   - Create zip backups
   - Handle file operation errors

