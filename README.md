[![C/C++ CI](https://github.com/markCwatson/rpi-os/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/markCwatson/rpi-os/actions/workflows/c-cpp.yml)

# rpi-os

A simple hobby operating system for the Raspberry Pi 4 Model B which is based on the Broadcom BCM2711, a quad-core ARM Cortex-A72 (ARMv8) 64-bit System on Chip (SoC). This work-in-progress is meant to help me learn OS and Linux kernel/driver development.

 
## Goals
My goals are to develop a simple operating system capable of the following functions:

<ol type="1">
<li>A simple Bash-like interface.</li>
<li>A file system.</li>
<li>Symmetric Multi-Processing utilizing all 4 ARM cores.</li>
<li>Internet connectivity via the ethernet connector on the RPi.</li>
<li>Basic web server functionality.</li>
<li>A very much simplified Linux-like kernel.</li>
</ol>

 
## Building

I am using GitHub Actions to trigger builds when a change is pushed to the remote. However, I am also able to build locally. Instructions for obtaining the toolchain, installing it, and building with `make` are included below.
 
### Installing Toolchain
My dev machine is x86_64 running Ubuntu Linux. The target is the ARM Cortex-A72 chip on the Rasberry Pi 4. Thus, the cross-compiler I am using (`aarch64-none-elf`) is included in a toolchain by ARM which can be found [here][ARM Tool]. 
 

```
sudo apt update

sudo apt -y upgrade

sudo apt install curl

ARM_TOOLCHAIN_VERSION=$(curl -s https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads | grep -Po '<h4>Version \K.+(?=</h4>)')

curl -Lo aarch64-none-elf.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-aarch64-none-elf.tar.xz"

sudo mkdir /opt/gcc-arm

sudo tar xf aarch64-none-elf.tar.xz --strip-components=1 -C /opt/gcc-arm

echo 'export PATH=$PATH:/opt/gcc-arm/bin' | sudo tee -a /etc/profile.d/aarch64-none-elf.sh

```

Alternatively, I have seen others use a GNU-based cross-compiler developed and maintained by [Ubuntu Core Developers][UCD], but I have not tried it.

```
sudo apt-get update

sudo apt-get install gcc-aarch64-linux-gnu 
```
 
### Invoke Make

To build, run the following commands inside the root of the project.

```
source /etc/profile

make
```

 
## References
The following resources were used to various capacities:

1. Tutorial by [Sergey Matyukevich][Sergey]. He uses a Raspberry Pi 3 Model B (with BCM2837 SoC) but does a great job at comparing to how things are implemented in Linux.

2. Two tutorials by Rocky Pulley: one on [writing a bare-metal OS for the Raspberry Pi][Pulley1], which extends Sergey's work, and one on [OS dev using the Linux kernel][Pulley2].

3. Tutorial by [Adam Greenwood-Byrne][Adam]. Adam extends Sergey's work to the Raspberry Pi 4.

4. [OSDev.org][OSDev] has a lot of content related to OS development including a section on writing a bare-metal OS for the Rasbperry Pi.

5. [ARM's offical documentation][ARM Doc].

6. [The ARMv8 architecture ref manual][ARMv8].

7. [BCM2711 documentation][BCM2711].

8. The [Write your own Operating System][Learn OS] YouTube channel.

9. I always recommend [Miro Samek's][Miro] embeded systems programming course.

[ARM Tool]: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
[UCD]: https://packages.ubuntu.com/bionic/devel/gcc-aarch64-linux-gnu
[Sergey]: https://github.com/s-matyukevich/raspberry-pi-os
[Pulley1]: https://youtube.com/playlist?list=PLVxiWMqQvhg9FCteL7I0aohj1_YiUx1x8
[Pulley2]: https://youtube.com/playlist?list=PLVxiWMqQvhg8ZisiOBLAVkhLOYCkzTst0
[Adam]: https://github.com/isometimes/rpi4-osdev
[OSDev]: https://wiki.osdev.org/Main_Page
[ARM Doc]: https://developer.arm.com/documentation/den0024/a
[ARMv8]: https://developer.arm.com/documentation/ddi0487/ca/
[BCM2711]: https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf
[Learn OS]: https://www.youtube.com/@writeyourownoperatingsystem
[Miro]: https://www.state-machine.com/video-course