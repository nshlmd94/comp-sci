// RECURSION EXAMPLE: Building a pyramid
// program that uses recursion 
// recursion needs a base case and a recursive case to work effectively and not loop indefinitely itself into a segmentation fault 
// This program demonstrates recursion by drawing a pyramid of # symbols
// Key concept: Recursion requires TWO things:
//   1. BASE CASE: A condition that stops the recursion (prevents infinite loop/segfault)
//   2. RECURSIVE CASE: The function calling itself with a simpler problem (moving toward base case)

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void draw(int n);

int main(void)
{
    int height = 0;
    printf("Enter a number.\n");
    scanf("%d", &height);

    draw(height); // Initial call - e.g., if user enters 4, this calls draw(4)
}

void draw(int n)
{
    // BASE CASE: Stop recursion when n reaches 0 or below
    // This prevents infinite recursion and stack overflow (segmentation fault)
    // Without this, the function would call itself forever!
    if(n <= 0)
    {
        return; // Exit immediately - don't do anything else
    }

    // RECURSIVE CASE: Call draw with a smaller value (n-1)
    // KEY INSIGHT: This line executes BEFORE the for-loop below
    // This means we go "all the way down" before printing anything
    //
    // Execution order for draw(4):
    //   draw(4) calls draw(3)
    //   draw(3) calls draw(2)
    //   draw(2) calls draw(1)
    //   draw(1) calls draw(0)
    //   draw(0) hits base case and returns
    //
    // Each call creates its own separate variable 'n' on the call stack
    // draw(4)'s n=4, draw(3)'s n=3, draw(2)'s n=2, etc. - all separate!
    draw(n-1);
    
    // IMPORTANT: Everything below this line executes AFTER the recursive call completes
    // This is why the for-loops execute in REVERSE order (bottom-up):
    //   draw(1) prints first: #
    //   draw(2) prints second: ##
    //   draw(3) prints third: ###
    //   draw(4) prints last: ####
    //
    // If you moved this for-loop ABOVE the draw(n-1) line, you'd get:
    //   ####
    //   ###
    //   ##
    //   #
    // (printing would happen top-down instead of bottom-up)
    for(size_t index = 0; index < n; index++)
    {
        printf("#"); // Print n number of # symbols
    }
    printf("\n"); // Newline after each row
}

/* 
 * RECURSION MENTAL MODEL:
 * 
 * Think of recursion like nested boxes:
 * 
 * draw(4) {
 *     [check base case - no]
 *     draw(3) {
 *         [check base case - no]
 *         draw(2) {
 *             [check base case - no]
 *             draw(1) {
 *                 [check base case - no]
 *                 draw(0) {
 *                     [check base case - YES! return] 
 *                 }
 *                  **FROM HERE IT PRINTS IN THIS ORDER BECAUSE draw(n-1) comes before the for loop, so it is ascending. If for loop was before draw(n-1), then it would execute in descending order.**
 *                 [now print 1 #]
 *             }
 *             [now print 2 #'s]
 *         }
 *         [now print 3 #'s]
 *     }
 *     [now print 4 #'s]
 * }
 * 
 * KEY TAKEAWAYS:
 * 1. Each function call gets its own copy of variables (separate n for each draw call)
 * 2. Function calls must complete before the next line executes (that's how all functions work)
 * 3. Position matters: Code BEFORE recursive call executes top-down (4→3→2→1→0)
 *                      Code AFTER recursive call executes bottom-up (1→2→3→4)
 * 4. Base case is essential - without it, infinite recursion → stack overflow → segfault
 * 5. Each recursive call should move closer to the base case (n-1 moves toward 0)
 */