#include <bits/stdc++.h>
using namespace std;

multimap<long int, function<void()>> tasks;
mutex m;
atomic<bool> done{ false };

void ExecuteTask() {

    while (!done || !tasks.empty()) {
        auto now = std::chrono::system_clock::now();
        auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count();

        unique_lock<mutex> lock(m);

        for (auto it = tasks.begin(); it != tasks.end(); ) {
            if (it->first == now_seconds) {
                cout << "Time while executing the task -->" << now_seconds << endl;
                auto task = it->second;
                task();
                it = tasks.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void AddTask() {
    int cnt{ 1 };

    while (cnt <= 10) {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed
        int randomNumber = 1 + std::rand() % 5;

        auto now = std::chrono::system_clock::now();
        auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count();

        unique_lock<mutex> lock(m);

        tasks.insert(make_pair(now_seconds + randomNumber, [now_seconds, randomNumber]() {
            cout << "----------" << endl;
            cout << "Task executed on " << now_seconds + randomNumber << " seconds..." << endl;
            cout << "----------" << endl << endl;
            }));

        lock.unlock();

        cout << "Task should be execute on " << now_seconds + randomNumber << endl;

        cnt++;

        this_thread::sleep_for(std::chrono::seconds(randomNumber));
    }
    done = true;
}

int main() {
    thread t1(AddTask);
    thread t2(ExecuteTask);

    t1.join();
    t2.join();

    cout << "Program Ends..." << endl;
}
