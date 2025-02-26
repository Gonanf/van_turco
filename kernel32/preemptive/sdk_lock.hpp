#ifndef KERNEL32_SDK_LOCK
#define KERNEL32_SDK_LOCK

//Redefining src/common/pico_sync/include/pico/lock_core.h in the pico sdk
#include"pico.h"
#define PICO_USE_MALLOC_MUTEX 1
#define lock_owner_id_t int8_t
#define LOCK_INVALID_OWNER_ID ((lock_owner_id_t)-1)
#include"./sdk_lock.cpp"

//#define lock_get_caller_owner_id() ((lock_owner_id_t)get_core_num())
#define lock_get_caller_owner_id() ((lock_owner_id_t)get_task_id())

//#define lock_internal_spin_unlock_with_wait(lock, save) spin_unlock((lock)->spin_lock, save), __wfe()
#define lock_internal_spin_unlock_with_wait(lock, save) spin_unlock((lock)->spin_lock, save), kernel_wait()

/*#define lock_internal_spin_unlock_with_best_effort_wait_or_timeout(lock, save, until) ({ \
    spin_unlock((lock)->spin_lock, save);                                                \
    best_effort_wfe_or_timeout(until);                                                   \
})*/
#define lock_internal_spin_unlock_with_best_effort_wait_or_timeout(lock, save, until) ({ \
    spin_unlock((lock)->spin_lock, save);                                                \
    kernel_wait_until(until);                                                   \
})

//#define sync_internal_yield_until_before(until) ((void)0)
#define sync_internal_yield_until_before(until) (kernel_wait();)

#endif