# at_c

`at_c` is the C implementation of the atProtocol

## Project structure

`archetypes`: contains useful templates for compiling applications for this library.  
`build`: cmake builds to this folder.  
`deps`: git submodules and other dependencies.
`example`: example applications.
`include`: declarations (header files).
`src`: definitions (source code).  
`lib`: staticly linked libraries.  
`targets`: additional configuration for build targets.  
`test`: contains the test source code files and where test binaries are moved to.
`tools`: contains tools and scripts, some used by tool.py

## Tools

The entire build pipeline can be run via python using `./tool.py`.

Usage:

```sh
usage: tool.py [-h] [-p {desktop,esp32}] [-f {mbedtls}] {init,build,clean,project}
```

Example:

Build for Desktop using MbedTLS:

```sh
python3 tool.py -p desktop -f mbedtls build
```

## Adding your own Test

1. Create your test in `test/`. Example: `test/my_test.c`

2. Write your test in main(). Example:

my_test.c

```c
int main()
{
    if(1 == 1) {
        return 0; // exit code 0
    } else {
        return 1; // exit code 1
    }
}
```

3. Add your test to `CMakeLists.txt`. Example:

```cmake
add_executable(test_my_test test/my_test.c)
target_link_libraries(test_my_test PRIVATE at_client)
add_test(
  NAME MY_TEST
  COMMAND $<TARGET_FILE:test_my_test>)
```

4. Build and test

```sh
python3 tool.py -p <platform> -f <framework> build
python3 tool.py -p <platform> -f <framework> test
```
