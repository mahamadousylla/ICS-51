/*
	ICS 51. Lab #3

	IMPORTATNT NOTES:

	- Noramally, the compiler adds the prologue/epilogue code for the callee. However, when the
	__declspec(naked) attribute is used, it is the programmer's responsibility to write the
	prologue/epilogue code. In this lab you need to write prologue/epilogue code sections only
	for the functions that have been declared with the naked attribute, namely:

	   + findMinIndex
	   + recFactorial
	   + performOperation
	   + fibonacci

	- You cannot define any local variable in the C code. If you need additional variables in your
	assembly code, you have to allocate space for them in the prologue of the function.

	- You are not allowed to change anything in this file except for adding your assembly code
    between the lines marked "BEGIN YOUR CODE HERE" and "END YOUR CODE HERE".

	- Remember to fill in your name, student ID below.

	- ONLY submit the lab3.c file for grading.

*/

char *yourName = "Mahamadou Sylla";
char *yourStudentID = "61549479";

/***********************************************************************************************

	PART 1: Selection Sort

	Selection sort is an in-place comparison sort algorithm that works by dividing the input list
	into two parts: the sublist of items already sorted, which is built up from left to right of
	the list, and the sublist of items remaining to be sorted that occupy the rest of the list.
	Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
	The algorithm proceeds by finding the smallest element in the unsorted sublist, exchanging it
	with the leftmost unsorted element (putting it in sorted order), and moving the sublist
	boundaries one element to the right. To learn more, read:
	https://en.wikipedia.org/wiki/Selection_sort#Example

	Our implementation here uses a function called "findMinIndex" to find the index of smallest
	element between ith index and jth index of the array. The function "selectionSort" uses
	this function to find the smallest number and exchanges it with the leftmost unsorted element
	in each iteration. You need to implement the behavior of both functions in x86 assembly.

************************************************************************************************/

__declspec(naked)
int findMinIndex (int integer_array[], int i, int j)
{

// C code to be converted to x86 assembly
/*
    int iMin = i;
    // test against elements after i and before j to find the smallest
    for ( i ; i < j; i++) {
        // if this element is less, then it is the new minimum
        if (integer_array[i] < integer_array[iMin]) {
            // found new minimum; remember its index
            iMin = i;
        }
    }

    return iMin;
*/

	__asm{
			// BEGIN YOUR CODE HERE
push ebp
mov ebp, esp
push esi
push edi
push edx
jmp MoveReg
MoveReg:
	mov edx, [12 + ebp]
	mov ecx, [8 + ebp]
	mov eax, [16 + ebp]
	mov ebx, edx
	jmp Start
Start:
	cmp eax, edx
	jle End
	mov edi, [ecx + 4 * edx]
	mov esi, [ecx + 4 * ebx]
	cmp esi, edi
	jle Next
	mov ebx, edx
Next:
	add edx,1
	jmp Start
End:
	mov ecx, ebx
	pop edx
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
			// END YOUR CODE HERE
			ret
	}

}

void selectionSort (int integer_array[], int array_size)
{

// C code to be converted to x86 assembly
/*
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size-1; j++) {

		// find the index of min element in the unsorted a[j .. n-1] //
 		iMin = findMinIndex (integer_array, j, array_size);

		if(iMin != j) { // swap values
			temp = integer_array[iMin];
			integer_array[iMin] = integer_array [j];
			integer_array[j] = temp;
		}
	}
*/

	__asm{
			// BEGIN YOUR CODE HERE
mov edi, integer_array
mov ebx, array_size
dec ebx
xor esi, esi
First:
	cmp esi, ebx
	jge End
	push ecx
	push eax
	push ebx
	mov edx, array_size
	push edx
	push esi
	push edi
	call findMinIndex
	jmp Increment
Increment:
    add esp, 12
	mov edx, ecx
	pop ebx
	pop eax
	pop ecx
	cmp edx, esi
	je NextLoop
	mov ecx, [edi + 4 * edx]
	mov eax, [edi + 4 * esi]
	xor ecx, eax
	xor eax, ecx
	xor ecx, eax
	mov[edi + 4 * edx], ecx
	mov[edi + 4 * esi], eax
NextLoop:
	inc esi
	jmp First
End:
	mov integer_array, edi
			// END YOUR CODE HERE
	}

}

/***********************************************************************************************

    PART 2: Recursive Factorial

	Implement two functions that calculates the factorial of an integer not greater than 12.

	The 1st function, factorial (unsigned int input, unsigned int *output), is the non
	recursive wrapper function which takes the input, sets up the stack, calls the recursive
	function and finally puts the result in the location pointed to by the pointer argument called
    output.

	The 2nd function, recFactorial(unsigned int n), is the recursive function that actually
	calculates the factorial.

	Given an unsigned integer number n,we define FACTORIAL(n) as:

        FACTORIAL(n) =  1                   ,    if n = 0 or n = 1
                        n * FACTORIAL(n-1)  ,    if n > 1

	Tip:

	- You need to use IMUL instruction to multiply unsigned integers. Learn how to use it:
	http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#instructions

************************************************************************************************/

__declspec(naked)
unsigned int recFactorial (unsigned int n)
{

// C code to be converted to x86 assembly
/*
	if (n<=1)
		return 1;
	else
		return n * recFactorial(n-1);
*/

	__asm{
			// BEGIN YOUR CODE HERE
push ebx
mov ebx, esp
push ecx
dec esp
dec esp
dec esp
dec esp
mov eax, [8 + ebx]
cmp eax, 0
jne NextLoop
add eax, 1
jmp AnotherLoop
NextLoop:
	cmp eax, 1
	jle AnotherLoop
	mov edi, eax
	dec eax
	push edi
	push eax
	call recFactorial
	jmp Increment
Increment:
	inc esp
	inc esp
	inc esp
	inc esp
	pop edi
	mul edi
AnotherLoop :
	pop ecx
	mov esp, ebx
	pop ebx
			// END YOUR CODE HERE
			ret
	}

}

void factorial (unsigned int input, unsigned int *output)
{

// C code to be converted to x86 assembly
/*
	*output = recFactorial (input);
*/

	__asm{
			// BEGIN YOUR CODE HERE
push input
mov edx, input
call recFactorial
inc esp
inc esp
inc esp
inc esp
mov edi, output
mov dword ptr[edi], eax
			// END YOUR CODE HERE
	}

}

/***********************************************************************************************

    PART 3: Vector Operation

	The vectorOperations function gets as parameters 4 arrays of the same length and
	the number of elements in those arrays.

	For each pair of elements in first_array and second_array, it calls performOperation
	and stores the returned result in the same index of output_array.

	output_array[index] = performOperation(operation_array[index], first_array[index], second_array[index]).

	You also need to implement the body of performOperation function according to the provided
	C code.

************************************************************************************************/

__declspec(naked)
int performOperation (int operation, int first, int second)
{

// C code to be converted to x86 assembly
/*
	if (operation==0)
		return first + second;
	else if (operation==1)
		return first - second;
	else if (operation==2)
		return (first > second)? first : second;
	else if (operation==3)
		return (first < second)? first : second;
	else
		return first;
*/

	__asm {
			// BEGIN YOUR CODE HERE
push ebp
mov ebp, esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
dec esp
mov eax, [16+ebp]  
mov ebx, [12+ebp] 
mov ecx, [8+ebp]
cmp ecx, 0
jne BeginLoop
ADD ebx, eax
BeginLoop:
	cmp ecx, 1
	jne NextLoop
	sub ebx, eax
NextLoop:
	cmp ecx, 2
	jne Fib
	cmp eax, ebx
jae NestedLoop
	jmp Fib
	NestedLoop:
	mov ebx, eax
	Fib:
	cmp ecx, 3
	jne EndofLoops
	cmp eax, ebx
	je AnotherNestedLoop
	jmp EndofLoops
AnotherNestedLoop:
	mov ebx, eax
EndofLoops:
	pop ecx
	mov esp, ebp
	pop ebp
			// END YOUR CODE HERE
			ret
	}

}

void vectorOperations (int number_of_elements, int *first_array, int *second_array,
					   int *operation_array, int *output_array)
{
// C code to be converted to x86 assembly
/*
	int i;
	for (i=0; i<number_of_elements; i++)
	{
		output_array[i] = performOperation(operation_array[i], first_array[i], second_array[i]);
	}
*/

	__asm {
			// BEGIN YOUR CODE HERE
mov edx, 0
BeginLoop:
	cmp edx, number_of_elements
	jae EndofLoop
	push edx
	mov edi, edx
	shl edi, 2   
	mov ecx, second_array
	add ecx, edi
	push[ecx] 
	mov ecx, first_array
	add ecx, edi
	push[ecx] 
	mov ecx, operation_array
	add ecx, edi
	push[ecx]
	call performOperation
	jmp Increment
Increment:
	inc edx
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	inc esp
	pop ecx
	mov ecx, output_array
	add ecx, edi
	mov dword ptr[ecx], ebx
	jmp BeginLoop
EndofLoop:
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 4: Change Letter Case

	You are given an array of characters (a string) that may contain numbers, upper and	lower case
    letters, punctuations symbols, etc. Implement a function to convert all uppercase letters to
    lowercase and vice versa.
    For example "ThisIsTheFinalLabOf51" should be converted to "tHISiStHEfINALlABoF51".
	The function has the following argument: An array of charaters and the size of the array. The
	array should be changed in place. There is no explicit output for this function.

	Tips:

	- Note that each element of the arrays is a char (1 byte). You can NOT use a 32-bit registersss
	to read/write from/to a memory location. Instead you should use the 8-bit version of the x86
	general-purpose registers.
	More info: http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#registers

	- The link to the ascii codes is here: http://www.asciitable.com/

************************************************************************************************/

void changeCase (char char_array[], int array_size ) {

	__asm{
			// BEGIN YOUR CODE HERE
mov ebx, 0
mov ecx, char_array
BeginLoop:
	cmp ebx, array_size
	jae EndofLoop
	mov al, byte ptr[ebx + ecx]
	cmp al, 64
	jle NextLoop
	cmp al, 123
	xor al, 32
	mov byte ptr[ebx + ecx], al
NextLoop:
	inc ebx
	jmp BeginLoop
EndofLoop:
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 5: Fibonacci

	Implement a recursive function in assembly which returns the Nth number in the fibbonaci
	series (1, 1, 2, 3, 5, 8, ...).

************************************************************************************************/

__declspec(naked)
unsigned int fibonacci (unsigned int n) {

// C code to be converted to x86 assembly
/*
	if (n < 2)
		return 1;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
*/

	__asm{
			// BEGIN YOUR CODE HERE
push ebp
mov ebp, esp
push esi
push edi
push ebx
jmp BeginLoop
BeginLoop :
	mov ebx, [8 + ebp]
	cmp ebx, 2
	jge NextLoop
	mov eax, 1
	jmp END
NextLoop:
	push eax
	push eax
	mov eax, ebx
	sub eax, 1
	push eax
	call fibonacci
	jmp Increment
Increment:
	inc esp
	inc esp
	inc esp
	inc esp
	jmp AnotherLoop
AnotherLoop:
	mov edi, eax
	mov eax, ebx
	dec eax
	dec eax
	push eax
	call fibonacci
	jmp AnotherIncrement
AnotherIncrement:
	inc esp
	inc esp
	inc esp
	inc esp
	jmp Continue
Continue:
	mov esi, eax
	pop eax
	pop eax
	mov eax, edi
	add eax, esi
END:
	pop ebx
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
			// END YOUR CODE HERE
			ret
	}
}
