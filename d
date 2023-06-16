Build the naive malloc that is presented in the concept page.

Prototype: void *naive_malloc(size_t size);
Where size is the size needed to be allocated for the user
Your function must return a pointer to the allocated memory that is suitably aligned for any kind of variable
You naive malloc should be able to:
Allocate enough memory to store
A size_t as the chunk header
The size requested as parameter
Allocate memory pages only

Start by adding two static variables in our function:
One variable to keep track of the address of the first chunk in our chain. This address is also the beginning of the heap.
Another variable to keep track of the number of chunks used in our chain. This represents the number of times our function has been called.
When the naive malloc function is called for the first time, we need to extend the program break by the size of a virtual memory page. This can be done by using a function like sbrk to allocate the initial memory page.
Each time our function is called, we need to iterate through our chain of chunks. This can be done by following the size information stored in each chunk's header. The goal is to locate an unused chunk that can satisfy the memory allocation request.
Once we find an unused chunk, we should split it into two separate chunks:
The first chunk will be the one returned to the user as the allocated memory (the used chunk).
The second chunk will contain the excess memory that remains unused.
At this stage, you don't need to handle the case when the heap is full and needs to be extended. you will address that later. For now, the heap should only be extended the first time our function is called.
These steps will guide you through the implementation process.
Here is also the requirements of the first task (naive_malloc) here from the concept page, so just you have to read it carefully to implement the naive_malloc, you should to follow that steps.
For the diference between task 0 and 1:
The naive_malloc function mentioned in the concept page  is a simplified version or a stepping stone towards implementing a fully functional malloc function. It serves as an intermediate step to understand the basic principles and concepts involved in memory allocation.
 The _malloc function in task 1 provides a more refined approach to memory allocation by considering the available memory and extending the heap accordingly. It avoids unnecessary heap extensions and optimizes memory usage compared to the first task_0.
Checking for available space: The first task_0 does not check for available space before allocating memory. This means that if there is not enough space available, the malloc() function will simply fail. The second task_1 checks for available space before allocating memory. If there is not enough space available, the malloc() function will try to extend the heap by calling the sbrk() system call. If the sbrk() system call fails, the malloc() function will return NULL.
Updating the available variable: The first task_0 does not update the available variable after allocating memory. This means that the amount of space that is still available on the heap will not be accurate. The task_1 updates the available variable after allocating memory. This ensures that the amount of space that is still available on the heap is always accurate.
Overall, the naive_malloc function provides a basic understanding of how memory allocation works by maintaining a chain of memory chunks and searching for unused chunks to satisfy allocation requests. However, it lacks some advanced features and optimizations that a fully functional malloc implementation would have, such as efficient memory management, fragmentation handling.
