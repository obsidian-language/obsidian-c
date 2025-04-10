# Obsidian Language: **An Experimental Language**

<p align="right">
  <a href="#why-build-obsidian">Why?</a> |
  <a href="#language-goals">Goals</a> |
  <a href="#project-status">Status</a> |
  <a href="#getting-started">Getting Started</a> |
  <a href="#join-us">Join Us</a> |
  <a href="#build-status">Build Status</a>
</p>

<a href="docs/snippets.md#fib">
<img src="docs/images/obsidian_snippet.png" align="right" width="375" alt="fib code in Obsidian. Follow the link to read more.">
</a>

### **Why Obsidian?**

- **Fast**:  
  - Performance comparable to C/C++ using LLVM, with direct access to low-level constructs.
  - Efficient and scalable builds.

- **Modern & Evolving**:  
  - Intuitive for developers familiar with C, with easy-to-learn language foundations.
  - Smooth upgrade path between versions.
  - Emphasis on safety and a roadmap towards memory safety.

- **Welcoming Open-source Community**:  
  - Transparent goals and decision-making.
  - An inclusive, friendly, and open community.
  - Comprehensive toolset: compiler, libraries, documentation, package manager, and more.

## Why Build Obsidian?

C++ has significant technical debt due to its long history. Obsidian aims to solve this by offering a new language with clean syntax, modular architecture, and modern features, ensuring a smooth transition from C++ without losing performance.

Obsidian is not meant to replace languages like Go, Swift, or Rust but is designed for cases where moving away from C/C++ is impractical.

## Language Goals

- High performance for critical applications.
- Code that's easy to read, write, and maintain.
- Safe coding patterns with built-in testing mechanisms.
- Support for modern OS platforms, architectures, and environments.
- Fast iteration and development cycles.

While these goals overlap with other languages, Obsidian's unique value lies in their combination.

### Non-goals:

- Stable [application binary interface (ABI)](https://en.wikipedia.org/wiki/Application_binary_interface).
- Absolute backward or forward compatibility.

For more details, see our [goals document](/docs/project/goals.md).

## Project Status

Obsidian is currently in its experimental phase, with ongoing active development on the toolchain, which includes a compiler and linker. Our primary goal is to create a viable language that can be evaluated as a potential successor to C++. Key advancements include:

- A robust strategy and structure for the Obsidian project.
- An open-source governance model and evolution process.
- An early-stage compiler for converting Obsidian code into executables.

Check out our [full roadmap](/docs/project/roadmap.md) for more details.

## Obsidian vs. C++

<p align="center">
  <a href="docs/snippets.md#c" style="display: inline-block;">
    <img src="docs/images/cpp_snippet.png" width="375" alt="A snippet of C++ code. Follow the link to read it." style="vertical-align: top;">
  </a>
  <a href="docs/snippets.md#obsidian" style="display: inline-block;">
    <img src="docs/images/obsidian_snippet.png" width="375" alt="A snippet of Obsidian code. Follow the link to read it." style="vertical-align: top;">
  </a>
</p>

## Memory Safety

Memory safety is a priority, focusing on:

- Improved tracking and enforcement of initialization.
- Dynamic bounds checks for secure debug builds.
- Robust API designs to support safer programming patterns.

## Getting Started

Obsidian is in early development, with nightly releases of the toolchain available.

```shell
# Get the release
$ wget https://github.com/obsidian-language/obsidian/releases/download/v${VERSION}/obsidian-${OS}-${ARCH}.tar.gz

# Unpack the toolchain:
$ tar -xvf obsidian-${OS}-${ARCH}.tar.gz

# Create a simple Obsidian source file:
$ echo "fn main() i32 { println(42); return 0; }" > forty_two.ob

# Compile to an executable file:
$ ./obsidian forty_two.ob -o forty_two

# Run it:
$ ./forty_two
```

Note: This is a very early-stage release, and many features are still in development. Check out our [0.1 milestone](/docs/project/milestones.md) for upcoming improvements.

### Building & Installing

For full information on building Obsidian, see [Obsidian Building Guide](#). Here follows a summary - if you get into trouble, the Building Guide has all the answers.

Before building Obsidian you may need to install some other tools and libraries. See, [Setting up your system for building Obsidian](#).

**Quick start**: Obsidian is built using the [Make build system](#). The following gives you a default build:
```
$ ./boot
$ ./configure
$ make
```

The `./boot` step is only necessary if this is a tree checked out from git.

## Build Status

| Master CI    | Build Status                                             |
|--------------|----------------------------------------------------------|
| Windows      | ![Windows builds](https://github.com/obsidian-language/obsidian-c/actions/workflows/build.yml/badge.svg?branch=master&event=push)                |
| macOS        | ![macOS builds](https://github.com/obsidian-language/obsidian-c/actions/workflows/build.yml/badge.svg?branch=master&event=push)                     |
| Linux Etc    | ![Linux (etc) builds](https://github.com/obsidian-language/obsidian-c/actions/workflows/build.yml/badge.svg?branch=master&event=push)              |

## Join Us

We'd love to have folks join us and contribute to the project. Obsidian is committed to a welcoming and inclusive environment where everyone can contribute.

- Most of Obsidian's design discussions occur on [Discord](https://discord.gg/#).
- To watch for major release announcements, subscribe to our [Obsidian release post on GitHub](#) and [star Obsidian-lang](https://github.com/obsidian-language/obsidian).
- See our [code of conduct](CODE_OF_CONDUCT.md) and [contributing guidelines](CONTRIBUTING.md) for information about the Obsidian development community.

### Contributing

You can also directly:

- [Contribute to the language design](CONTRIBUTING.md#contributing-to-the-language-design): feedback on design, new design proposals.
- [Contribute to the language implementation](CONTRIBUTING.md#contributing-to-the-language-implementation): [Obsidian Toolchain](#), and project infrastructure.

You can **check out some ["good first issues"](https://github.com/obsidian-language/obsidian/labels/good%20first%20issue)**, or join the `#contributing-help` channel on [Discord](https://discord.gg/#). See our full [`CONTRIBUTING`](CONTRIBUTING.md) documentation for more details.
