/**
 * @file DekiUARTPackage.cpp
 * @brief Package entry point for deki-uart
 */
#include "DekiUARTPackage.h"
#include <deki/interop/Plugin.h>
#include <deki/LogSystem.h>

#ifdef DEKI_EDITOR
extern void DekiUART_RegisterComponents();
extern int  DekiUART_GetAutoComponentCount();
extern const Deki::ComponentMeta* DekiUART_GetAutoComponentMeta(int index);
#endif

static bool s_UARTRegistered = false;

extern "C" {

DEKI_UART_API int DekiUART_EnsureRegistered(void)
{
#ifdef DEKI_EDITOR
    if (s_UARTRegistered) return DekiUART_GetAutoComponentCount();
    s_UARTRegistered = true;
    DekiUART_RegisterComponents();
    return DekiUART_GetAutoComponentCount();
#else
    return 0;
#endif
}

DEKI_PLUGIN_API const char* DekiPlugin_GetName(void)    { return "Deki UART Package"; }
DEKI_PLUGIN_API const char* DekiPlugin_GetVersion(void)
{
#ifdef DEKI_PACKAGE_VERSION
    return DEKI_PACKAGE_VERSION;
#else
    return "0.0.0-dev";
#endif
}
DEKI_PLUGIN_API int  DekiPlugin_Init(void)     { DEKI_LOG_INFO("[deki-uart] DekiPlugin_Init"); return 0; }
DEKI_PLUGIN_API void DekiPlugin_Shutdown(void) { s_UARTRegistered = false; }

#ifdef DEKI_EDITOR
DEKI_PLUGIN_API int  DekiPlugin_GetComponentCount(void) { return DekiUART_GetAutoComponentCount(); }
DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPlugin_GetComponentMeta(int index)
{
    return DekiUART_GetAutoComponentMeta(index);
}
#else
DEKI_PLUGIN_API int  DekiPlugin_GetComponentCount(void) { return 0; }
DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPlugin_GetComponentMeta(int) { return nullptr; }
#endif

DEKI_PLUGIN_API void DekiPlugin_RegisterComponents(void)
{
#ifdef DEKI_EDITOR
    int n = DekiUART_EnsureRegistered();
    DEKI_LOG_INFO("[deki-uart] DekiPlugin_RegisterComponents -> %d component(s)", n);
#endif
}


}  // extern "C"
