# 11512 GATTACA
Our approach to this question involves,

1.) Create a suffix array for the given string
2.) Sort the suffixes lexigraphically, then find the longest common prefix. (LCS) shared by at least two suffixes,  by comparing the current array with the previous.
3.) We then use the Knuth Morris Pratt (KMP) pattern matching algorithm to find the count 
of the prefix we found at step 2. 
4.) Return the prefix, and the count 

For Example.

GAGAGAG

the suffix array is

AG
AGAG
AGAGAG
G 
GAG 
GAGAG 
GAGAGAG 

the longest prefix shared by at least two suffix is GAGAG ,

Now we use the KMP algorithm to find the number of suffixs begin with GAGAG, which returns 2
