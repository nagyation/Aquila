#ifndef _PROC_H
#define _PROC_H

#include <core/system.h>
#include <fs/vfs.h>

#if ARCH==X86
#include <arch/x86/include/proc.h>
#endif

#define FDS_COUNT	64

typedef struct
{
	inode_t *inode;
	size_t  offset;
} file_list_t;

typedef enum 
{
	RUNNABLE,
	ISLEEP,	/* Interruptable SLEEP (I/O) */
	USLEEP,	/* Uninterruptable SLEEP (Waiting for event) */
	ZOMBIE,
	STOPPED,
} state_t;

typedef struct proc proc_t;
struct proc
{
	char		*name;
	int 		pid;	/* Process identifier */
	state_t		state;
	file_list_t *fds;	/* Open file descriptors */
	proc_t 		*parent;
	char 		*cwd;	/* Current Working Directory */
	void		*heap;	/* Process heap pointer */

	void		*arch;	/* Arch specific data */

	/* Process flags */
	int			spawned : 1;

	proc_t 		*next;	/* Processes queue next pointer */
} __attribute__((packed));

proc_t *load_elf(const char *fn);
int get_pid();
int get_fd(proc_t *proc);

/* sys/fork.c */
proc_t *fork_proc(proc_t *proc);

void init_process(proc_t *proc);
proc_t *execve_elf(proc_t *proc, const char *fn, char * const argv[], char * const env[]);

#endif /* !_PROC_H */