#include <iostream>

#include <Core/Logger.hpp>

int main()
{
#ifdef NDEBUG
    gir::Logger::SetLogLevel(gir::ELogLevel::Info);
    gir::Logger::Info("Build mode: Release");
#else
    gir::Logger::SetLogLevel(gir::ELogLevel::Debug);
    gir::Logger::Info("Build mode: Debug");
#endif

    gir::Logger::Info("GIR-Engine: Initialized");

    gir::Logger::Info("GIR-Engine: Shutdown");

    return 0;
}
