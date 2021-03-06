#include <iostream>

#include <Core/Core.hpp>

#include <Application/Application.hpp>

int main()
{
#ifdef NDEBUG
    gir::Logger::SetLogLevel(gir::ELogLevel::Info);
    gir::Logger::Info("Build mode: Release");
#else
    gir::Logger::SetLogLevel(gir::ELogLevel::Debug);
    gir::Logger::Info("Build mode: Debug");
#endif

    auto application = new gir::Application();

    gir::Logger::Info("GIR-Engine: Initialized");

    application->Setup();
    application->Run();
    delete application;

    gir::Logger::Info("GIR-Engine: Shutdown");

    return 0;
}
