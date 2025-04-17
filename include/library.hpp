#ifndef RWLock_H
#define RWLock_H

#include <atomic>

namespace template_library {
    class RWSpinLock {
    public:
        void LockRead() {
        }

        void UnlockRead() {
        }

        void LockWrite() {
        }

        void UnlockWrite() {
        }
    };
}

#endif // RWLock_H
