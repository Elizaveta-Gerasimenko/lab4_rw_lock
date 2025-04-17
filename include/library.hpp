#ifndef RWLock_H
#define RWLock_H

#include <atomic>
#include <thread>

namespace template_library {
    class RWSpinLock {
    private:
        std::atomic<uint32_t> counter{ 0 }; // младший бит - флаг записи, остальные - счетчик читателей

    public:
        void LockRead() {
            uint32_t expected;
            do {
                expected = counter.load(std::memory_order_relaxed);
                while (expected & 1) { // ждем, пока нет блокировки на запись
                    std::this_thread::yield();
                    expected = counter.load(std::memory_order_relaxed);
                }
            } while (!counter.compare_exchange_weak(expected, expected + 2,
                std::memory_order_acquire, std::memory_order_relaxed));
        }

        void UnLockRead() {
            counter.fetch_sub(2, std::memory_order_release);
        }

        void LockWrite() {
            uint32_t expected = 0;
            while (!counter.compare_exchange_weak(expected, 1,
                std::memory_order_acquire, std::memory_order_relaxed)) {
                expected = 0;
                std::this_thread::yield();
            }
        }

        void UnLockWrite() {
            counter.store(0, std::memory_order_release);
        }
    };
}

#endif // RWLock_H