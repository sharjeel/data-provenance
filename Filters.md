# _Filtering provenance_ #

We provide a set of filters to manipulate provenance metadata before it is committed to storage. They are described below:


---


### Fusion ###

The Fusion filter can be used to merge vertices from related provenance streams. The configuration for this filter is stored in `cfg/fusion.config` and has the following format:

```
-- BEGIN FILE --
<1st reporter>
<2nd reporter>
<1st reporter>.<annotation>=<2nd reporter>.<annotation>
...
-- END FILE --
```

To merge the two streams, the names of both reporters must be specified on the first two lines of the config file.

Next, rules can be specified on which to merge annotations. These rules are specified as `<1st reporter>.<annotation>=<2nd reporter>.<annotation>`.

The Fusion filter will check to see if the incoming vertices satisfy the merging rules. If vertices are found that match the criteria, they are fused into a single vertex.


---


### IORuns ###

Reads and writes in an operating system often occurs as _runs_ of one or the other type. For example, a single function that reads in a file may result in multiple read system calls. This can result in a high volume of provenance metadata, especially when reading or writing large files. The IORuns filter can be used to fuse consecutive edges of the same type of I/O operation (i.e., either read or write) into a single edge.


---


### CycleAvoidance ###

This filter tracks the ancestors of a file and creates a new version each time a new ancestor is encountered.


---


### GraphFinesse ###

This filter tracks the entire lineage graph of a file and creates a new version if a new edge would have created a cycle.