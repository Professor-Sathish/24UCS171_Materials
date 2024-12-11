# Comprehensive Guide to NumPy and Pandas

## 1. NumPy (Numerical Python) 🔢

### What is NumPy?
NumPy is the foundation for scientific and mathematical computing in Python:
- Fast operations on large arrays
- Mathematical and statistical functions
- Linear algebra operations
- Random number generation

### 1.1 Creating Arrays
```python
import numpy as np

def numpy_array_creation():
    # Different ways to create arrays
    print("1. Create from list:")
    arr1 = np.array([1, 2, 3, 4, 5])
    print(arr1)  # [1 2 3 4 5]

    print("\n2. Create range array:")
    arr2 = np.arange(0, 10, 2)  # Start, Stop, Step
    print(arr2)  # [0 2 4 6 8]

    print("\n3. Create evenly spaced numbers:")
    arr3 = np.linspace(0, 1, 5)  # Start, Stop, Number of points
    print(arr3)  # [0.   0.25 0.5  0.75 1.  ]

    print("\n4. Create 2D array:")
    arr4 = np.array([[1, 2, 3], [4, 5, 6]])
    print(arr4)

    print("\n5. Special arrays:")
    print("Zeros:", np.zeros(3))
    print("Ones:", np.ones((2, 2)))
    print("Identity matrix:", np.eye(3))
    print("Random array:", np.random.rand(3, 3))

# Usage
numpy_array_creation()
```

### 1.2 Array Operations and Math
```python
def numpy_operations():
    # Create sample arrays
    arr1 = np.array([1, 2, 3, 4, 5])
    arr2 = np.array([6, 7, 8, 9, 10])
    
    print("Basic Operations:")
    print("Addition:", arr1 + arr2)
    print("Multiplication:", arr1 * arr2)
    print("Square root:", np.sqrt(arr1))
    print("Exponential:", np.exp(arr1))
    
    # Matrix operations
    matrix1 = np.array([[1, 2], [3, 4]])
    matrix2 = np.array([[5, 6], [7, 8]])
    
    print("\nMatrix Operations:")
    print("Matrix multiplication:")
    print(np.dot(matrix1, matrix2))
    print("\nTranspose:")
    print(matrix1.T)

# Usage
numpy_operations()
```

### 1.3 Array Indexing and Slicing
```python
def array_manipulation():
    # Create sample array
    arr = np.array([[1, 2, 3, 4],
                    [5, 6, 7, 8],
                    [9, 10, 11, 12]])
    
    print("Original array:")
    print(arr)
    
    print("\nSlicing:")
    print("First two rows:", arr[:2])
    print("First two columns:", arr[:, :2])
    print("Specific element:", arr[1, 2])
    
    # Boolean indexing
    print("\nBoolean indexing:")
    print("Elements greater than 5:", arr[arr > 5])
    
    # Fancy indexing
    print("\nFancy indexing:")
    rows = np.array([0, 2])
    cols = np.array([1, 3])
    print("Selected elements:", arr[rows[:, np.newaxis], cols])

# Usage
array_manipulation()
```

### 1.4 Statistical Operations
```python
def statistical_analysis():
    # Create sample data
    data = np.random.normal(100, 15, 1000)  # Mean=100, STD=15, Size=1000
    
    print("Statistical Measures:")
    print(f"Mean: {np.mean(data):.2f}")
    print(f"Median: {np.median(data):.2f}")
    print(f"Standard Deviation: {np.std(data):.2f}")
    print(f"Variance: {np.var(data):.2f}")
    
    # Percentiles
    print("\nPercentiles:")
    percentiles = [25, 50, 75]
    for p in percentiles:
        value = np.percentile(data, p)
        print(f"{p}th percentile: {value:.2f}")
    
    # Histogram data
    hist, bins = np.histogram(data, bins=10)
    print("\nHistogram data:")
    print("Counts:", hist)
    print("Bin edges:", bins)

# Usage
statistical_analysis()
```

### 1.5 Practical Example: Image Processing
```python
def image_processing():
    # Create a simple image (grayscale)
    image = np.random.randint(0, 255, (100, 100))
    
    # Image operations
    print("Image operations:")
    print(f"Mean pixel value: {np.mean(image):.2f}")
    print(f"Max pixel value: {np.max(image)}")
    print(f"Min pixel value: {np.min(image)}")
    
    # Image transformations
    rotated = np.rot90(image)  # Rotate 90 degrees
    flipped = np.flipud(image)  # Flip up-down
    
    # Apply filters
    blurred = np.convolve(image.flatten(), 
                         np.ones(5)/5, 
                         mode='valid').reshape(96, 96)
    
    return image, rotated, blurred

# Usage
original, rotated, blurred = image_processing()
```

## 2. Pandas 🐼

### What is Pandas?
Pandas is designed for data manipulation and analysis:
- Data cleaning and preparation
- Merging and joining datasets
- Time series functionality
- Data visualization

### 2.1 Creating DataFrames
```python
import pandas as pd

def create_dataframes():
    # From dictionary
    dict_data = {
        'Name': ['John', 'Emma', 'Alex', 'Sarah'],
        'Age': [25, 28, 22, 30],
        'City': ['New York', 'London', 'Paris', 'Tokyo']
    }
    df1 = pd.DataFrame(dict_data)
    print("DataFrame from dictionary:")
    print(df1)
    
    # From list of lists
    list_data = [
        ['John', 25, 'New York'],
        ['Emma', 28, 'London'],
        ['Alex', 22, 'Paris']
    ]
    df2 = pd.DataFrame(list_data, 
                      columns=['Name', 'Age', 'City'])
    print("\nDataFrame from list:")
    print(df2)
    
    # From CSV file
    # df3 = pd.read_csv('data.csv')
    
    return df1

# Usage
df = create_dataframes()
```

### 2.2 Data Selection and Indexing
```python
def data_selection(df):
    print("Basic Selection:")
    print("\nSelect single column:")
    print(df['Name'])
    
    print("\nSelect multiple columns:")
    print(df[['Name', 'Age']])
    
    print("\nSelect by position:")
    print(df.iloc[0])  # First row
    print(df.iloc[0:2])  # First two rows
    
    print("\nSelect by label:")
    print(df.loc[0])  # First row
    
    print("\nConditional selection:")
    print(df[df['Age'] > 25])
    
    # Advanced selection
    print("\nComplex conditions:")
    condition = (df['Age'] > 25) & (df['City'] == 'London')
    print(df[condition])

# Usage
data_selection(df)
```

### 2.3 Data Manipulation
```python
def data_manipulation(df):
    # Add new column
    df['Country'] = ['USA', 'UK', 'France', 'Japan']
    
    # Calculate new column
    df['Age_Group'] = pd.cut(df['Age'], 
                            bins=[0, 25, 30, 100],
                            labels=['Young', 'Adult', 'Senior'])
    
    # Sort values
    print("Sorted by Age:")
    print(df.sort_values('Age'))
    
    # Group by and aggregate
    print("\nAge statistics by City:")
    print(df.groupby('City')['Age'].agg(['mean', 'min', 'max']))
    
    # Replace values
    df['City'] = df['City'].replace('London', 'Manchester')
    
    return df

# Usage
df_modified = data_manipulation(df)
```

### 2.4 Data Cleaning
```python
def data_cleaning():
    # Create sample dirty data
    dirty_data = pd.DataFrame({
        'Name': ['John', 'Emma', None, 'Sarah'],
        'Age': [25, -28, 22, 3000],
        'City': ['New York', '', 'Paris', 'Tokyo']
    })
    
    print("Original dirty data:")
    print(dirty_data)
    
    # Check for missing values
    print("\nMissing values:")
    print(dirty_data.isnull().sum())
    
    # Handle missing values
    clean_data = dirty_data.copy()
    clean_data['Name'].fillna('Unknown', inplace=True)
    clean_data['City'].replace('', 'Unknown', inplace=True)
    
    # Handle invalid values
    clean_data.loc[clean_data['Age'] < 0, 'Age'] = 0
    clean_data.loc[clean_data['Age'] > 120, 'Age'] = 120
    
    print("\nCleaned data:")
    print(clean_data)
    
    return clean_data

# Usage
clean_df = data_cleaning()
```

### 2.5 Data Analysis and Statistics
```python
def data_analysis(df):
    # Basic statistics
    print("Basic Statistics:")
    print(df.describe())
    
    # Correlation
    print("\nCorrelation:")
    print(df.corr())
    
    # Value counts
    print("\nCity distribution:")
    print(df['City'].value_counts())
    
    # Custom analysis
    print("\nCustom analysis:")
    analysis = {
        'Total Count': len(df),
        'Average Age': df['Age'].mean(),
        'Age Range': df['Age'].max() - df['Age'].min(),
        'Most Common City': df['City'].mode()[0]
    }
    print(pd.Series(analysis))

# Usage
data_analysis(df)
```

### 2.6 Time Series Analysis
```python
def time_series_analysis():
    # Create date range
    dates = pd.date_range(start='2024-01-01', 
                         end='2024-12-31', 
                         freq='D')
    
    # Create time series data
    data = pd.Series(np.random.randn(len(dates)), index=dates)
    
    print("Daily data:")
    print(data.head())
    
    # Resample to monthly
    monthly = data.resample('M').mean()
    print("\nMonthly averages:")
    print(monthly)
    
    # Rolling statistics
    rolling_mean = data.rolling(window=7).mean()
    print("\nWeekly rolling average:")
    print(rolling_mean.head(10))
    
    return data, monthly, rolling_mean

# Usage
daily, monthly, rolling = time_series_analysis()
```

### 2.7 Advanced Operations: Merge and Join
```python
def merge_and_join():
    # Create sample dataframes
    df1 = pd.DataFrame({
        'ID': [1, 2, 3, 4],
        'Name': ['John', 'Emma', 'Alex', 'Sarah'],
        'Age': [25, 28, 22, 30]
    })
    
    df2 = pd.DataFrame({
        'ID': [1, 2, 3, 5],
        'City': ['New York', 'London', 'Paris', 'Berlin'],
        'Salary': [50000, 60000, 45000, 65000]
    })
    
    # Different types of joins
    print("Inner join:")
    print(pd.merge(df1, df2, on='ID', how='inner'))
    
    print("\nOuter join:")
    print(pd.merge(df1, df2, on='ID', how='outer'))
    
    print("\nLeft join:")
    print(pd.merge(df1, df2, on='ID', how='left'))
    
    print("\nRight join:")
    print(pd.merge(df1, df2, on='ID', how='right'))

# Usage
merge_and_join()
```

### 2.8 Practical Example: Sales Analysis
```python
def sales_analysis():
    # Create sample sales data
    dates = pd.date_range('2024-01-01', '2024-12-31', freq='D')
    products = ['Product A', 'Product B', 'Product C']
    
    sales_data = pd.DataFrame({
        'Date': np.repeat(dates, len(products)),
        'Product': np.tile(products, len(dates)),
        'Units': np.random.randint(1, 100, len(dates) * len(products)),
        'Price': np.random.uniform(10, 100, len(dates) * len(products))
    })
    
    # Calculate revenue
    sales_data['Revenue'] = sales_data['Units'] * sales_data['Price']
    
    # Daily analysis
    daily_sales = sales_data.groupby(['Date', 'Product'])['Revenue'].sum()
    
    # Monthly analysis
    sales_data['Month'] = sales_data['Date'].dt.to_period('M')
    monthly_sales = sales_data.groupby(['Month', 'Product']).agg({
        'Units': 'sum',
        'Revenue': 'sum'
    })
    
    # Product performance
    product_performance = sales_data.groupby('Product').agg({
        'Units': 'sum',
        'Revenue': 'sum',
        'Price': 'mean'
    }).round(2)
    
    return sales_data, daily_sales, monthly_sales, product_performance

# Usage
sales_df, daily, monthly, performance = sales_analysis()
```

## Practice Projects 🎯

1. **Stock Market Analysis**
   - Load stock price data using Pandas
   - Calculate moving averages with NumPy
   - Analyze price trends and patterns
   - Generate trading signals

2. **Weather Data Analysis**
   - Process temperature data using NumPy
   - Calculate seasonal patterns
   - Create weather forecasts
   - Visualize temperature trends

3. **Student Performance Analysis**
   - Load and clean student data
   - Calculate grade statistics
   - Identify performance patterns
   - Generate student reports

4. **E-commerce Analytics**
   - Analyze customer behavior
   - Calculate sales metrics
   - Identify top products
   - Generate revenue reports

