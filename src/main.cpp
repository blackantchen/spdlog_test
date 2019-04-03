/*
 * main.cpp
 *
 *  Created on: Mar 27, 2019
 *      Author: jerry
 */

#include <pthread.h>
#include <iostream>

#include "./include/spdlog/spdlog.h"
#include "mt_log.h"

void *TestThread_1(void *arg);
void *TestThread_2(void *arg);

int main(int argc, char *arg[]) {
	MtLog my_log;

	cout << "Welcome to spdlog" << endl;

	my_log.Initialize();

//	my_log.OutputToFile();
	my_log.OutputToConsole();

	my_log.Info("Hello, Application Logger");

	my_log.Trace("this is trace");
	my_log.Debug("this is debug");
	my_log.Info("this is info");
	my_log.Warn("this is warn");
	my_log.Error("this is error");
	my_log.Critical("this is critical");

	pthread_t thread_1, thread_2;

	pthread_create(&thread_1, NULL, TestThread_1, (void*) &my_log);
	pthread_create(&thread_2, NULL, TestThread_2, (void*) &my_log);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	return 0;
}

void *TestThread_1(void *arg) {
//	std::shared_ptr<spdlog::logger> log = arg;
	MtLog* log = (MtLog*) arg;

	usleep(1000 * 100);

	for (int i = 0; i < 20; i++) {
//		log->AppLogger()->info("Test Thread 1: {}", i);
		log->Warn("Test Thread 1: {}", i);
		usleep(1000 * 100);
	}

	exit(0);
}

void *TestThread_2(void *arg) {
//	std::shared_ptr<spdlog::logger> log = arg;
	MtLog* log = (MtLog*) arg;

	usleep(1000 * 250);

	for (int i = 0; i < 20; i++) {
//		log->AppLogger()->info("Test Thread 2: {}", i);
		log->Critical("Test Thread 2: {}", i);
		usleep(1000 * 100);
	}

	exit(1);
}
