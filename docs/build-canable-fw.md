# Reference to build canable firmware

Install MSYS2 from the following link:

https://www.msys2.org/




## Install git and other additional packages

```
pacman -S git
pacman -S make
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-x86_64-arm-none-eabi-toolchain
```


## Trouble shooting

### signature from "David Macek <david.macek.0@gmail.com>" is unknown trust

Suggested work arround (Did not succeed)
Uninstalling MSYS2 and reinstalling it solved the problem.

I have a work-around - that being to Disable Signature Checking (ref: ) that appears to make the environment function again.. However, I would recommend the following procedure FIRST (ref: https://www.msys2.org/news/ )

Stage 1: From https://www.msys2.org/news/

If you still see signature errors, resetting your pacman key store might help:

```
# rm -r /etc/pacman.d/gnupg/
# pacman-key --init
# pacman-key --populate msys2
```

Stage 2: https://wiki.archlinux.org/index.php/Pacman/Package_signing

Disabling signature checking

Warning: Use with caution. Disabling package signing will allow pacman to install untrusted packages automatically.
If you are not concerned about package signing, you can disable PGP signature checking completely. Edit /etc/pacman.conf and uncomment the following line under [options]:

SigLevel = Never

You need to comment out any repository-specific SigLevel settings too because they override the global settings. 
This will result in no signature checking, which was the behavior before pacman 4. 
If you decide to do this, you do not need to set up a keyring with pacman-key. You can change this option later if you decide to enable package verification.