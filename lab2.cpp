//
//	ICS 51, Lab #2
//
//	-----------------------------------------------------------------
// 
//	IMPORTATNT NOTES:
//	
//	- To test your code use the tests in lab2-testing.cpp
//	
//	- Write your assembly code only in the marked blocks.
//	
//	- Do NOT change anything outside the marked blocks.
//
//	- Remember to fill in your name, student ID below.
// 
//	- This lab has to be done individually.
//
//  - Use lodepng.h and lodepng.cpp to read/write png files.
//
//  - Two test images are provided to you.
//	
//	- Submit ONLY lab2.cpp file for grading.
// 


char *yourName = "Mahamadou Sylla";
char *yourStudentID = "61549479";


//
// This function should takes in a square sized grayscale image and applies thresholding on each pixel.
// Width and height of the image are equal to dim.
// NOTE: you can't define additional variables.
//
void imageThresholding(unsigned char* image, int dim) {
	
	__asm {
    
// YOUR CODE STARTS HERE
mov eax, dim
mul dim
mov ebx, image
mov ecx, 0

BeginLoop:
	cmp eax, ecx
	jle EndofLoop
	mov dl, byte ptr[ebx + ecx]
	cmp dl, 0x80
	jae NextLoop
	mov dl, 0x00
	mov byte ptr[ebx + ecx], dl
	inc ecx
	jmp BeginLoop
NextLoop:
	mov dl, 0xFF
	mov byte ptr[ebx + ecx], dl
	ADD ecx, 1
	jmp BeginLoop

EndofLoop:
// YOUR CODE ENDS HERE
	
  }
}



// This function flips an square iamge of given dimension horizontally/vertically.
// Width and height of the image are equal to dim.
// if direction is 0, image should be flipped horizontally
// otherwise image should be flipped vertically.
//
//
// Two variables are definde to help you with implemetanion.
// NOTE: you can't define additional variables.
//
void imageFlip(unsigned int* image, int dim, int direction) {
  
  unsigned int a_p, a_p_m;
  
  __asm {
    
// YOUR CODE STARTS HERE

// YOUR CODE ENDS HERE
  
  }
  
}