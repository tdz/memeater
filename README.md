memeater
========

Consumes a fixed amount of memory

# License

Memeater is distributed under the Mozilla Public License 2.0.

# Compile and install

Copy this directory into the application directory of your Android
NDK and run ndk-build, or copy the directory into B2G's external/
directory and have memeater buil dand installed automatically with
B2G.

# Usage

When executed, memeater allocates memory and waits until it receives
input from STDIN. An example call for consuming 4 Mebibyte is shown
below.

    ./memeater -m 4M

Memeater supports the following command-line options.

    -f <filename>   The filename to wait on, instead of STDIN.

    -m <size>       Sets the amount of memory to consume. The modifiers
                    'g', 'm', 'k' to specify Gibi-, Mebi-, and Kibibyte
                    are supported. The modifier 'p' specifies the number
                    of pages to allocate. Minor divergences from the
                    specified size are possible.
