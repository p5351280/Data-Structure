Your Student ID: 404410053
Your Name: ±iºÓ®¦

Your complie command:
gcc -Wall 1.c -o 1
gcc -Wall 2.c -o 2
gcc -Wall 3.c -o 3

Brief explanation of how to use your program.
For problem 1 and 2, just input the file name of text file, it will give you the min spanning tree.
For problem 3, expect the file name, you should also give the program the start vertex and the end vertex.
It will help you to find the min road.
To compile three problem, just use makefile to help you.

Describe the problems you meet during the homework and how do you solve it.
This time, I try to use fgets to get the file name, but it has a problem.
Using gets won't have a '\n' in the string, 
but for fgets it will put a '\n' end of the string if the strlen is less than the string array size.
It will make the program can't find the file success.
So, I try to use strchr to find '\n' and replace it with '\0', and so the program read the file success.
And when doing the third problem, I find that I'm not so familiar with Dijkstra, so I read the book and search on the net.
After doing this problem, I'll think that Dijkstra isn't so difficult.

