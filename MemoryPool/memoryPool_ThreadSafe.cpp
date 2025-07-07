#include <iostream>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <thread>

class ThreadSafeMemoryPool {
    struct Block {
        Block* next;
    };

    Block* freeList = nullptr;
    void* pool;
    size_t blockSize;
    size_t blockCount;
    std::mutex mtx;

public:
    ThreadSafeMemoryPool(size_t blockSize, size_t blockCount)
        : blockSize(blockSize > sizeof(Block*) ? blockSize : sizeof(Block*)), blockCount(blockCount) {
        pool = std::malloc(blockSize * blockCount);

        // Initialize free list
        freeList = nullptr;
        for (size_t i = 0; i < blockCount; ++i) {
            auto* block = (Block*)((char*)pool + i * blockSize);
            block->next = freeList;
            freeList = block;
        }
    }

    void* allocate() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!freeList) {
            throw std::bad_alloc();
        }

        void* result = freeList;
        freeList = freeList->next;
        return result;
    }

    void deallocate(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        auto* block = (Block*)ptr;
        block->next = freeList;
        freeList = block;
    }

    ~ThreadSafeMemoryPool() {
        std::free(pool);
    }
};

struct MyObject {
    int x, y;
};

int main() {
    ThreadSafeMemoryPool pool(sizeof(MyObject), 1000);

    auto task = [&pool]() {
        for (int i = 0; i < 100; ++i) {
            MyObject* obj = static_cast<MyObject*>(pool.allocate());
            obj->x = i;
            obj->y = i * 2;
            pool.deallocate(obj);
        }
        };

    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();

    std::cout << "Done.\n";
    return 0;
}
