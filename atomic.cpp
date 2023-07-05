// ConsoleApplication7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#pragma execution_character_set("utf-8")
#include "atomic.h"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>

void threadProc1(Atomic<unsigned long>& value)
{
    for (int i = 0;i < 1000000;++i)
    {
        ATOMIC_INCREMENT(value);
    }
}

int main()
{
    //测试原子操作
    DWORD start = GetTickCount64();
    const int N = 10;
    Atomic<unsigned long> value;
    HANDLE thread[N];

    for (int i = 0; i < N; ++i)
    {
        thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProc1, &value, 0, nullptr);
    }

    for (int i = 0; i < N; ++i)
    {
        WaitForSingleObject(thread[i], INFINITE);
    }

    std::cout << "通过原子操作得到结果和时间如下：" << std::endl;
    std::cout << ATOMIC_GET_VALUE(value) << "---";

    for (int i = 0; i < N; ++i)
    {
        CloseHandle(thread[i]);
    }
    DWORD end = GetTickCount64();
    DWORD time = end - start;
    std::cout << "Time: " << time << std::endl;
}

#else
#include <pthread.h>
#include <vector>
#include <ctime>
void* threadProc3(void* arg)
{
    Atomic<long>* value = static_cast<Atomic<long>*>(arg);
    for (int i = 0; i < 1000000; i++)
    {
        ++(*value);
    }
    return nullptr;
}


int main()
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    Atomic<long> atomicInt(0);
    const int numThreads = 10;

    std::vector<pthread_t> threads;

    // 创建并启动多个线程对AtomicInt进行操作
    for (int i = 0; i < numThreads; i++) {
        pthread_t thread;
        pthread_create(&thread, nullptr, threadProc3, &atomicInt);
        threads.push_back(thread);
    }

    // 等待所有线程完成
    for (auto thread : threads) {
        pthread_join(thread, nullptr);
    }

    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    // 打印最终的AtomicInt值
    std::cout << "Final value: " << atomicInt.getValue() << std::endl;
    std::cout << "Time: " << elapsedTime << std::endl;

// 	struct timespec start1;
// 	clock_gettime(CLOCK_MONOTONIC, &start1);
//
// 	Linux_Mutex atomicInt1(0);
// 	const int numThreads1 = 10;
//
// 	std::vector<pthread_t> threads1;
//
// 	// 创建并启动多个线程对AtomicInt进行操作
// 	for (int i = 0; i < numThreads1; i++) {
// 		pthread_t thread1;
// 		pthread_create(&thread1, nullptr, threadProc4, &atomicInt1);
// 		threads1.push_back(thread1);
// 	}
//
// 	// 等待所有线程完成
// 	for (auto thread1 : threads1) {
// 		pthread_join(thread1, nullptr);
// 	}
//
// 	struct timespec end1;
// 	clock_gettime(CLOCK_MONOTONIC, &end1);
// 	double elapsedTime1 = (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec) / 1e9;
// 	// 打印最终的AtomicInt值
// 	std::cout << "Final value1: " << atomicInt1.getValue() << std::endl;
// 	std::cout << "Time1: " << elapsedTime1 << std::endl;

    return 0;
}

#endif
