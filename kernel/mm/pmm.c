/**********************************************************************
 *                  Physical Memory Manager
 *
 *
 *  This file is part of Aquila OS and is released under the terms of
 *  GNU GPLv3 - See LICENSE.
 *
 *  Copyright (C) 2016 Mohamed Anwar <mohamed_anwar@opmbx.org>
 */

#include <core/system.h>
#include <core/qsort.h>
#include <boot/boot.h>
#include <mm/mm.h>
#include <mm/buddy.h>

char *kernel_heap = NULL;

void pmm_setup(struct boot *boot)
{
    printk("Total memory: %d KiB, %d MiB\n", boot->total_mem, boot->total_mem / 1024);

    arch_pmm_setup();

    buddy_setup(boot->total_mem * 1024);
}