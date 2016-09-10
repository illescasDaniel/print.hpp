# print.h

A replacement for the 'cout' function.  

Using 'print' you can display information easily.  
The 'to_string' function that I implemented let you convert containers (like std::vector) to string.
<br></br>

Syntax
-----
<br></br>
· **print:**  
```c++
print(const Type& value, const Args& ...args);
```

· Example:  
```c++
print("This is a number:", 23123); // Output -> This is a number: 23123
```

<br></br>
· **to_string for containers:**  
```c++
to_string(const container& cont); 
```

· Example using both functions:  
```c++
print("My vector:", to_string(vector)); // Possible output -> My vector: [1, 2, 3]
```

<br></br>
· **to_string for classic arrays:**  
```c++
to_string(const T * array, size_t size);
```

· Example:  
```c++
print(to_string(array,5));
```

<br></br>
· **to_string for matrices:**  
```c++
to_string(const Type& matrix, size_t rows, size_t cols);
```

· Example:  
```c++
print(to_string(matrix,rows,cols)); // An output -> [[1, 2], [3, 4], [5, 6]]
```

