#include <iostream>
#include <vector>

class MemoryPool {
    struct Block {
        Block* next;
    };

    Block* freeList = nullptr;
    std::vector<void*> allocations;
    size_t blockSize;
    size_t blockCount;

public:
    MemoryPool(size_t blockSize, size_t blockCount)
        : blockSize(blockSize), blockCount(blockCount) {
        void* pool = std::malloc(blockSize * blockCount);
        allocations.push_back(pool);
        freeList = nullptr;

        // Split pool into blocks
        for (size_t i = 0; i < blockCount; ++i) {
            auto* block = (Block*)((char*)pool + i * blockSize);
            block->next = freeList;
            freeList = block;
        }
    }

    void* allocate() {
        if (!freeList) throw std::bad_alloc();
        void* result = freeList;
        freeList = freeList->next;
        return result;
    }

    void deallocate(void* ptr) {
        Block* block = (Block*)ptr;
        block->next = freeList;
        freeList = block;
    }

    ~MemoryPool() {
        for (void* mem : allocations)
            std::free(mem);
    }
};

struct MyStruct { int x, y; };

int main() {
    MemoryPool pool(sizeof(MyStruct), 100);

    MyStruct* a = static_cast<MyStruct*>(pool.allocate());
    a->x = 10; a->y = 20;

    pool.deallocate(a);
}
