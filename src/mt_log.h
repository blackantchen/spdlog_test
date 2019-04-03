/*
 * mt_log.h
 *
 *  Created on: Apr 2, 2019
 *      Author: jerry
 */

#ifndef SRC_MT_LOG_H_
#define SRC_MT_LOG_H_

#include "./include/spdlog/spdlog.h"
#include "./include/spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;

class MtLog {
public:
	MtLog() {
	}
	~MtLog() {
	}

	void Initialize(void) {
		this->LoggerRegistry();
	}

	void SetLogLevel(spdlog::level::level_enum log_level) {
		app_logger_->set_level(log_level);
	}
	spdlog::level::level_enum GetLogLevel() {
		return app_logger_->level();
	}
	
	void OutputToFile() {
		app_logger_ = async_file_logger_;
	}
	void OutputToConsole() {
		app_logger_ = console_logger_;
	}

	std::shared_ptr<spdlog::logger> AppLogger() {
		return app_logger_;
	}

	template<typename ... Args>
	void Trace(const char *fmt, const Args &... args) {
		app_logger_->trace(fmt, args...);
	}

	template<typename ... Args>
	void Debug(const char *fmt, const Args &... args) {
		app_logger_->debug(fmt, args...);
	}

	template<typename ... Args>
	void Info(const char *fmt, const Args &... args) {
		app_logger_->info(fmt, args...);
	}

	template<typename ... Args>
	void Warn(const char *fmt, const Args &... args) {
		app_logger_->warn(fmt, args...);
	}

	template<typename ... Args>
	void Error(const char *fmt, const Args &... args) {
		app_logger_->error(fmt, args...);
	}

	template<typename ... Args>
	void Critical(const char *fmt, const Args &... args) {
		app_logger_->critical(fmt, args...);
	}

private:
	std::shared_ptr<spdlog::logger> app_logger_;
	std::shared_ptr<spdlog::logger> console_logger_;
	std::shared_ptr<spdlog::logger> async_file_logger_;

	const size_t kMaxFileSizeBytes = 1024 * 1024 * 8; // max file size is 8M bytes
	const size_t kMaxNumFiles = 3;
//	const size_t kQueueSize = std::pow(2, 16);
	
	const std::string kAppFileName = "./application.log";

	void LoggerRegistry() {
		// Create a stdout logger
		console_logger_ = spdlog::stdout_color_mt("console");

		// Create a file rotating logger with kMaxFileSizeBytes and kMaxNumFiles rotated files.
		async_file_logger_ = spdlog::rotating_logger_mt("app log", kAppFileName, kMaxFileSizeBytes, kMaxNumFiles);

		app_logger_ = console_logger_; // set default logger of application

		app_logger_->set_level(spdlog::level::info); // set default log level
//		appLogger_->set_pattern(APP_PATTERN_STRING);
	}
};

#endif /* SRC_MT_LOG_H_ */
