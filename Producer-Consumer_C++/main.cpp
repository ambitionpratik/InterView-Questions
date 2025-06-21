#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;

const unsigned int MAX_BUFFER_SIZE = 5;
bool done = false;

void producer(int id) {
    for (int i = 1; i <= 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << "\n";
        lock.unlock();

        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    lock.unlock();
    cv.notify_all();
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty() || done; }); // Unlock the lock and wait untill condition fulfill

        if (!buffer.empty()) {
            int val = buffer.front();
            buffer.pop();
            std::cout << "Consumer " << id << " consumed: " << val << "\n";
        } else if (done) {
            break;
        }

        lock.unlock();
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    std::thread prod1(producer, 1);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);

    prod1.join();
    cons1.join();
    cons2.join();

    std::cout << "All done.\n";
    return 0;
}
