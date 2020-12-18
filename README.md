# Timer application for [CasparCG](https://github.com/CasparCG).

![screenshot](screenshot.png)

## Installation

Binary (Debian/Ubuntu/etc):

```console
$ ver=0.2
$ url=https://github.com/dimitry-ishenko-casparcg/timer/releases/download/v${ver}
$ wget ${url}/timer_${ver}_amd64.deb
$ sudo apt install ./timer_${ver}_amd64.deb
```

Binary (RaspberryPi):

```console
$ ver=0.2
$ url=https://github.com/dimitry-ishenko-casparcg/timer/releases/download/v${ver}
$ wget ${url}/timer_${ver}_armhf.deb
$ sudo apt install ./timer_${ver}_armhf.deb
```

Compile from source (requires [Qt5](https://www.qt.io/) and [CMake](https://cmake.org/) >= 3.1):

```console
$ ver=0.2
$ wget https://github.com/dimitry-ishenko-casparcg/timer/archive/v${ver}.tar.gz
$ tar xzf v${ver}.tar.gz
$ mkdir timer-${ver}/build
$ cd timer-${ver}/build
$ cmake ..
$ make
$ sudo make install
```

Clone and compile from repository (requires [git](https://git-scm.com/), [Qt5](https://www.qt.io/) and [CMake](https://cmake.org/) >= 3.1):

```console
$ git clone https://github.com/dimitry-ishenko-casparcg/timer.git
$ mkdir timer/build
$ cd timer/build
$ cmake ..
$ make
$ sudo make install
```

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.
