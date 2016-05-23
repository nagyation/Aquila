#ifndef _MM_H
#define _MM_H

#include <core/system.h>

#if ARCH==X86
#include <arch/x86/include/mm.h>
#endif

/* Physical Memory Manager interface */

#define KR	_BV(0)	/* Kernel Read */
#define KW	_BV(1)	/* Kernel Write */
#define KX	_BV(2)	/* Kernel eXecute */
#define KRW	(KR|KW)	/* Kernel Read/Write */
#define KRX	(KR|KX)	/* Kernel Read/eXecute */
#define KWX	(KW|KX)	/* Kernel Write/eXecute */
#define KRWX	(KR|KW|KX)	/* Kernel Read/Write/eXecute */


#define UR	_BV(3)	/* User Read */
#define UW	_BV(4)	/* User Write */
#define UX	_BV(5)	/* User eXecute */
#define URW	(UR|UW)	/* User Read/Write */
#define URX	(UR|UX)	/* User Read/eXecute */
#define UWX	(UW|UX)	/* User Write/eXecute */
#define URWX	(UR|UW|UX)	/* User Read/Write/eXecute */

typedef struct
{
	int		(*map)(uintptr_t addr, size_t size, int flags);
	void	(*unmap)(uintptr_t addr, size_t size);
	void*	(*memcpypp)(void *phys_dest, void *phys_src, size_t n);	/* Phys to Phys memcpy */
	void*	(*memcpypv)(void *virt_dest, void *phys_src, size_t n);	/* Phys to Virt memcpy */
	void*	(*memcpyvp)(void *phys_dest, void *virt_src, size_t n);	/* Virt to Phys memcpy */
} pmman_t;

extern pmman_t pmman;

#endif /* !_MM_H */