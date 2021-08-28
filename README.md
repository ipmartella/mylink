# MyLink - A simple plain-text link collector
MyLink is a CLI application that helps you collect and manage links (URLs) in a simple plain-text file.
You can think of MyLink as a simplified version of the bookmark manager embedded in your web browser, or as a local alternative to services like Pocket.

MyLink is built for people who want full control over their data. 
Your link collection is stored as a single plain-text file using the Markdown syntax, so you can read and edit it using any plain-text software you are familiar with (grep, awk, sed, emacs, vim, Notepad++, etc.) on any operating system.

# Features
* Add links to your collection as URLs (with optional title) using the `mylink add` command
* Access your link collection directly from your favorite web browser using the `mylink server` command
* Add a webpage to your collection straight from your web browser using the integrated bookmarklet

# Design goals
MyLink is designed to give you full control over your collection of links/bookmarks/read-it-later articles. Most apps and services for bookmark/article management offer convenient access to your collection at the cost of privacy, targeted advertising.

On the contrary, MyLink:
* Runs entirely on your PC.
* Does NOT show you any ads.
* Does NOT collect any personal information.
* Does NOT require an account/subscription.
* Does NOT send any *telemetry*. Does NOT *phone home*.
* It's free and open source.

# Usage
By default, MyLink stores your link collection in a file called `links.md` in the current working folder.
If you want to use a different file, use the `-p <path>` command line option.

## Add a URL from the command line

  ```
  mylink add https://myurl.url
  ```

## Add a URL from the command line, with a specific title

  ```
  mylink add https://myurl.url -t "My Title"
  ```

## Use your MyLink collection with your web browser

  ```
  mylink server
  ```
  
Then browse to `http://localhost:1234/mylink.html`, and you will see a list of your bookmarks/links.
The webpage contains also a [bookmarklet](https://en.wikipedia.org/wiki/Bookmarklet) to add a webpage to your MyLink collection.

# Install
## Prerequisites
For the time being, MyLink only works on Linux (Windows support is on the way).

## Steps
1. Download the latest prebuilt version from the [release page](https://github.com/ipmartella/mylink/releases)
2. Extract the archive to a folder of your choice
3. Run `mylink -h` to check available commands


# Build
## Prerequisites
Before you begin, ensure you have met the following requirements:
* [CMake](https://cmake.org/) v3.5 or above
* A C++14 compiler toolchain (tested with gcc v10.3.0)

## Steps
1. Clone the repo

  ```
  git clone https://github.com/ipmartella/mylink mylink
  cd mylink
  ```

2. Generate build files with CMake

  ```
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release ..
  ```

3. Build the project

  ```
  cmake --build . --parallel --target mylink
  ```

At the end of a successful build, you can find the `mylink` executable and the web resources (the `www` folder) in the `cli` subfolder.

        
# Limitations
The latest of MyLink has the following limitations:
* The application is available only on Linux
* You cannot change the binding address and the port for the MyLink server
* You cannot edit/remove links from the CLI or web interface

Most (if not all) of these limitations are going to be removed in future versions.
If you want to propose a new feature, or if you want to contact the author, open a Pull Request or a Github Issue :)

# Used third-party libraries
MyLink is build on top of a number of open source libraries:
- [argh](https://github.com/yhirose/cpp-httplib)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [doctest](https://github.com/onqtam/doctest)
- [json](https://github.com/nlohmann/json)

MyLink would not exist without these awesome projects, so my deepest gratitude goes to the respective developers.

# License
This project is licensed [GNU General Public License v3.0 or later](https://spdx.org/licenses/GPL-3.0-or-later.html).
