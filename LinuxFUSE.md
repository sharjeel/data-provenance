# _Limiting filesystem provenance collection on Linux_ #

It may be preferable to only collect provenance about a limited part of the filesystem (that a target application is using, for example). Additionally, collecting fine-grained provenance, including I/O time, can impose significant overhead when done across the entire operating system. This reporter allows provenance collection to be limited to a subtree (/tmp/mountPoint in the example below) of the filesystem.

### Requirements: ###
  * FUSE (http://fuse.sourceforge.net/)
  * On Fedora, FUSE can be installed by issuing the following command:
```
yum install fuse fuse-devel fuse-libs
```


---


The LinuxFUSE reporter is built automatically with 'make' in the root SPADE directory. Before this reporter can be used, the option **user\_allow\_other** _must_ be enabled in the file `/etc/fuse.conf`.


---


To use this reporter, the argument must specify the path where the FUSE filesystem will be mounted:

```
-> add reporter LinuxFUSE /tmp/mountPoint
Adding reporter LinuxFUSE... done
```

Provided that no file or directory already exists at `/tmp/mountPoint`, the above line will mount the FUSE filesystem at `/tmp/mountPoint`. Any filesystem events that occur in this subtree will be monitored by SPADE and their provenance recorded.