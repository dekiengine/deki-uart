# Deki UART

Documentation: https://dekiengine.github.io/deki-uart/ (components and properties, generated from the code)

UART serial peripheral interface for the Deki Engine. Defines `IDekiUART`: port configuration, timed reads, and writes.

Serial-attached peripherals such as the NMEA GPS backend in `deki-gps` consume this interface rather than a platform driver directly.

Part of the [Deki Engine](https://github.com/dekiengine/deki-engine) package ecosystem.

## Namespace

This package's types live in `DekiUart`. Scene files store the qualified
name, so a component is `DekiUart::SomeComponent` there, and code naming one
needs the namespace:

```cpp
using namespace DekiUart;
obj->AddComponent<SomeComponent>();
```

Scenes saved before 0.16.0 used bare names and still load: every component
records what it used to be called, and a save writes the current name.

## Installation

Install via the Package Manager inside the Deki Editor.

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for details.
