/* Support files for GNU libc.  Files in the system namespace go here.
   Files in the C namespace (ie those that do not start with an
   underscore) go in .c.  */

#include <unistd.h>
#include <errno.h>

#undef errno
extern int errno;

#define FreeRTOS
#define MAX_STACK_SIZE 0x200
#define VTOR 0xE000ED08

#ifndef FreeRTOS
  register char * stack_ptr asm("sp");
#endif

caddr_t _sbrk		_PARAMS ((int));

caddr_t _sbrk(int incr)
{
	extern char end asm("end");
	static char *heap_end;
	char *prev_heap_end,*min_stack_ptr;

	if (heap_end == 0)
		heap_end = &end;

	prev_heap_end = heap_end;

#ifdef FreeRTOS
	/* Use the NVIC offset register to locate the main stack pointer. */
	min_stack_ptr = *(unsigned int *)(*(unsigned int *)VTOR);
	/* Locate the STACK bottom address */
	min_stack_ptr -= MAX_STACK_SIZE;

	if (heap_end + incr > min_stack_ptr)
#else
	if (heap_end + incr > stack_ptr)
#endif
	{
//		write(1, "Heap and stack collision\n", 25);
//		abort();
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}
 	
