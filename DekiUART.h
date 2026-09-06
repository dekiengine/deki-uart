#pragma once

#include "IDekiUART.h"
#include "DekiUARTPackage.h"

/**
 * @brief Factory for UART instances. Each chip driver owns its own UART
 * (UARTs are point-to-point, so there's no shared-bus registry).
 *
 * Platform integration packages call SetFactory at boot; chip drivers call
 * Create() when they need an instance.
 */
class DEKI_UART_API DekiUART
{
public:
    using Factory = IDekiUART* (*)();

    static void       SetFactory(Factory factory);
    static IDekiUART* Create();
    static bool       HasFactory();

private:
    static Factory s_Factory;
};
