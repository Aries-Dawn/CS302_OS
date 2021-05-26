# Report 9

> **11811901 樊顺**

*Assume, for all of the questions in this part, that filesystem blocks are 4 KBytes.*

## Question 1

Consider a really simple filesystem, cs302fs, where each inode only has 10 direct pointers, each of which can point to a single file block. Direct pointers are 32 bits in size (4 bytes). What is the maximum file size for cs302fs?

> cs302fs have 10 directly pointer, each pointer can point to a Block that is 4KBytes,so cs302fs's max file size is 10*4KBytes = 40KBytes.

## Question 2

Consider a filesystem, called extcs302fs, with a construct called an extent. Extents have a pointer (base address) and a length (in blocks). Assume the length field is 8 bits (1 byte). Assuming that an inode has exactly one extent. What is the maximum file size for extcs302fs?

> Because the length field is 8 bits, so it can express max 2^8-1 = 255 blocks, maximum file size is 255*4KBytes = 1020KBytes.

## Question 3

Consider a filesystem that uses direct pointers, but also adds indirect pointers and double-indirect pointers. We call this filesystem, indcs302fs. Specifically, an inode within indcs302fs has 1 direct pointer, l indirect pointer, and 1 doubly-indirect pointer field. Pointers, as before, are 4 bytes (32 bits) in size. What is the maximum file size for indcs302fs?
>
> + the directly pointer can express 1 blocks.
> + the indirect pointer can express 1 blocks's pointer, which is (4KBytes/4Bytes),
> + the double-indirect pointer can express (4KBytes/4Bytes) indirect pointers, which is (4KBytes/4Bytes)* (4KBytes/4Bytes) blocks.
> + so, after all, the maximum file size is ( (4KBytes/4Bytes)*(4KBytes/4Bytes) +(4KBytes/4Bytes) +1)*4KBytes. = 4GBytes+4MBytes+4KBytes.
