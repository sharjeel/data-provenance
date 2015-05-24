# _Overview of SPADE's architecture_ #

The current version of **SPADE** is the second generation of our data provenance collection, analysis and management software infrastructure. The system has been completely re-architected to decouple the production, storage, and utilization of provenance metadata, as illustrated below. At its core is a novel _**provenance kernel**_ that mediates between the producers and consumers of provenance information, providing policy-based integration and storage of the records.

<p align='center'>
<img src='http://data-provenance.googlecode.com/svn/wiki/img/SPADEv2.png' />
</p>

The kernel handles buffering, filtering, and multiplexing incoming metadata from multiple _**provenance reporters**_ (such as programs that monitor an operating system's audit trail or the function calls of a MATLAB application). It can be configured to commit the elements to multiple _**provenance stores**_ (such as a graph database for fast path querying and a SQL database for fast numeric attribute querying), and responds to concurrent queries from _**provenance consumers**_ (such as Web browsers and command-line query tools). The kernel also supports _**provenance filters**_ that operate on the stream of provenance graph elements, allowing the aggregation, fusion, and composition of provenance elements to be customized for specific application domains.

The underlying data model used throughout the system is graph-based, consisting of vertices and directed edges, each of which can be labeled with an arbitrary number of annotations. It includes classes for the [Open Provenance Model (OPM)](http://eprints.ecs.soton.ac.uk/21449/)'s controlling _**Agent**_, executing _**Process**_, and data _**Artifact**_ vertex types, and edge types that relate which process _**used**_ which artifact, which artifact _**wasGeneratedBy**_ which process, which process _**wasTriggeredBy**_ which other process, which artifact _**wasDerivedFrom**_ which other artifact, and which process _**wasControlledBy**_ which agent.

```
boolean putVertex(Agent a);
boolean putVertex(Process p);
boolean putVertex(Artifact a);

boolean putEdge(Used u);
boolean putEdge(WasControlledBy wcb);
boolean putEdge(WasDerivedFrom wdf);
boolean putEdge(WasGeneratedBy wgb);
boolean putEdge(WasTriggeredBy wtb);
```

Each provenance reporter utilizes the same interface to the kernel, shown above. This holds regardless of whether the provenance elements are manually curated, application-emitted, logged by a workflow engine, or from the operating system's audit trail. The domain semantics are captured as annotations on the vertices and edges. Since a reporter maps the semantics of the domain for which it is capturing provenance, a separate one is needed for different contexts even if the level of abstraction is the same.

The **SPADE** kernel exposes a non-blocking interface to the reporters. This minimizes the possibility of reporters dropping events while waiting for the kernel to return control. Internally, the kernel maintains a buffer for each reporter from which it ingests events, utilizing the aggregation, fusion, and composition filters to reconcile the provenance elements where possible. By specifying policies in these filters, data provenance can be integrated automatically.