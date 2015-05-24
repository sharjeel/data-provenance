# SPADE with LogicBlox as storage #
This page will guide you on how to setup LogicBlox as a storage for SPADE.

## Requirements ##
  * A 64-bit flavor of Linux.
  * Python 2.7 or newer (but not Python 3.x).
  * [Oracle JDK](http://www.oracle.com/technetwork/java/javase/downloads/index.html)


## Setting up LogicBlox ##

[Follow instructions on the LogicBlox website.](https://developer.logicblox.com/content/docs4/core-reference/webhelp/installation.html)

## Setting up SPADE to use LogicBlox as storage ##

Check out SPADE from the source code repository by executing the following command in the terminal window:
```
svn checkout http://data-provenance.googlecode.com/svn/trunk/SPADE/
```
This command will create a new `SPADE` directory and download the required files into it. To compile the SPADE code, navigate to this newly created directory and configure the package before executing the `make` command as follows:
```
cd SPADE
./configure
```
In the makefile change the JAVA\_CP to include the LogixBlox libraries. Assuming you installed LogicBlox in /opt/logicblox this change would look like this.
```
JAVAC_CP = build:lib/*:/opt/logicblox/logicblox-4.1.7/lib/java/*
```
Now run make.
```
make
```
After SPADE is compiled change the spade start script in /bin directory as so that it uses the LogicBlox libraries in the classpath.
```
java -cp "./build:./lib/*:/opt/logicblox/logicblox-4.1.7/lib/java/*" -server -Xms128M -Xmx512M spade.core.Kernel
```