## Packaging Instructions ##

Below are instructions for creating SPADE packages for deployment on Mac or Linux:

### Mac OS X ###

For packaging on Mac OS X, it is assumed that you have MacPorts installed on your system. MacPorts can be found at http://www.macports.org/. The MacPorts guide's section on [Local Portfile Repositories](http://guide.macports.org/#development.local-repositories) describes the steps to set up a local portfile. For this purpose, you can download [SPADE's portfile](https://code.google.com/p/data-provenance/source/browse/trunk/misc/Portfile). Once the local port is added to the PortIndex as per the instructions in the guide, it becomes available for installing and packaging:

```
sudo port install spade
port pkg spade
```

The above steps will create a SPADE `pkg` file for deployment on Mac OS X systems.


### Linux ###

For creating a Debian package for deployment on Linux, it is assumed that you have `dh_make` and `dpkg` installed. After navigating to an empty directory, the steps to create a package are as follows:

```
svn export -r 987 http://data-provenance.googlecode.com/svn/trunk/SPADE/
mv SPADE/ spade-2.0
cd spade-2.0/
dh_make --createorig
cd debian/
rm *.ex *.EX
cd ..
dpkg-buildpackage 
```