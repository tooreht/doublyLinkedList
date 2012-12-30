# C Doubly Linked List

This is an implementation of a doubly linked list in the C programming language.

The current features of my implementation are:

- create dll
- traverse dll
- search dll
- create node
- add first node
- add begin
- add end
- add after
- free node
- delete
- delete first
- delete last
- destroy dll
- reverse dll
- sort dll
- print dll

The file interactive.c provides a little command line like interface to test the features:

Usage:

print (p)  print the list
info		print list info
reverse		reverse the list
sort		sort the list in ascending order
delf		delete the first node
dell		delete the last node
destroy		delete the whole list

beg 1		add an integer to the beginning of the list
end 1		adds an integer to the end of the list
find 1		searche after an integer in the list
del 1		delete an integer in the list
performance 10	do some performance testing with a number of elements

after 1 2	add integer 2 after integer 1 in the list
fill 10 20	fill the list with integers from 10 to 20
