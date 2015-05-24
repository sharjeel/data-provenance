# _Storing provenance in a graph database_ #

Storage in the Neo4j graph database can be activated using the SPADE controller. A single argument must be provided. This is the location in the filesystem where the database is to be created if it does not exist, or where it is to be retrieved from if it has previously been created. In the example below `/tmp/spade.graph_db` is the location of the database:

```
-> add storage Neo4j /tmp/spade.graph_db
Adding storage Neo4j... done
```


---


Storage can be added and removed while the SPADE server is running. For example, this will cause the server to stop sending provenance records to the Neo4j database:

```
-> remove storage Neo4j
Shutting down storage Neo4j... done
```