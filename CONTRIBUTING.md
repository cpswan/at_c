<a href="https://atsign.com#gh-light-mode-only"><img width=250px src="https://atsign.com/wp-content/uploads/2022/05/atsign-logo-horizontal-color2022.svg#gh-light-mode-only" alt="The Atsign Foundation"></a><a href="https://atsign.com#gh-dark-mode-only"><img width=250px src="https://atsign.com/wp-content/uploads/2023/08/atsign-logo-horizontal-reverse2022-Color.svg#gh-dark-mode-only" alt="The Atsign Foundation"></a>

# Contributing guidelines

We 💙 [Pull Requests](https://help.github.com/articles/about-pull-requests/)
for fixing issues or adding features. Thanks for your contribution!

Please read our [code of conduct](code_of_conduct.md), which is based on
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.0-4baaaa.svg)](code_of_conduct.md)

For small changes, especially documentation, you can simply use the "Edit" button
to update the Markdown file, and start the
[pull request](https://help.github.com/articles/about-pull-requests/) process.
Use the preview tab in GitHub to make sure that it is properly
formatted before committing. Please use conventional commits and follow the semantic PR format as documented
[here](https://github.com/atsign-foundation/.github/blob/trunk/docs/atGitHub.md#semantic-prs).
A pull request will cause integration tests to run automatically, so please review
the results of the pipeline and correct any mistakes that are reported.

If you plan to contribute often or have a larger change to make, it is best to
setup an environment for contribution, which is what the rest of these guidelines
describe. The atsign-foundation GitHub organization's conventions and configurations are documented
[here](https://github.com/atsign-foundation/.github/blob/trunk/docs/atGitHub.md).

## Development Environment Setup

### Prerequisites

1. Ensure you have Git (you can check if you have it by running the following command)

   ``` sh
   git --version
   ```

1. Ensure you have a C Compiler, such as gcc (recommended) (you can check if you have it by running the following command)

   ```sh
   gcc --version
   ```

1. Ensure you have CMake (you can check if you have it by running the following command)

   ```sh
   cmake --verison
   ```

### GitHub Repository Clone

To prepare your dedicated GitHub repository:

1. Fork in GitHub <https://github.com/atsign-foundation/REPO>
2. Clone *your forked repository* (e.g., `git clone git@github.com:yourname/REPO`)
3. Set your remotes as follows:

   ```sh
   cd REPO
   git remote add upstream git@github.com:atsign-foundation/REPO.git
   git remote set-url upstream --push DISABLED
   ```

   Running `git remote -v` should give something similar to:

   ```text
   origin  git@github.com:yourname/REPO.git (fetch)
   origin  git@github.com:yourname/REPO.git (push)
   upstream        git@github.com:atsign-foundation/REPO.git (fetch)
   upstream        DISABLED (push)
   ```

   The use of `upstream --push DISABLED` is to prevent those
   with `write` access to the main repository from accidentally pushing changes
   directly.

### Development Process

1. Fetch latest changes from main repository:

   ```sh
   git fetch upstream
   ```

1. Reset your fork's `trunk` branch to exactly match upstream `trunk`:

   ```sh
   git checkout trunk
   git reset --hard upstream/trunk
   git push --force
   ```

   **IMPORTANT**: Do this only once, when you start working on new feature as
   the commands above will completely overwrite any local changes in `trunk` content.
1. Edit, edit, edit, and commit your changes to Git:

   ```sh
   # edit, edit, edit
   git add *
   git commit -m 'A useful commit message'
   git push
   ```

1. How to run tests:

   ``` sh
   # explain tests here
   ```

1. Open a new Pull Request to the main repository using your `trunk` branch

## Reporting a bug

The best place to report a bug is going to our repostiory's [issues](https://github.com/atsign-foundation/at_c) and submitting a ticket. Please provide as much information as possible, including:

- the release verison you are using (or commit hash)
- the operating system you are using (e.g. Ubuntu 20.04, macOS 12.0)
- the CPU architecture you are using (e.g. x86_64, arm64)

## Bug fix and delivery process

- Bugs will initially be placed into the Sprint Planning Board so that they
can be triaged, estimated and scheduled.
- Once work on a bug is scheduled one or more engineers will be assigned to
fixing the bug, and story points will be allocated to match the time estimated
to fix the bug.
- Progress on fixing the bug will be updated in the associated GitHub issue,
and reviewed during subsequent sprint planning meetings where necessary.
- Once a fix is created we will work with the reporter to ensure that the fix
is appropriate to their needs, and where possible this should happen prior to
release to pub.dev

## Closure of the bug

- Where possible the issue associated with the bug should be closed by mutual
consent with the reporter. This could be:
  - The reporter closing the issue because they have found a workaround.
  - The reporter closing the issue because they are satisfied with a fix
    provided.
  - A team member closes the issue after the reporter leaves a comment
    indicating that they are happy for it to be closed.
- If the reporter does not respond within 14 calendar days then we must assume
that they no longer have an interest in fixing the bug and work in progress can
be closed out at the team’s discretion.

## C Contributing Specification

- [Convention 1. Snake Case](#convention-1-snake-case)
  - [Description](#description)
  - [Examples](#examples)
  - [Exceptions](#exceptions)
- [Convention 2. Function Signature Format](#convention-2-function-signature-format)
  - [Description](#description-1)
- [Convention 3. Function Input](#convention-3-function-input)
  - [Description](#description-2)
  - [Method 1](#method-1)
  - [Method 2](#method-2)
- [Convention 4. Function Output](#convention-4-function-output)
  - [Description](#description-3)
  - [Double Pointer Method](#double-pointer-method)
  - [Buffer And Length Method](#buffer-and-length-method)
  - [Buffer and No Length](#buffer-and-no-length)
- [Convention 5. Validating Arguments](#convention-5-validating-arguments)
  - [Description](#description-4)
  - [Examples](#examples-1)
- [Convention 6. Error Handling](#convention-6-error-handling)
  - [Rule 1: The first statement in any function that is returning `int`](#rule-1-the-first-statement-in-any-function-that-is-returning-int)
  - [Rule 2: Try to avoid non-nested if statements](#rule-2-try-to-avoid-non-nested-if-statements)
  - [Rule 3: Set error code as soon as possible](#rule-3-set-error-code-as-soon-as-possible)
  - [Rule 4: Function return types should be `int`, if there is an error code](#rule-4-function-return-types-should-be-int-if-there-is-an-error-code)

### Convention 1. Snake Case

#### Description

We're using snake case instead of camel case because MbedTLS happens to be snake
case. Since MbedTLS is one of our core libraries seen everywhere, we may as well
follow their naming convention. Most C programs are also generally known to be
in snake_case.

When using snake case, we separate each **word** with an underscore.

#### Examples

Good:

```c
aes_pkam_public_key
value_encrypted_for_us_base64
atclient
atsign
```

Bad:

```c
aespkampublickey
skeencalgo
at_client
at_key
HelloWorld
helloWorld
```

#### Exceptions

Some exceptions that you may find throughout the code base:

- We consider `base64` as one word because "64" isn't really a word
- When we use the `at` prefix, we do not consider it as a word which is why we
have `atclient` instead of `at_client`. There are just too many ats that an
extra underscore would be too much.

### Convention 2. Function Signature Format

#### Description

Functions should return an `int` to hand off an error code to the caller of the
function. If an error is not possible, `void` should be used. Some exceptions
on this will be emphasized.

Example of a function:

```c
int calculate_length(const atclient_atkey *atkey, int *output_length);
```

Generally, function signatures should follow this format:

```c
<return_type> <function_name>(<context>, <input,...>, <output,...>, <optional,...>);
```

- `<return_type>` - generally an `int` to give an error code, or may be any other
return type as long as a complex error is not possible
- `<function_name>` - the name of the function (example 'foo_bar') should be in snake_case
- `<context>` - typically this is a struct pointer that is the core object meant
to be used in the function (i.e. this function LIVES and BREATHES because of the
object that the caller is passing), this should be set to `const` if it is meant
to be read-only
- `<input,..>` - any input function arguments, any values that are not editable or
should not be edited, should be set to `const`.
- `<output,..>` - any output function arguments, typically we have pointers or
double pointers to give the caller some complex values, any const inputs that are
related to the output should be put in this section (for example, buffer size is
related to the buffer, which is an output).
- `<optional,...>`- any optional inputs or outputs or any kind of optional
arguments should be at the end. An argument is considered "optional" when NULL
can be passed to it and the function will expect it to be either NULL or NON-NULL.

Here are some examples:

```c
// function signature
int atclient_put(atclient *ctx, const char *value, int *commit_id);
```

```c
// usage
atclient ctx;
atclient_init(&ctx);
int error_code;
int commit_id;
if((error_code = atclient_put(&ctx, "foo_bar", &commit_id)) != 0) {
    // handle error
}
printf("%d\n", commit_id); // outputs "37", for example
```

### Convention 3. Function Input

Related discussions have been made in : #341

#### Description

This section is regarding the `<input,...>` section of the function signature.

When receiving input in a function signature, when is it appropriate to pass the
length of the buffer and when is it not?

Take the following example

```c
// method 1 - assume it is null-terminated
int do_something1(const char *value);

// method 2 - expect value length as input
int do_something(const char *value, const size_t value_len);
```

#### Method 1

In method 1, take the input and expect it to be null-terminated

Use method 1 when:

- Working with strings (chars)
- You specify that the input should be null-terminated and it is the caller's
responsibility to pass in a null-terminated string

#### Method 2

In method 2, take both the input and length

Use method 2 when:

- Working with bytes (unsigned chars) - a null-terminator cannot be dependent to
act as the end of the data
- Working with files or standard input - when the caller is most likely passing
in this data from a file, it will be a lot easier for them to pass the length as
opposed to having to make a completely separate string and null-terminate it.

### Convention 4. Function Output

Related discussions have been made in : #335

#### Description

This section is regarding the `<output,...>` section of the function signature.

There are three ways to give back an array of data back to the caller of the function.
The first way is **double pointer method**, the second way is **buffer and length**,
and the third way is **buffer and no length** which is similar to the second.

In the first way, the **function** is responsible for allocating the memory and
the **caller** is responsible for freeing. In the second way, the **caller**
is responsible for both allocating and freeing the memory. In the third way, the
caller is responsible for allocating the correct size of the buffer as specified
by the function documentation.

The third way is very similar to the second method, but the function does not return
the length.

#### Double Pointer Method

In this first method, you pass a double pointer so that the function can allocate
**just enough** memory for you, making your life easier while also optimally using
your memory.

```c
// function signature
int atclient_atkey_to_string(const atclient_atkey *atkey, char **return_string);
```

```c
// usage
char *string = NULL;

atclient_atkey_to_string(&atkey, &string);

printf("%s\n", string); // outputs "foo.bar@bob"

free(string);
```

You should use this method when:

- Returning a string (this is most optimal for strings because a null-terminator
can be used to avoid passing a length)
- Output is calculable (if we know how long the string is going to be, we know
where to put the null-terminator !)
- The returned data is a substring of a superior buffer (example, I want to return
"foo" from "foo_bar", "foo" is trivial to extract from the string and should be
simplified for the caller).

#### Buffer And Length Method

In this second method, the caller has more control over the memory usage (e.g.
they could allocate it statically or dynamically if they would like!), but is a lot
harder to use. In the example below, the caller has to go through and allocate
the memory, reset the buffer, and make a variable to hold the length.

```c
// function signature
int atclient_atkey_to_string(const atclient_atkey *atkey, char *return_buffer,
    const size_t return_buffer_size, size_t *return_buffer_len);
```

Sometimes, `size_t *return_buffer_len` is an optional buffer and NULL can be passed
here if the caller doesn't want to receive the length. This is useful for when the
caller null-terminates the buffer themselves and can trust that the buffer will be
null-terminated and safe for string usage.

```c
// usage
const size_t string_size = 100;
char string[string_size];
memset(string, 0, sizeof(char) * string_size);
size_t string_len = 0;

atclient_atkey_to_string(&atkey, string, string_size, &string_len);

printf("[%d]: %.*s\n", (int) string_len, (int) string_len, string);
    // outputs "[11]: foo.bar@bob"
```

You should use this method when:

- Returning bytes (a null-terminator cannot be depended on to act as a stopping
point in the buffer)
- Output is not calculable (let the caller decide how much memory is enough to not
cause a segfault, this is typically found in something like RSA decryption)
- When the input is most likely coming from a file (makes it easier to pass in
strings so that the caller doesn't have to make separately null-terminated strings
and easily do something like foo_bar(string[3], 10, string[14], 5, string[20], 3);)

#### Buffer and No Length

This third method is very similar to the second way, except there is no need to
pass a `size` and `output_length` pointer. It should be specified in
**function documentation** the assumed size of the allocated buffer as well as
the expected output.

```c
// function signature

/**
 * @param shared_with - shared with atSign, null-terminated and non-null
 * @param shared_encryption_key - assumed to be at least 32 bytes allocated
 * (representing an AES256 key)
 */
int get_shared_encryption_key(const char *shared_with, unsigned char *shared_encryption_key);
```

```c
// usage
const char *shared_with = "@bob";
unsigned char shared_encryption_key[32];
if((ret = get_shared_encryption_key(shared_with, shared_encryption_key)) == 0) {
    // at this point, shared_encryption_key was successfully populated with 32
    // bytes to the brim
}
```

You should use this method when

- You wanted to use Method 2 but the size and length are always the same (in the
example above, the size always == length and is always 32, assuming that the return
exit code was 0 which means successful).
- You're not returning a string, you're returning bytes (unsigned chars)

### Convention 5. Validating Arguments

#### Description

It is important to validate arguments in functions to avoid common pitfalls
such as null pointers, negative values, etc.

#### Examples

The first thing in every function
should be similar to the following:

```c
int foo_bar(atclient *ctx, atclient_atkey *atkey) {
    int ret = 1;
    /*
     * 1. Validate arguments
     */
    if(ctx == NULL) {
        ret = 1;
        return ret;
    }

    if(atkey == NULL) {
        ret = 1;
        return ret;
    }
}
```

Another thing to note is that in the validating section of the function uses
`return` and never uses `goto`. This is because the next part of the function
is usually variable allocation where dynamic and static memory is allocated.
If we were to use `goto`, then we would have to free the memory that was allocated
before the `goto` statement. This is a common pitfall in C programming and should
be avoided.

Example of how this practice should be executed:

```c
int foo_bar(atclient *ctx, atclient_atkey *atkey) {
    int ret = 1;
    /*
     * 1. Validate arguments
     */
    if(ctx == NULL) {
        ret = 1;
        return ret; // use return
    }

    if(atkey == NULL) {
        ret = 1;
        return ret; // use return
    }

    /*
     * 2. Variables
     */
    char *buffer = NULL;
    unsigned char recv[4096];
    char *xyz = malloc(sizeof(char) * 45);

    /*
     * 3. Do stuff
     */
    if((ret = foo_bar()) != 0) {
        goto exit; // use goto
    }

    if((ret = foo_bar()) != 0) {
        goto exit; // use goto
    }

    if((ret = foo_bar()) != 0) {
        goto exit; // use goto
    }

    goto exit;
exit: {
    free(xyz);
    return ret;
}
}
```

In the above example, if it is important to note that we use `goto` only once
`xyz` is declared. That is because we `free(xyz)` in the `exit` block. We use
`return` in the validating section because we do not want to allocate memory if
the arguments are invalid. If we were to use `goto` in the validating section,
then we would have to free the memory that was allocated before the `goto` statement.

### Convention 6. Error Handling

#### Rule 1: The first statement in any function that is returning `int`

(with the intent of returning an exit code) should be declaring what the default
error code is).

For example,

```c
int foo_bar() {
    int ret = 1;

    // do stuff

    return ret;
}
```

The reason for this rule is to make it easier to make any changes to our error
handling in the future.

#### Rule 2: Try to avoid non-nested if statements

If an error occurs, then set the error code if it is not already set by the
function, log, then either exit or return.

For example,

Bad

```c
if((ret = foo_bar()) == 0 ) {
    if((ret = foo_baz()) == 0) {
        if((ret = foo_bat()) == 0) {
            // code
        } else {
            // error
            return ret;
        }
    } else {
        // error
        return ret;
    }
} else {
    // error
    return ret;
}
```

Good

```c
if((ret = foo_bar()) != 0 ) {
    // log
    return ret;
}

if((ret = foo_baz()) != 0) {
    // log
    return ret;
}

if((ret = foo_bat()) != 0) {
    // log
    return ret;
}

// code
```

The "bad" situation is not always bad and may help with the readability of your
code or the "good" scenario is simply impossible to achieve. That is why this
rule says "Try" to achieve the "good" scenario.

#### Rule 3: Set error code as soon as possible

If an error code isn't returned by a function and an error occurs explicitly set
it as the first as soon as the error occurs

For example,

Bad

```c
int exit_code;
unsigned char *x = NULL;
if((x = malloc(sizeof(unsigned char) * 45)) == NULL) {
    printf("Error occurred\n");
    exit_code = 5; // the exit_code should be the FIRST thing set AS SOON AS the
        // error occurs. This is wrong !
    return exit_code;
}
```

Good

```c
int exit_code;
unsigned char *x = NULL;
if((x = malloc(sizeof(unsigned char) * 45)) == NULL) {
    exit_code = 5; // first thing ! :))
    printf("Error occurred\n");
    return exit_code;
}
```

The reason for this rule is to limit things that could go wrong. It is important
that the error code is set as soon as the error occurs to avoid any potential
issues. For example, if printf for some reason caused an error, then the exit
code could potentially not have been set and an exit code 0 could somehow be
mistakenly `returned. The reason for this rule is also because of Rule 1, and
it helps us in the future if we ever want to change our error handling.

#### Rule 4: Function return types should be `int`, if there is an error code

If an error is not possible, then the return type should be `void`. With the exception
of types like `bool` or `size_t` where the error code is not complex.

Example

```c
bool atclient_connection_is_connected(atclient *ctx) {
    int erro_code = 0;
    if((ret = atclient_connection_send(ctx, "noop:0\r\n")) != 0) {
        return false;
    }
    return true;
}
```

In the above example, since the function returned a failure, it is safe to assume
that the connection is not connected. If the function returned a success, then it
is safe to assume that the connection is connected.

Another example:

```c
size_t calculate_length(atclient_atkey *atkey) {
    size_t length = 0;
    if(atkey == NULL) {
        return length;
    }
}
```

Since atkey was null, then it is pretty obvious that the length is 0. The length
is truly 0 beacuse nothing exists and there was nothing to calculate. This is
why the return type need not be `int` in this scenario. There is *always* an
answer to the question "what is the length of this atkey?" that fits the return
type `size_t`.
