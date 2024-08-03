Simple cpp project to compare Binary-Search map, Red-Black-Tree map and a std::map. I added the naive vector map as a reference. Served me as a study resource for implementing data structures. 

All code is based on the wikipedia articles, cpp-reference map page:
https://en.wikipedia.org/wiki/Binary_search_tree
https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
https://en.cppreference.com/w/cpp/container/map
Written mainly by me with some ai help for debugging.

For iterators i used information provided here:
https://internalpointers.com/post/writing-custom-iterators-modern-cpp
and given in great talk "Back to Basics: Designing Classes (part 2 of 2)" by Klaus Iglberger at CppCon 2021
https://youtu.be/O65lEiYkkbc?si=d5mmcYcY6c_2-7b5

I tested the maps on setSizes = {1000, 5000, 10000, 20000, 30000, 40000, 50000}. For each set i did 100 runs of inserts and searches to sample mean and standard deviation for postprocessing. I generated 3 types of key sets: linear (1,2,3...,n), linearRev(n,n-1,...1) and random. 

Some example results, that i will maybe format if i find any free time. I should do it propely and come up with a better measure than time, as better data structure should be 'higher' on the plot. Well thats a future TODO :) .
It can be seen comparing the two images, that even though the regular Binary Search Tree map performs well on random set it completely fails on the linear sets. The self-balancing mechanism in RBTMap solves those issues and it can be noticed that the rand set takes the longest to insert/search.

![image](https://github.com/user-attachments/assets/03aa6556-8861-473c-b149-d2b5172712d9)
![image](https://github.com/user-attachments/assets/61a5e9f1-bf07-4f23-95f4-15bf1c0c5378)

![image](https://github.com/user-attachments/assets/b1c60575-d4f1-4e26-b584-139ef44d8609)
![image](https://github.com/user-attachments/assets/24c76d2c-5413-4ec5-9129-7fd7e57271e3)

Comparing those maps i get to a conclusion that if the linear patterns appear in ones dataset it is absolutely crucial to implement self-balancing mechanism into a tree data structure. Even on the rand set the balanced maps performed better. The simple vector map turned out to be more efficient than the BSTMap on the linear sets as it iterates through continous memory. The BSTMap on linear set becomes a linked-list and has to follow pointers what leads to cache misses and unnecessary overhead.

Coding those map templates I got an idea to implement a new map based on both the vector and RBT structure. One could utilize the efficient continous memory block that vectors have and the self-balancing tree structure erricient lookup. The MapNode in such structure would hold references to left/right/parent as vector ids. But thats just an idea for futrure project.
