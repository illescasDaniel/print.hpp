# print.h

A replacement for the 'cout' function.  

Using 'print' you can display information easily.  
The 'to_string' function that I implemented let you convert containers (like std::vector) to string.
<br></br>

· **print function syntax:**  
```c++
print(const Type& value, const Args& ...args);
```

· Example:  
```c++
print("This is a number:", 23123); // Output -> This is a number: 23123
```
<br></br>
· **to_string function syntax for containers:**  
```c++
to_string(const container& cont); 
```

· Example:  
```c++
to_string(vector1); 
```

· Example using both functions:  
```c++
print("My vector:", to_string(vector1)); // Possible output -> My vector: [1,2,3]
```
<br></br>
· **to_string function syntax for classic arrays:**  
```c++
to_string(const T * array, size_t size);
```

· Example:  
```c++
to_string("My array:", to_string(array1,5));
```
