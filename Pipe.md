# _Collecting provenance from an external application_ #

To let a user (or external application) start sending provenance information to SPADE with minimal effort, we have implemented a `DSL` reporter. It creates a named pipe in the filesystem, to which a user (or external application) can send provenance information in a simple language that we describe below.


---


The `DSL` reporter is compiled along with SPADE. This reporter takes a single argument, which is the location in the filesystem where the pipe is to be created. Note that this must be done in the SPADE controller (after the SPADE server has been started):

```
-> add reporter DSL /tmp/spade_pipe
Adding reporter DSL... done
```

As long as no other object existed at that location (such as a file, directory, socket, or pipe), the `DSL` reporter will create a named pipe at that location (which is `/tmp/spade_pipe` in the above example).


---


To send provenance metadata to the SPADE server through the `DSL` reporter, each vertex or edge must be described on a new line.

### Sending a provenance vertex ###

To send a vertex, write a line of the below form to the pipe:

| **`type:<Agent|Process|Artifact>  id:<unique identifier>  <key>:<value>  ... <key>:<value>`** |
|:----------------------------------------------------------------------------------------------|

Depending on whether the value associated with the key `type` is `Agent`, `Process`, or `Artifact`, a corresponding Open Provenance Model vertex will be created. The `unique identifier` is used to disambiguate a vertex so that it can be referred to as the endpoint of an edge. Each `<key>:<value` pair (of which there can be an arbitrary number) is turned into an annotation on the vertex.

(Note that the `type:<Agent|Process|Artifact>` and `id:<unique identifier>` elements are only used to tell the `DSL` reporter what vertices / edges to create, and are not committed to storage.)


---


For example, the line below can be entered on the command line of a Unix shell to report that a program named `firefox` ran with a `PID` of 1234:

```
echo type:Process id:1 program:firefox pid:1234 >> /tmp/spade_pipe
```

Similarly, a provenance vertex can be created to describe that a data artifact has filename `index.html` and is owned by `user`:

```
echo type:Process id:2 filename:index.html owner:user >> /tmp/spade_pipe
```


---


### Sending a provenance edge ###

To send an edge, write a line of the below form to the pipe:

| **`type:<Used|WasGeneratedBy|WasTriggeredBy|WasDerivedFrom|WasControlledBy>  from:<unique identifier>  to:<unique identifier>  <key>:<value>  ... <key>:<value>`** |
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------|

The `unique identifier` value associated with the `from` key determines which vertex is the source of the edge, while the `unique identifier` value associated with the `to` key determines which vertex is the destination of the edge.

If the key `type` is `Used`, the key `from` must be associated with a value that is the unique identifier of a `Process` vertex, and the key `to` must be associated with a value that is the unique identifier of an `Artifact` vertex.
If the key `type` is `WasGeneratedBy`, the key `from` must be associated with a value that is the unique identifier of an `Artifact` vertex, and the key `to` must be associated with a value that is the unique identifier of an `Process` vertex.
If the key `type` is `WasTriggeredBy`, the key `from` must be associated with a value that is the unique identifier of a `Process` vertex, and the key `to` must be associated with a value that is the unique identifier of an `Process` vertex.
If the key `type` is `WasDerivedFrom`, the key `from` must be associated with a value that is the unique identifier of an `Artifact` vertex, and the key `to` must be associated with a value that is the unique identifier of an `Artifact` vertex.
If the key `type` is `WasControlledBy`, the key `from` must be associated with a value that is the unique identifier of a `Process` vertex, and the key `to` must be associated with a value that is the unique identifier of an `Agent` vertex.

All the remaining `<key>:<value>` pairs are turned into annotations on the edge.


---


Continuing the example above, the fact that the `firefox` process read the `index.html` file at 4:20 am can be reported with a `Used` edge:

```
echo type:Used from:1 to:2 time:0420 >> /tmp/spade_pipe
```

Note that the keys `type`, `id`, `from`, and `to` are reserved and cannot be used as annotation keys. Spaces (' ') and colons (:) can be used in the remaining keys and in all values by escaping them using a backslash (\). For example, instead of the value _0420_, a value _4:20 am_ can be sent by writing it as `4\:20\ am`.

To record provenance from within an application, simply print or write the information to the named pipe.


---


Reporters can be added and removed while the SPADE server is running. For example, the provenance metadata being written to the named pipe created by the `DSL` reporter will no longer be sent to the SPADE server after this:

```
-> remove reporter DSL
Shutting down reporter DSL... done
```