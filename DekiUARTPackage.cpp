/**
 * @file DekiUARTPackage.cpp
 * @brief Package entry point for deki-uart
 */
#include "DekiUARTPackage.h"
#include <deki/interop/Plugin.h>
#include <deki/LogSystem.h>

extern void DekiUARTRegisterComponents();
extern int DekiUARTGetAutoComponentCount();
extern const Deki::ComponentMeta* DekiUARTGetAutoComponentMeta(int index);

namespace DekiUart
{

#ifdef DEKI_EDITOR
#endif

static bool s_UARTRegistered = false;

}  // namespace DekiUart
// The exports below are C symbols at global scope; the package's own
// registration helpers and statics live in its namespace.
using namespace DekiUart;

extern "C"
{
    DEKI_UART_API int DekiUARTEnsureRegistered(void)
    {
#ifdef DEKI_EDITOR
        if (s_UARTRegistered)
        {
            return ::DekiUARTGetAutoComponentCount();
        }
        s_UARTRegistered = true;
        ::DekiUARTRegisterComponents();
        return ::DekiUARTGetAutoComponentCount();
#else
        return 0;
#endif
    }

    DEKI_PLUGIN_API const char* DekiPluginGetName(void)
    {
        return "Deki UART Package";
    }
    DEKI_PLUGIN_API const char* DekiPluginGetVersion(void)
    {
#ifdef DEKI_PACKAGE_VERSION
        return DEKI_PACKAGE_VERSION;
#else
        return "0.0.0-dev";
#endif
    }
    DEKI_PLUGIN_API int DekiPluginInit(void)
    {
        return 0;
    }
    DEKI_PLUGIN_API void DekiPluginShutdown(void)
    {
        s_UARTRegistered = false;
    }

#ifdef DEKI_EDITOR
    DEKI_PLUGIN_API int DekiPluginGetComponentCount(void)
    {
        return ::DekiUARTGetAutoComponentCount();
    }
    DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPluginGetComponentMeta(int index)
    {
        return ::DekiUARTGetAutoComponentMeta(index);
    }
#else
    DEKI_PLUGIN_API int DekiPluginGetComponentCount(void)
    {
        return 0;
    }
    DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPluginGetComponentMeta(int)
    {
        return nullptr;
    }
#endif

    DEKI_PLUGIN_API void DekiPluginRegisterComponents(void)
    {
#ifdef DEKI_EDITOR
        DekiUARTEnsureRegistered();
#endif
    }

}  // extern "C"
