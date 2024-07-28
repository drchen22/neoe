#pragma once

#include <memory>
namespace neoe {
    class WindowSystem;

    struct RHIInitInfo {
        std::shared_ptr<WindowSystem> window;
    };

    class RHI {
    public:
        virtual ~RHI() = 0;

        virtual void initialize(RHIInitInfo initialize_info) = 0;
        virtual void prepareContext() = 0;


    private:
    };

    inline RHI::~RHI() {}
}
