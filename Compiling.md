# _Downloading and compiling_ #

After fulfilling the necessary requirements for your system, the following steps are performed to download and compile SPADE.


---


### Linux and Mac OS X ###

First, use the following command to download SPADE. Ensure that you use the revision number specified in the command as the latest version of the source code may not be stable:

```
svn -r 1006 export http://data-provenance.googlecode.com/svn/trunk/SPADE/
```

This will create a `SPADE` directory and download all the necessary files in it.

To compile the SPADE code, navigate to this newly created directory and `configure` the package before executing the `make` command as follows:

```
cd SPADE
./configure
make
```


---


### Windows ###

Enter the Cygwin terminal and use the following command to download the SPADE source files:

```
svn -r 1006 export http://data-provenance.googlecode.com/svn/trunk/SPADE/
```

This will create a `SPADE` directory and download all the necessary files in it. For the source files to compile, Cygwin must find the `javac` Java compiler in the `PATH` variable. To add `javac` to `PATH`, execute the following inside the Cygwin terminal replacing `c/Program\ Files/Java/jdk1.7.0_09` with the path to your JDK installation:

```
export PATH=$PATH:/cygdrive/c/Program\ Files/Java/jdk1.7.0_09/bin
```

Please also ensure that any spaces in the path are escaped with a backslash as in the example above. Finally, execute the following commands to navigate to the newly-created SPADE directory and compile the package:

```
cd SPADE
./configure
make
```