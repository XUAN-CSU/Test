#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex mtx;

void worker(int id) 
{
    std::unique_lock<std::mutex> lock(mtx);

    std::cout << "Thread " << id << " has the lock." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    lock.unlock();

    std::cout << "Thread " << id << " has release the lock. " << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    lock.lock();

    std::cout << "Thread " << id << " has re-acquired the lock. " << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    t1.join();
    t2.join();

    return 0;
}


