# Minerva

This project is a modified fork of the Athena library and has been modified to suit our needs.<br>
The original project can be found at https://github.com/lolrobbe2/Athena.

The name has been changed to respect the Apache v2.0 license.

---

**Minerva** is a versatile C++ library designed for efficient binary file operations, allowing developers to directly write structs, classes, raw data, and arrays into a binary format. It combines high-performance compression with modular data management, making it an excellent tool/library for handling complex binary data storage needs.

### Key Features:

1. **LZ4 Compression**  
   Minerva leverages the [LZ4](https://github.com/lz4/lz4) compression algorithm, which is known for its speed and efficiency. This feature ensures that data can be compressed and decompressed rapidly, optimizing both storage space and access times.

2. **Modular Sections with Parallel Compression**  
   Files created with Minerva are divided into independent sections, each of which is compressed separately. To enhance performance, Minerva compresses each section in a different thread, allowing for faster processing, especially when working with large files. This modular and parallel approach enables selective decompression of individual sections, providing flexibility when accessing or modifying specific parts of a file without needing to handle the entire file.

3. **Raw Data and Array Handling**  
   In addition to structs and classes, Minerva supports direct writing of raw data and arrays. This feature makes it easier to handle a wide range of binary data types, offering flexibility in how data is structured and stored.

4. **Backward and Forward Compatibility**  
    Minerva ensures that [Trivially Copyable Structs and Classes](#trivially-copyable-structs-and-classes)
   maintain compatibility across different versions, as long as changes (such as adding or removing fields) are performed in a stack-like order. This compatibility is crucial for maintaining data integrity and accessibility over time as the data structures evolve.

Minerva is ideal for developers who need a high-performance, flexible solution for managing binary data in C++, with robust support for various data types, parallel compression for improved performance, and backward compatibility.