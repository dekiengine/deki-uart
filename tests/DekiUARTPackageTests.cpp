// deki-uart: the factory chip drivers get their UART from, and the package's plugin entry points, which
// register its components with the editor once however often it asks and let
// a reloaded package register them again.
//
// The registration functions reflection codegen generates are stood in for
// here, so the entry file is tested as it is.

#include <gtest/gtest.h>

#include "DekiUART.h"

#include <deki/PackageConfig.h>
#include <deki/interop/Plugin.h>

#include <cstring>

using namespace DekiUart;

namespace
{
int g_Registered = 0;
}

// Stand-ins for the generated registration functions the entry file calls.
void DekiUARTRegisterComponents()
{
    ++g_Registered;
}
int DekiUARTGetAutoComponentCount()
{
    return 3;
}
const Deki::ComponentMeta* DekiUARTGetAutoComponentMeta(int)
{
    return nullptr;
}

// The entry points, from the package's entry file.
extern "C"
{
    int DekiUARTEnsureRegistered(void);
    const char* DekiPluginGetName(void);
    const char* DekiPluginGetVersion(void);
    void DekiPluginShutdown(void);
    int DekiPluginGetComponentCount(void);
    void DekiPluginRegisterComponents(void);
}

namespace
{

class PackageTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        DekiPluginShutdown();
        g_Registered = 0;
    }
};

class Fake : public IDekiUART
{
public:
    const char* GetPackageId() const override { return "uart"; }
    const char* GetPackageName() const override { return "Fake"; }
    void Configure(const Deki::PackageConfig&) override {}
    bool Initialize() override { return true; }
    void Shutdown() override {}
    void Update(float) override {}
    Deki::PackageState GetState() const override { return Deki::PackageState::Running; }
    const char* GetLastError() const override { return ""; }
    int Read(uint8_t*, size_t, uint32_t) override { return 0; }
    int Write(const uint8_t*, size_t len) override { return static_cast<int>(len); }
};

IDekiUART* CreateFake()
{
    return new Fake();
}

}  // namespace

TEST_F(PackageTest, CreateNeedsTheFactoryAPlatformRegisters)
{
    DekiUART::SetFactory(nullptr);
    EXPECT_FALSE(DekiUART::HasFactory());
    EXPECT_EQ(DekiUART::Create(), nullptr);

    DekiUART::SetFactory(&CreateFake);
    EXPECT_TRUE(DekiUART::HasFactory());
    IDekiUART* a = DekiUART::Create();
    IDekiUART* b = DekiUART::Create();
    ASSERT_NE(a, nullptr);
    EXPECT_NE(a, b);  // one instance per chip driver: a UART links exactly two devices
    delete a;
    delete b;
    DekiUART::SetFactory(nullptr);
}

TEST_F(PackageTest, ComponentsAreRegisteredOnce)
{
    EXPECT_EQ(DekiUARTEnsureRegistered(), 3);
    EXPECT_EQ(DekiUARTEnsureRegistered(), 3);
    DekiPluginRegisterComponents();
    EXPECT_EQ(g_Registered, 1);
    EXPECT_EQ(DekiPluginGetComponentCount(), 3);
}

TEST_F(PackageTest, AReloadedPackageRegistersAgain)
{
    DekiUARTEnsureRegistered();
    DekiPluginShutdown();
    DekiUARTEnsureRegistered();
    EXPECT_EQ(g_Registered, 2);
}

TEST_F(PackageTest, ThePluginNamesItselfAndItsVersion)
{
    EXPECT_GT(std::strlen(DekiPluginGetName()), 0u);
    EXPECT_STREQ(DekiPluginGetVersion(), "tests");  // DEKI_PACKAGE_VERSION, as the build sets it
}
