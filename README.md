# mtl — MarineTelematics Template Library

## Overview

**mtl (MarineTelematics Template Library)** is a reusable C++ utility library.

The library provides:

- A collection of **template-based utilities**
- A small set of **component abstractions/implementations**
- Shared infrastructure used across multiple firmware and embedded software projects

Its primary goal is to promote code reuse, consistency, and reliability across projects while remaining lightweight and suitable for constrained systems.

---

## Contents

### Template Utilities

A set of generic, header-only utilities, including (but not limited to):

- Type traits and compile-time helpers
- Strongly-typed abstractions
- Utility classes and helper algorithms
- Safer or more expressive alternatives to common C++ patterns

These utilities are written with performance, clarity, and embedded constraints in mind.

---

### HAL Abstractions

The library also contains selected **component abstractions**, which may include:

- Peripheral and device interfaces
- Common driver abstractions
- Platform-independent APIs with platform-specific implementations

The intent is to decouple application logic from hardware-specific details while keeping overhead minimal.

---

## Directory Structure

```text
/mtl
├── include/            # Public headers (templates, interfaces, utilities)
├── tests/              # Unit and integration tests
├── docs/               # Internal documentation and design notes
└── README.md
```
