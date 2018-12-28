# TSA

TSA is a static analysis tool for clang.

By adding annotations (attributes) to the source code that is using
the POSIX threads API, and compiling with `clang -Wthread-safety`,
the source code is analyzed in compile-time for unsafe locking
patterns that would lead into data races or deadlocks, or both.

The official documentation for TSA is

https://clang.llvm.org/docs/ThreadSafetyAnalysis.html

While that page talks only about using TSA with C++, it is quite
possible to use most of the functionality with plain C.

That is, in fact, why this repository exists.

## Usage

1. Include the tsa.h into your code where you use POSIX mutexes to coordinate POSIX threads' access to data.
2. Annotate your code with the TSA macros to explain what you think should be the "protocol" to access the data.
3. Compile with `clang -Wthread-safety`.
4. Suffer.
5. Enjoy.

You can see example usage and the errors caused by issuing `make`.
Each of the example programs demonstrates one particular type of error.

To see how to fix the problems, issue `make pass` and study the
example programs.  The first branch of the `#ifndef TSA_PASS` shows
the wrong way (which may be: "doing nothing"), while the second branch
shows the right way.

## TSA is not TSAN

TSA is NOT the same thing as "thread sanitizer" or "tsan".

The TSA is completely compile-time, whereas the thread sanitizer adds
instrumentation to the compiler output so that the runtime can detect
data races during execution.  The added instrumentation adds some
execution overhead, but quite considerable memory overhead.  None
of this happens with TSA.

## License

The tsa.h is distributed under the MIT license, which is compatible
with the clang (LLVM) license:
http://llvm.org/docs/DeveloperPolicy.html#license

The license is both inlined to tsa.h, and available as a separate file
LICENSE, directly from https://opensource.org/licenses/MIT

## Acknowledgments

I would not have delved into this without the Perl 5 project.  One of
the build modes of Perl 5 is to build with support for POSIX threads,
and to sanity check the logic of that, I found out that clang had TSA.
The Perl 5 Porters (the Perl 5 development and maintenance project)
helped out in testing the TSA C API, special thanks to Craig Berry and
Jerry Hedden.  You will find something very much like tsa.h as a part
of perl.h in the Perl 5 source code, courtesy of myself.

## Author

```
Jarkko Hietaniemi <jhi@iki.fi>
```
