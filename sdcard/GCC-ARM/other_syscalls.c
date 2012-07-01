/* Support files for GNU libc.  Files in the system namespace go here.
   Files in the C namespace (ie those that do not start with an
   underscore) go in .c.  */

#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>
#include <unistd.h>



/* Forward prototypes.  */
int     _system     _PARAMS ((const char *));
int     _rename     _PARAMS ((const char *, const char *));
int     isatty		_PARAMS ((int));
int     _isatty		_PARAMS ((int));
clock_t _times		_PARAMS ((struct tms *));
int     _gettimeofday	_PARAMS ((struct timeval *, struct timezone *));
void    _raise 		_PARAMS ((void));
int     _unlink		_PARAMS ((void));
int     _link 		_PARAMS ((void));
int     _stat 		_PARAMS ((const char *, struct stat *));
int     _fstat 		_PARAMS ((int, struct stat *));
int     _getpid		_PARAMS ((int));
int     _kill		_PARAMS ((int, int));
void    _exit		_PARAMS ((int));
int     _close		_PARAMS ((int));
int     _swiclose	_PARAMS ((int));
int     _open		_PARAMS ((const char *, int, ...));
int     _swiopen	_PARAMS ((const char *, int));
int     _swiwrite	_PARAMS ((int, char *, int));
int     _lseek		_PARAMS ((int, int, int));
int     _swilseek	_PARAMS ((int, int, int));
int     _read		_PARAMS ((int, char *, int));
int     _swiread	_PARAMS ((int, char *, int));
void    initialise_monitor_handles _PARAMS ((void));

static int	wrap		_PARAMS ((int));
static int	error		_PARAMS ((int));
static int	get_errno	_PARAMS ((void));
static int	remap_handle	_PARAMS ((int));
static int 	findslot	_PARAMS ((int));

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");


/* following is copied from libc/stdio/local.h to check std streams */
extern void   _EXFUN(__sinit,(struct _reent *));
#define CHECK_INIT(fp) \
  do                                    \
    {                                   \
      if ((fp)->_data == 0)             \
        (fp)->_data = _REENT;           \
      if (!(fp)->_data->__sdidinit)     \
        __sinit ((fp)->_data);          \
    }                                   \
  while (0)

/* Adjust our internal handles to stay away from std* handles.  */
#define FILE_HANDLE_OFFSET (0x20)

static int std_files_checked;
static int monitor_stdin;
static int monitor_stdout;
static int monitor_stderr;

/* Struct used to keep track of the file position, just so we
   can implement fseek(fh,x,SEEK_CUR).  */
typedef struct
{
  int handle;
  int pos;
}
poslog;

#define MAX_OPEN_FILES 1
static poslog openfiles [MAX_OPEN_FILES];

static int get_errno (void)
{
    return 0;
}

static int error (int result)
{
  errno = get_errno ();
  return result;
}

static int wrap (int result)
{
  if (result == -1)
    return error (-1);
  return result;
}

int _read (int file,
       char * ptr,
       int len)
{
  return 0;
}

int _lseek (int file,
	int ptr,
	int dir)
{
  return 0;
}


int _open (const char * path,
       int          flags,
       ...)
{
  return -1;
}

int _close (int file)
{
  return -1;
}

void _exit (int n)
{
  /* FIXME: return code is thrown away.  */
  while(1);
}

int _kill (int n, int m)
{
   return -1;
}


#include <sys/stat.h>

int _fstat(int file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _stat (const char *fname, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _link (void)
{
  return -1;
}

int _unlink (void)
{
  return -1;
}

void _raise (void)
{
  return;
}

int _getpid	(int n)
{
   return -1;
}


int _gettimeofday (struct timeval * tp, struct timezone * tzp)
{
  /* Return fixed data for the timezone.  */
  if (tzp)
    {
      tzp->tz_minuteswest = 0;
      tzp->tz_dsttime = 0;
    }

  return 0;
}

clock_t _times (struct tms * tp)
{
  clock_t timeval=0;

  if (tp)
    {
      tp->tms_utime  = timeval;	/* user time */
      tp->tms_stime  = 0;	/* system time */
      tp->tms_cutime = 0;	/* user time, children */
      tp->tms_cstime = 0;	/* system time, children */
    }
  
  return timeval;
};

int isatty (int fd)
{
  return 1;
  fd = fd;
}

int _isatty (int fd)
{
  return 1;
  fd = fd;
}

int _system (const char *s)
{
  if (s == NULL)
    return 0;
  errno = ENOSYS;
  return -1;
}

int _rename (const char * oldpath, const char * newpath)
{
  errno = ENOSYS;
  return -1;
}


