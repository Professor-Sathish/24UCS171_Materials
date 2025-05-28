# Bank Account Management System - Progressive Learning Journey

## Repository Structure
```
bank-account-system/
├── README.md
├── docs/
│   ├── learning-path.md
│   └── concepts-explained.md
├── version-01-basic-struct/
│   ├── README.md
│   ├── main.c
│   ├── tests/
│   └── Makefile
├── version-02-file-operations/
├── version-03-crud-operations/
├── version-04-menu-system/
├── version-05-data-validation/
├── version-06-sorting-features/
└── final-complete-system/
```

## Learning Philosophy: Test-Driven Development (TDD)

Each version follows the **Red-Green-Refactor** cycle:
1. **Red**: Write failing tests first
2. **Green**: Write minimal code to pass tests
3. **Refactor**: Improve code while keeping tests passing

## Version Progression Overview

### Version 1: Basic Data Structure (Week 1)
**Learning Goals:**
- Understand C structures
- Memory layout concepts
- Basic data representation

**Key Concepts:**
- `struct` keyword
- Member access (dot notation)
- Structure initialization
- Memory allocation for structures

### Version 2: File I/O Fundamentals (Week 2)
**Learning Goals:**
- File operations in C
- Binary vs text files
- File pointers and modes

**Key Concepts:**
- `fopen()`, `fclose()`
- `fread()`, `fwrite()`
- File positioning with `fseek()`
- Error handling

### Version 3: CRUD Operations (Week 3-4)
**Learning Goals:**
- Create, Read, Update, Delete operations
- Random access file handling
- Data persistence

**Key Concepts:**
- Record positioning
- Data validation
- File structure management

### Version 4: User Interface (Week 5)
**Learning Goals:**
- Menu-driven programs
- User input validation
- Program flow control

**Key Concepts:**
- Switch statements
- Input validation
- Loop constructs

### Version 5: Data Validation & Error Handling (Week 6)
**Learning Goals:**
- Robust error handling
- Input sanitization
- Edge case management

**Key Concepts:**
- Defensive programming
- Error codes and messages
- Input validation techniques

### Version 6: Advanced Features (Week 7-8)
**Learning Goals:**
- Sorting algorithms
- Data analysis
- Performance considerations

**Key Concepts:**
- `qsort()` function
- Comparison functions
- Array manipulation
- Algorithm complexity

## TDD Learning Approach

### For Each Version:

1. **Study Phase** (Day 1-2)
   - Read concept documentation
   - Understand the theory
   - Review example code snippets

2. **Test-First Development** (Day 3-4)
   - Write tests for expected functionality
   - Run tests (they should fail initially)
   - Implement minimal code to pass tests

3. **Enhancement Phase** (Day 5-6)
   - Add more comprehensive tests
   - Refactor code for better design
   - Add documentation and comments

4. **Integration Phase** (Day 7)
   - Combine with previous versions
   - Ensure backward compatibility
   - Update documentation

## Assessment Criteria

### For Each Version:
- [ ] All tests pass
- [ ] Code is properly documented
- [ ] No memory leaks
- [ ] Follows C coding standards
- [ ] README explains the concepts clearly

### Skills Development Tracking:
- **Beginner**: Can read and understand the code
- **Intermediate**: Can modify existing functions
- **Advanced**: Can add new features independently
- **Expert**: Can optimize and refactor the entire system

## Resources Provided

### For Each Version Directory:
- `README.md` - Detailed explanation of concepts
- `main.c` - Working implementation
- `tests/` - Unit tests and test data
- `Makefile` - Build configuration
- `concepts.md` - Theoretical background
- `exercises.md` - Practice problems

### Testing Framework
We'll use a simple C testing framework that's easy to understand:
```c
// Simple test macros
#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        printf("FAIL: Expected %d, got %d\n", expected, actual); \
        return 0; \
    }

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        printf("FAIL: Condition failed\n"); \
        return 0; \
    }
```

## Next Steps

1. Clone this repository
2. Start with `version-01-basic-struct/`
3. Read the README thoroughly
4. Run the tests: `make test`
5. Study the implementation
6. Complete the exercises
7. Move to the next version only after mastering current one

## Mentorship Notes

As your professor (My buddies), I recommend:
- Spend at least one week on each version
- Don't rush to the complex versions
- Focus on understanding, not just completion
- Ask questions when concepts are unclear
- Practice the exercises multiple times
- Code review sessions after each version

Remember: **"The expert in anything was once a beginner who refused to give up."**