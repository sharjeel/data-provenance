# _Querying SPADE_ #

SPADE supports three classes of queries. These are invoked using the SPADE query client which is started with the following command:

```
dig.sh
```

The following will appear:

```
SPADE 2.0 Query Client

Available commands:
       <result> = getVertices(expression)
       <result> = getEdges(expression)
       <result> = getPaths(src_id, dst_id, max_length)
       <result> = getLineage(id, depth, direction)
       <result> = getLineage(id, depth, direction, expression)
       <result> = <result>.getChildren(expression)
       <result> = <result>.getParents(expression)
       <result>.showVertices(expression)
       <result> = import(path)
       <result>.export(path)
       list
       exit

->
```

---


### Finding provenance vertices ###

The `getVertices()` class of queries finds all the provenance vertices that have specific properties. The properties are framed as a query expression that can be evaluated by the storage system.

For example, to query for all vertices that have the annotation `date:02-15-1564` use the following command to evaluate this query and assign the result to `var1`:

```
-> var1 = getVertices(date:02-15-1564)
Time taken for query: 158 ms
```

In the case of `Neo4j`, the expressions can use the full [Lucene query syntax](http://lucene.apache.org/core/old_versioned_docs/versions/3_5_0/queryparsersyntax.html), including wildcards, lexicographic ranges, Boolean operators, fuzzy matching, and proximity searches.


---


### Finding paths between vertices ###

The `getPaths` class of queries lets the user find all paths between two vertices. The first argument is the source vertex identifier and the second argument is the destination vertex identifier. The maximum path length is specified in the third argument. For example, to find paths from vertex 2 to vertex 5 having a maximum length of 10, the following query could be used:

```
-> var2 = getPaths(2, 5, 10)
Time taken for query: 211 ms
```


---


### Retrieving lineage ###

The `getLineage()` class of queries is used find the ancestors or descendants of a specific provenance vertex.

  * The first argument is the `vertex id` used by the storage system to identify the starting vertex for the query.
  * The second argument is the maximum number of levels of the graph that should be returned.
  * The third argument is either `ancestors` or `descendants` to indicate whether to return the vertices from which the specified one was derived or the vertices which used the specified vertex.
  * The fourth argument is optional and specifies the expression on which the lineage should terminate.

For example, if the database contained **Artifact** vertices with the dates of birth of people and **WasDerivedFrom** edges from children to parents, this query could be used to find Galileo's parents:

```
-> var3 = getLineage(1024, 1, ancestors)
Time taken for query: 688 ms
```


---


### Listing results of queries ###

The `list` command can be used to show the results of queries that have been executed:

```
-> list
----------------------------------------------
Graph      | Expression
----------------------------------------------
var1       | getVertices(date:02-15-1564)
var2       | getPaths(2, 5, 10)
var3       | getLineage(1024, 1, ancestors)
----------------------------------------------
```


---


### Exporting results of queries ###

Query results can be exported to files in DOT format which can be rendered as images using [Graphviz](http://www.graphviz.org/). The following illustrates the use of the `export` command:

```
-> export var2 /tmp/galileo_parents.dot
Exported var2 to /tmp/galileo_parents.dot
```


---


### Importing previously exported results ###

Existing files in DOT format can be imported to result variables in the graph. The following illustrates the use of the `import` command:

```
-> import /tmp/galileo_parents.dot var3
Imported /tmp/galileo_parents.dot to var3
```


---


  * [An illustration of the use of the query command.](QueryExample.md)