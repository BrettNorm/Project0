This program makes a ternary tree out of text and then traverses them inorder, preorder, and postorder. 

- With 0 arguments [./P0], it will read from the keyboard, put the text into an output file, make a ternary tree
from said text, traverse it in those 3 ways, and output into output.inorder, output.preorder, and 
output.postorder. 

- With 1 argument [./P0 test], it will search for a file with the name 'test' with the extension ".sp2022"
at the end of it. It will read text from that file, make a ternary tree, traverse, and then output into
test.inorder, test.preorder, and test.postorder. 

- With 2 arguments [./P0 w text.sp2022], it will create a file (add to an existing one), make a ternary tree
from that text, and output in into output.inorder, output.preorder, and output.postorder.

- Invocation: 
    - [./P0] to input text from keyboard
    - [./P0 test] to read from 'input.sp2022'
    - [./P0 w text.sp2022] to write to 'text.sp2022' and output into output files


- Problems: 
    - Function doesn't behave if using '<' in "./P0 < somefile.sp2022". I use w instead, but any character or string would work. 
    - My linked list is backwards. I spent too much time on different errors, somehow flipped it, and I am out of time to try to reverse it back. 



- I spent two days on an error that randomly popped up after not having changed any code whatsoever. 
When calling buildTree, my file pointer would just go straight to the end of the file. BUT, 
it only did it when argc = 2. If I used different invocations of the program? It would work
perfectly fine. What finally fixed was just rewinding my file pointer right before I accessed
it in buildTree. 
    - Undoubtedly the most frustrating experience I have ever had. 
