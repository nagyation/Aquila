#include <core/system.h>
#include <core/arch.h>
#include <sys/proc.h>

#include "sys.h"

void arch_spawn_proc(proc_t *init)
{
	x86_proc_t *arch = init->arch;
	printk("Spawning: %s (%d) [IP: %x, SP: %x, F: %x, KSTACK: %x]\n", init->name, init->pid, arch->eip, arch->esp, arch->eflags, arch->kstack);
	
	switch_page_directory(arch->pd);

	x86_set_kernel_stack(arch->kstack);

	extern void x86_jump_user(uintptr_t eip, uintptr_t cs, uintptr_t eflags, uintptr_t esp, uintptr_t ss);
	x86_jump_user(arch->eip, X86_CS, arch->eflags, arch->esp, X86_SS);
}

void arch_init_proc(void *d, proc_t *p, uintptr_t entry)
{
	x86_proc_t *arch = kmalloc(sizeof(x86_proc_t));
	struct arch_load_elf *s = d;

	arch->pd = s->new;

	uintptr_t kstack_base = (uintptr_t) kmalloc(KERN_STACK_SIZE);
	arch->kstack = kstack_base + KERN_STACK_SIZE;	/* Kernel stack */
	arch->eip = entry;
	arch->esp = USER_STACK;
	arch->eflags = X86_EFLAGS;

	p->arch = arch;
}

void arch_switch_process(proc_t *proc)
{
	x86_proc_t *arch = proc->arch;
	printk("Switching %s (%d) [KSTACK: %x, EIP: %x, ESP: %x, EBP: %x]\n", proc->name, proc->pid, arch->kstack, arch->eip, arch->esp, arch->ebp);
	
	switch_page_directory(arch->pd);

	x86_set_kernel_stack(arch->kstack);

	extern void x86_goto(uintptr_t eip, uintptr_t ebp, uintptr_t esp) __attribute__((noreturn));
	x86_goto(arch->eip,  arch->ebp, arch->esp);
}