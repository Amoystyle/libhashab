# libhashab
## libgpod extension to make it talk to iPod nano 6th generation

libhashab enables any [libgpod](http://www.gtkpod.org/libgpod/) compatible player to update an iPod nano 6th gen. This version is slightly modified to work on Slackware 64 -current multilib. I didn't tested it on 32 bit version.

I'm not the author of this library. I just changed the install script to make it work on Slackware, as the original one is targeted to Ubuntu.

Orignal author is danwood76. [This](http://ubuntuforums.org/showthread.php?t=1611473&page=4&p=12606043#post12606043) is the link for the forum post where he releases libhashab source. There is also another [blog post](http://lizquilty.com/2013/09/28/how-to-get-an-ipod-nano-6th-gen-working-in-linux/) talking about this library that also mirrors the tarball.

## Bellow is the README from the original author.

Contained within this archive is a version of the libhashab.so
library that I have modified to compute the HashAB that is required
to correctly sign the iTunes database on the 6G iPod nano.

The soruces for the 64-bit wrappers are included for refeerence and
also a build script that will help you compile the two files correctly.

###INSTALL:

To install the modified libraries simply execute on of the install
scripts as the super user.

So in ubuntu:

  sudo install_32bit.sh for 32-bit Ubuntu
  sudo install_64bit.sh for 64-bit Ubuntu

These have only been tested on Ubuntu 12.04, on other versions or
distributions the library paths may be different.

**Warning:**

The modified library will only calculate the hash checksum for
devices with an 8 byte UUID like the nano 6g, if the library works
for your iPhone or other device that uses a 20 byte UUID then this
library will not work for you.

**My libhashab.so Modification:**

The libhashab.so library calculates the HashAB for a 20 byte UUID,
unfortunately the nano 6g has an 8 byte UUID that is used in the
calculation of the HashAB.

I spoke to the original developer of the libhashab.so library but
he was unwilling to help without me paying him money. I decided that
I would try and dissassemble and recreate the libhashab.so library
myself.

So I dissassembled the library and after a bit of analysis I found
that there was already an attempt to distinguish between the 8 and 20
byte UUIDs but obviously this didn't work on my iPod. I didn'tmanage
to fix the detection code but I have forced the library to always
calculate the 8 byte hash.

Another down side to the mod is that I couldn't find the same hook
in the 64-bit library so I had to create a wrapper around the 32-bit
library that can be called from 64-bit code.

I have included the original libhashab.so so you can view my mod,
maybe someone a little more experienced in x86 reverse engineering
can fix the real fault in the code

**File List:**

  libhashab32.so (MD5 = f782ef22a814c77cd995b9d1ad1c9f14):

Modified 32-bit libhashab.so that computes the hashab for 8 byte
UUID instead of the 20 bytes UUID it computes by default

  libhashab32_wrapper (MD5 = d77d97ace553d59b1b4b97e2cbb7a5f7):

32 bit executable that allows you to access the 32-bit libhashab.so
from the command line enabling access from the 64-bit library

  libhashab64.so (MD5 = 7b6cadfa1b1b93d22042ce73beabea1e):

New 64-bit libhashab.so that uses the 32 bit version through the 
libhashab32_wrapper program

  libhashab_original.so (MD5 = bb7180cb0c9cee2a605a5a276672913e):

Original libhashab.so file
