# How to build doxygen html

1. download from https://doxygen.nl/index.html
2. open `Doxywizard`
3. `File` -> `Open`
4. Open the file ./Doxyfile 
5.  To tab `Run` , Click `Run doxygen`

# How to build & run doxygen html on Ubuntu

The following steps are verified on Ubuntu 22.04：

```shell
$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 22.04.5 LTS
Release:	22.04
Codename:	jammy
```

The following packages (and dependents) need to be installed:

```shell
$ sudo apt update
$ sudo apt install doxygen
$ sudo apt install graphviz
```

Assume that the path of RT-Thead code tree is $RTT, execute the following command to build html.

```shell
$ cd $RTT/documentation/doxygen
$ rm -rf html
$ doxygen
```

A new html directory will be created and all the html files will be placed in this directory.

If you want to quickly browse HTML locally (in Ubuntu environment), you can enter the html directory and start a local HTML server through Python.

```shell
$ cd html
$ python3 -m http.server
Serving HTTP on 0.0.0.0 port 8000 (http://0.0.0.0:8000/) ...
```

Open the browser and enter `http://<IP>:8000/index.html` to access the created html web pages. If it is a local access, then `<IP>` should be replaced by `localhost`. If it is a remote access, then `<IP>` should be replaced by the actual accessible IP address of the machine where HTML is located.
