# _Creating Graphviz output_ #

SPADE includes support for the sever to send all the provenance metadata to a single file in [Graphviz](http://www.graphviz.org) _dot_ format.

In order to do this, add the Graphviz storage before sending the relevant provenance metadata to the server:

```
-> add storage Graphviz /tmp/provenance.dot
Adding storage Graphviz... done
```

At this point any provenance metadata that is sent to the server will be integrated and corresponding elements will be output to the `/tmp/provenance.dot` file. (Note that the file will be overwritten if it already existed.)


---


To stop further provenance metadata from being added to the file, the Graphviz storage can be removed:

```
-> remove storage Graphviz
Shutting down storage Graphviz... done
```


---


Assuming [Graphviz](http://www.graphviz.org) is installed, the `/tmp/provenance.dot` file can be rendered with:

```
dot -Tsvg -o /tmp/provenance.svg /tmp/provenance.dot
```


---


The resulting file `/tmp/provenance.svg` can be opened with a Web browser:

```
firefox /tmp/provenance.svg
```