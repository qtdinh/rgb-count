# rgb-count
Counts RGBA pixels in a bitmap using front-back linear search as well as checking the previous pixel.

##Description
This was a student project for advanced computer architecture. 
The purpose of this program was to search a bitmap and count the number of pixels that match a set of colors (64 entries).

##Thoughts
My solution used a front and back linear search along with comparing the pixel to the previous one. 
This is not the most optimal solution, but at the time I wasn't well-versed with data structures.
Other better solutions include using a hashmap or a binary search.
