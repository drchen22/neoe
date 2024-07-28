#include <runtime/core/log/log_system.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
namespace neoe {
    std::shared_ptr<spdlog::logger> LogSystem::logger_ {};

    void LogSystem::Init() {
        logger_ = spdlog::stdout_color_mt<spdlog::async_factory>("neoe");
        logger_->set_level(spdlog::level::trace);
        logger_->set_pattern("%^%H:%M:%S:%e [%P-%t] [%1!L] [%20s:%-4#] - %v%$");
    }
}
