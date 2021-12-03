
Samantha Scholz
README Completed: 4/3/20

Struct for BNode:
	-prepares word and line number data to be inserted into a binary search tree
Main:
	-get command line input for source file
	-read dictionary file "dict.txt"
	-make a hashtable with the proper size for number of words being hashed
	-want a load factor of .5 
	-size is automatically doubled so I input the number of words plus 100 to account
	for words being added to the dictionary in the future
	-create Binary search tree object to hold last instance of misspelled words and 
	their respective line numbers
	-get data from source file
	-while loop controls line number
	-for loop controls collecting words from the line
	-while loop within the for controls collecting chars to form words avoiding symbols
	using a " " as a delimiter
	-once a word is made(a space is reached), it is compared to the hashtable using the 
	find function
	-if the word is not found the menu function is called
	-after the word is evaluated, it is cleared and sent back through the for and while 
	loop until end of line is reached
	-once end of line is reached, line counter is increased and the while loop continues
	until end of file is reached
	-after exiting the end of file while loop, the BST is sent to the outfile "notfound.txt"
Menu function:
	-user choice is received and used in a switch statement
	-case a: inserts word into dictionary hash table
	-case i: ignores the word and future cases of the word by adding it to the ignored 
	hashtable
	-case g: does nothing (breaks switch statement)
	-case s: tests for suggested spellings by switching adjacent letters in a while loop
	 and comparing the results to the dictionary hashtable using the find function
		-this is implemented by having 2 char variables that get assigned adjacent
		values and then are swapPed using concatonation of string objects and substr
		-the while loop contains 3 if statements
			-1 case: index does not equal 0
			-another case: index less than the word length minus two
			-if the temporary word is found in the hash table, report it to the user
	-if found it prompts the user to press enter to continue
	-case q: calls an exit funciton and sends the BST data to outfile "notfound.txt"
	-default case: displays an error message and makes a recursive call to the menu
	function
HashTable:
	-used to hold dictionary words and ignored words
	-find function used to determine if the words are in the dictionary or have been ignored
	-handles collisions and folding during insertions
BST:
	-organizes and sorts not found data
	-has a printTree function that was used to send the tree data to the output file
