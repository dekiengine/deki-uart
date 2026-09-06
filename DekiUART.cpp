#include "DekiUART.h"
#include <deki/LogSystem.h>

DekiUART::Factory DekiUART::s_Factory = nullptr;

void DekiUART::SetFactory(Factory factory)
{
    s_Factory = factory;
    DEKI_LOG_INTERNAL("DekiUART: Factory registered");
}

IDekiUART* DekiUART::Create()
{
    if (!s_Factory)
    {
        DEKI_LOG_ERROR("DekiUART: No factory registered - platform package must call SetFactory()");
        return nullptr;
    }
    return s_Factory();
}

bool DekiUART::HasFactory()
{
    return s_Factory != nullptr;
}
