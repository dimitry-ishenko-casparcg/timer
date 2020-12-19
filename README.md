# Timer application for CasparCG.

The Timer application is intended to be used in conjunction with
[CasparCG](https://github.com/CasparCG) Server and/or Client. It uses
[OSC](http://opensoundcontrol.org/spec-1_0) protocol to display event run time
as well as current video countdown.

![screenshot](screenshot.png)

## Installation

### Prerequisites

* [osc++](https://github.com/dimitry-ishenko-casparcg/osc) >= 0.6

Follow installation instructions on their home page. `libosc++-dev` package is
only needed when compiling `timer` from source.

### Binary

Debian/Ubuntu/etc:

```console
$ ver=0.3
$ url=https://github.com/dimitry-ishenko-casparcg/timer/releases/download/v${ver}
$ wget ${url}/timer_${ver}_amd64.deb
$ sudo apt install ./timer_${ver}_amd64.deb
```

RaspberryPi:

```console
$ ver=0.3
$ url=https://github.com/dimitry-ishenko-casparcg/timer/releases/download/v${ver}
$ wget ${url}/timer_${ver}_armhf.deb
$ sudo apt install ./timer_${ver}_armhf.deb
```

### From source

Stable version (requires [Qt](https://www.qt.io/) >= 5.7 and
[CMake](https://cmake.org/) >= 3.1):

```console
$ ver=0.3
$ wget https://github.com/dimitry-ishenko-casparcg/timer/archive/v${ver}.tar.gz
$ tar xzf v${ver}.tar.gz
$ mkdir timer-${ver}/build
$ cd timer-${ver}/build
$ cmake ..
$ make
$ sudo make install
```

Latest master (requires [git](https://git-scm.com/), [Qt](https://www.qt.io/) >=
5.7 and [CMake](https://cmake.org/) >= 3.1):

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
