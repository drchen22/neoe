#pragma once

#include <memory>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

namespace neoe {
    class LogSystem {
        LogSystem &operator=(LogSystem &&) = delete;
    public:
        static void Init();

        static spdlog::logger& GetLogger() {
            if (!logger_) { LogSystem::Init(); }

            return *logger_;
        }

    private:
        static std::shared_ptr<spdlog::logger> logger_;
    };

#define LOG_T(...) neoe::LogSystem::GetLogger().trace(__VA_ARGS__)
#define LOG_D(...) neoe::LogSystem::GetLogger().debug(__VA_ARGS__)
#define LOG_I(...) neoe::LogSystem::GetLogger().info(__VA_ARGS__)
#define LOG_W(...) neoe::LogSystem::GetLogger().warn(__VA_ARGS__)
#define LOG_E(...) neoe::LogSystem::GetLogger().error(__VA_ARGS__)
#define LOG_F(...) neoe::LogSystem::GetLogger().critical(__VA_ARGS__)

}
