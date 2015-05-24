# _Collecting system-wide provenance on Mac OS X_ #

The OpenBSM reporter is built automatically when the `make` command is issued.

Before this reporter can be used, the following commands must be executed in terminal inside the SPADE directory to allow access to the OpenBSM audit stream. These commands only need to be executed once after compiling SPADE:

```
sudo chown root lib/spadeOpenBSM
sudo chmod ug+s lib/spadeOpenBSM
```


---


The argument is unused when starting this reporter:

```
-> add reporter OpenBSM
Adding reporter OpenBSM... done
```