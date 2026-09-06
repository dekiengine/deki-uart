#pragma once

#include <deki/providers/IPackage.h>
#include <cstdint>
#include <cstddef>

class IDekiUART : public Deki::IPackage
{
public:
    const char* GetPackageCategory() const override { return "uart"; }

    virtual int Read (uint8_t* dst, size_t maxLen, uint32_t timeoutMs) = 0;
    virtual int Write(const uint8_t* src, size_t len) = 0;
};
