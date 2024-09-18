
CLI program in C++
=====================
Written as an exercise 12.27 - 12.28 from the textbook The C++ Primer (5th Edition) 
by Stanley B. Lippman, Josée Lajoie, and Barbara E. Moo

What we learn here
---------------------
To use the standard C++ library.

What the program does (user perspective)
---------------------------------------------
-lets a user search a file for words that occur in it
-result output example when querying for word "object":
$ ./query file01.txt
enter word to look for, or q to quit: object
occurs 2 times on these lines:
(line 2) if the TextQuery object is destroyed before a corresponding QueryResult? In
(line 3) that case, the QueryResult would refer to data in an object that no longer exists.

So: total num of occurrences, line numbers where the word occurs, text of that line
(if multiple such words on a line, that line is displayed only once 
(I assume that counted also once)).
(Lines appear ordered.)

Design of the Query Program
----------------------------------
(Tip: A good way to start the design of a program is to list the program's operations.
It will help to decide on the data structures.)
---Operations overview
-read input line by line, word by word in each line
-associate line numbers with words (nu duplicates of lines)
-retrieve line content for each line number

---Implementation details
(Library facilities and data structures)
-vector<string> to store a copy of the entire input file, line per index.
(fetch lines content by indexing this vector)
-use istringstream to get words from a line
-use map to associate {word, set<int> of line numbers}

---Two classes
(1) TextQuery
-Reads and stores the file into a vector, builds the query map.
-Constructor of this class performs this job: takes a filename, builds vector, map.
(2) QueryResult
-Holds the result of a query:
/set of line numbers (for the given word), 
/actual text of these lines.
These data are stored in objects of the 1st class type TextQuery.
Its "print" function prints the results.



















