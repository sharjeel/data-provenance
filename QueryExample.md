# _Example illustrating provenance querying_ #

The example below illustrates the use of the query client.


---


After the SPADE server has been started, add the `Neo4j` storage and `DSL` reporter using the control client:

```
-> add storage Neo4j /tmp/spade_database
Adding storage Neo4j... done

-> add reporter DSL /tmp/spade_pipe
Adding reporter DSL... done
```


---


To create the provenance metadata needed for the example, use the following commands in terminal or shell to add the vertices and edges:

```
echo type:Process id:1 name:root\\ process pid:10 >> /tmp/spade_pipe 
echo type:Process id:2 name:child\\ process pid:32 >> /tmp/spade_pipe 
echo type:WasTriggeredBy from:2 to:1 time:5\\:56\\ PM >> /tmp/spade_pipe 
echo type:Artifact id:3 filename:output.tmp >> /tmp/spade_pipe 
echo type:Artifact id:4 filename:output.o >> /tmp/spade_pipe 
echo type:Used from:2 to:3 iotime:12\\ ms >> /tmp/spade_pipe 
echo type:WasGeneratedBy from:4 to:2 iotime:11\\ ms >> /tmp/spade_pipe 
echo type:WasDerivedFrom from:4 to:3 >> /tmp/spade_pipe 
echo type:Agent id:user uid:10 gid:10 name:john >> /tmp/spade_pipe 
echo type:WasControlledBy from:1 to:user >> /tmp/spade_pipe 
echo type:WasControlledBy from:2 to:user >> /tmp/spade_pipe 
```

(Note that the **Agent** vertex has a non-numeric `id`. This illustrates that a vertex's `id` key can have any value as long as it is unique.)


---


If the `Graphviz` storage had been added, the resulting graph would be:

<p align='center'>
<img src='http://data-provenance.googlecode.com/svn/wiki/img/QueryData.gif' />
</p>

Note that the [Open Provenance Model (OPM)](http://eprints.ecs.soton.ac.uk/21449/) convention of using octagons for **Agent** vertices, rectangles for **Process** vertices, and ellipses for **Artifact** vertices is followed. In addition, the graph elements are colored with the following semantics:

<p align='center'>
<table><thead><th> <b>Color</b> </th><th> <b>OPM</b> meaning </th></thead><tbody>
<tr><td> pink         </td><td> Agent              </td></tr>
<tr><td> light blue   </td><td> Process            </td></tr>
<tr><td> yellow       </td><td> Artifact           </td></tr>
<tr><td> purple       </td><td> WasControlledBy    </td></tr>
<tr><td> green        </td><td> Used               </td></tr>
<tr><td> red          </td><td> WasGeneratedBy     </td></tr>
<tr><td> dark blue    </td><td> WasTriggeredBy     </td></tr>
<tr><td> orange       </td><td> WasDerivedFrom     </td></tr>
</p></tbody></table>


---


The graph of the provenance of the `root process` (which has a `vertexId` of `1`) can be retrieved with:

```
-> graph1 = getLineage(1, 10, ancestors)
Time taken for query: 389 ms
-> export graph1 /tmp/ancestors.dot
Exported graph1 to /tmp/ancestors.dot
```

The file `/tmp/ancestors.dot` is in [Graphviz](http://www.graphviz.org) format. When rendered it looks like this:

<p align='center'>
<img src='http://data-provenance.googlecode.com/svn/wiki/img/QueryExampleAncestors.gif' />
</p>


---


Similarly, the graph in which the same vertex is part of the provenance can be retrieved with:

```
-> graph2 = getLineage(1, 10, descendants)
Time taken for query: 560 ms
-> export graph2 /tmp/descendants.dot
Exported graph2 to /tmp/descendants.dot
```

When rendered, it looks like this:

<p align='center'>
<img src='http://data-provenance.googlecode.com/svn/wiki/img/QueryExampleDescendants.gif' />
</p>