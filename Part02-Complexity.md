# Findings
| Method         	| BSTtime (sec) 	| Big-O BST 	| HashTable time (sec) 	| Big-O HashTable 	| AVL time (sec) 	| Big-O AVL 	| 2-5 time (sec) 	| Big-O 2-5 	|
|----------------	|---------------	|-----------	|----------------------	|-----------------	|----------------	|-----------	|----------------	|-----------	|
| Search         	| 1.06e-04   	| O(n)      	| 7.52e-05          	| O(n)            	| 4.25e-05    	| O(logn) 	| 5.49e-05    	| O(logn) 	|
| Insert         	| 1.0e-04    	| O(n)      	| 6.47e-05          	| O(n)            	| 4.74e-05    	| O(logn) 	| 7.17e-05    	| O(logn) 	|
| Delete         	| 1.02e-04   	| O(n)      	| 6.85e-05          	| O(n)            	| 3.85e-05    	| O(logn) 	| 4.60e-05    	| O(logn) 	|
| Sort           	| 5.78e-03   	| O(n)      	| 1.56e-02          	| O(nlogn)      	| 1.79e-03    	| O(n)      	| 1.24e-03    	| O(n)      	|
| Range (k=10)   	| 5.67e-05   	| O(n)      	| 2.35e-03          	| O(n)            	| 6.23e-06    	| O(n)      	| 1.05e-04    	| O(n)      	|
| Range (k=100)  	| 4.35e-04   	| O(n)      	| 3.75e-03          	| O(n)            	| 2.48e-05    	| O(n)      	| 1.39e-04    	| O(n)      	|
| Range (k=1000) 	| 2.61e-03   	| O(n)      	| 6.15e-03          	| O(n)            	| 1.17e-04    	| O(n)      	| 1.61e-04    	| O(n)      	|

# Conclusions
- AVL search/insert/delete is faster than BST by about a factor of ten. This makes sense as we can expect AVL's time for these operations to always be at least as good as the BST timings. The reason that AVL isn't vastly superior in speed (as I first expected) is just because the BST did not degenerate to the worst case (a linked list) and thus performed well on average, and the Big-O is for worst-case. As for range and sort, we can see that AVL again performed better than the BST. This is probably just because the AVL is balanced and thus there aren't as many recursive traversals down the tree.

- 2-5 tree outperformed BST and was on par with AVL for search/insert/delete. This makes sense, since the 2-5 tree is also self-balancing, like the AVL tree. We can see the range function of the AVL outperformed the 2-5 tree for small n - I believe this is due to the fact that the AVL tree range algorithm seeks the root of the subtree containing the range of elements and then traverses it, avoiding many unnecessary comparisons. As n grows, the range subtree's root approach the root of the entire tree, and AVL range becomes very comparable to 2-5 tree range.

# Big-O reasoning
- AVL tree and 2-5 tree search/insert/delete is logn, because they are balanced binary trees which can traverse to the correct location of the search/insertion/deletion in logn time.
- AVL tree and 2-5 tree sort is n time, corresponding to a traversal of the n elements of the tree in-order.
- AVL tree and 2-5 tree range is also n time, since in the worst case range can encompass the entire tree and it again becomes an in-order traversal of all tree elements.
