# _Using SPADE's provenance reporting API_ #

To create a reporter that sends information programmatically to the SPADE server, create a class in the `spade.reporter.*` package that extends the [spade.core.AbstractReporter](http://code.google.com/p/data-provenance/source/browse/trunk/SPADE/src/spade/core/AbstractReporter.java) class. For example, to activate a class named `myReporter`, use:

```
-> add reporter myReporter arguments
```

This will cause the server to invoke the _**spade.reporter.myReporter.launch()**_ method and pass the `arguments` string to it. Note that `myReporter` must be in the `spade.reporter.*` package and the Java class must be stored in the `SPADE/src/spade/reporter` directory. The server will load the `spade.reporter.myReporter` class dynamically when the above command is issued in the SPADE controller.

Similarly, the reporter can be deactivated while the server is running:

```
-> remove reporter myReporter
```

The above command will cause the SPADE server to invoke the _**spade.reporter.myReporter.shutdown()**_ method. It will also be called when the SPADE server is exiting.


---


### Sending a provenance vertex ###

The following steps are used to send a provenance vertex to the SPADE server:

  * Create an instance of `spade.vertex.opm.Agent`, `spade.vertex.opm.Process`, or `spade.vertex.opm.Artifact`. For example, to create a vertex describing a file use:

```
import spade.vertex.opm.Artifact;
Artifact artifact = new Artifact();
```

  * Optionally, add key-value pair annotations to the vertex using the _addAnnotation()_ method that the vertex subclass inherits from the `spade.core.AbstractVertex` class:

```
artifact.addAnnotation("file name", "/etc/passwd");
artifact.addAnnotation("modification time", "04:20:00 am");
```

  * Send the vertex to the server using the _putVertex()_ method that the reporter subclass inherits from the `spade.core.AbstractReporter` class:

```
putVertex(artifact);
```


---


### Sending a provenance edge ###

The following steps are used to send a provenance edge to the SPADE server:

  * Create an instance of `spade.edge.opm.Used`, `spade.edge.opm.WasGeneratedBy`, `spade.edge.opm.WasDerivedFrom`, `spade.edge.opm.WasTriggeredBy`, or `spade.edge.opm.WasControlledBy`. For example, to create an edge describing that a file was read by a process:

```
import spade.edge.opm.Used;
Used used = new Used(process, file);
```

In the above example, the variable `process` must be an instance of `spade.vertex.opm.Process` and the variable `file` must be an instance of `spade.vertex.opm.Artifact`.

  * Optionally, add key-value pair annotations to the edge using the _addAnnotation()_ method that the edge subclass inherits from the `spade.core.AbstractEdge` class:

```
used.addAnnotation("I/O time", "42ms");
```

  * Send the edge to the server using the _putEdge()_ method that the reporter subclass inherits from the `spade.core.AbstractReporter` class:

```
putEdge(artifact);
```