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
It can be seen comparing the two images, that even though the regular Binary Search Tree map performs well on random set it completely fails on the linear set. The self-balancing RBT-Map perfomred much better on the linear set

![image](https://github.com/user-attachments/assets/16c53f86-14b5-4c00-a815-9e1c6f16e516)
![image](https://github.com/user-attachments/assets/90ff6b66-125c-4686-a54c-dba68399cb0c)

What suprised me is that the raw BST performed worse than the vecMap, so i will have to double-check the postpro
![image](https://github.com/user-attachments/assets/c9196ba0-034c-4558-88f7-7d63a9c68526)
