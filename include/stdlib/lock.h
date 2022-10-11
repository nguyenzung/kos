#ifndef LOCK_H
#define LOCK_H

#define DECLARE_LOCK(name) volatile int name ## Locked
#define INIT_LOCK(name) name ## Locked = 0
#define LOCK(name) \
	while (!__sync_bool_compare_and_swap(& name ## Locked, 0, 1)); \
	__sync_synchronize();
#define UNLOCK(name) \
	__sync_synchronize(); \
	name ## Locked = 0;

#endif