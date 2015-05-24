# _Requirements_ #

This page lists the requirements for setting up SPADE on various operating systems. In all cases, the Oracle Java Development Kit (JDK) is required to compile SPADE. This can be downloaded from http://www.oracle.com/technetwork/java/javase/downloads/index.html

On Ubuntu 14.04, this can be installed with:

```
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
sudo apt-get install oracle-java8-installer
```


---


### Linux ###

In addition to the JDK, building SPADE requires that you have Subversion installed on your system. It is used to download the source files for compilation. You will also need [Linux Audit](http://people.redhat.com/sgrubb/audit/) and [FUSE development libraries](http://fuse.sourceforge.net/). On Ubuntu 14.04, all of these can be installed via the following command:

```
sudo apt-get install subversion libaudit-dev auditd libfuse-dev fuse
```

<a href='Hidden comment: 
For Fedora, use the following command:

```
sudo yum install subversion audit fuse-devel fuse-libs
```
'></a>


---


### Mac OS X ###

If you are using Mac OS X, you will need Subversion to retrieve the SPADE source files. [Fuse4X](http://fuse4x.github.com/) is required, unless you already have [MacFUSE](http://code.google.com/p/macfuse/) installed. Using [MacPorts](http://www.macports.org/), you can install the required packages with the following command:

```
sudo port install subversion fuse4x
```


---


### Windows ###

On Windows, SPADE can be installed using [Cygwin](http://www.cygwin.com/). Detailed instructions on setting up Cygwin can be found on its homepage. The following Cygwin packages are required:

  * `gcc` (under the `Devel` category)
  * `gcc-core` (under the `Devel` category)
  * `make` (under the `Devel` category)
  * `subversion` (under the `Devel` category)

To use the `ProcMon` reporter for Windows, you will need to download and install [Process Monitor](http://technet.microsoft.com/en-us/sysinternals/bb896645.aspx).