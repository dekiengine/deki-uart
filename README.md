# Deki UART

Docs: https://dekiengine.github.io/deki-uart/ (components and properties, generated from the code)

UART serial peripheral interface for the Deki Engine. Defines `IDekiUART`: port configuration, timed reads, and writes.

Serial-attached peripherals such as the NMEA GPS backend in `deki-gps` consume this interface rather than a platform driver directly.

Part of [Deki Engine](https://github.com/dekiengine/deki-engine).

## Namespace

Types live in `DekiUart`. Scene files store the qualified name, and so does code:

```cpp
using namespace DekiUart;
obj->AddComponent<SomeComponent>();
```

Scenes saved before 0.16.0 used bare names and still load; saving writes the current one.

## Install

Package Manager in the Deki Editor, or `DekiEditor --packages-add deki-uart <project>`.

## License

Apache 2.0. See [LICENSE](LICENSE).
