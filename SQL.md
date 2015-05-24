# _Storing provenance in a relational database_ #

The SQL storage can be added to SPADE using the controller, allowing provenance records to be sent to a relational database. Note that four arguments must be provided when adding this storage: **the database driver to use, database URL, username, and password**. When adding the storage using the controller, these arguments are separated by spaces. If either the username or password is unused, the string literal `null` should be used.

SPADE comes pre-packaged with the H2 SQL library and the following example shows how to use it to create a database in the filesystem:

```
-> add storage SQL org.h2.Driver jdbc:h2:/tmp/sql/spade.sql_db sa null
Adding storage SQL... done
```

This will create a database in the filesystem at `/tmp/sql/spade.sql_db` if it does not exist, or use the existing database if it has previously been created. The username for connecting to this database will be `sa` and no password will be used.


---


The following will cause SPADE to stop sending provenance records to the SQL database:

```
-> remove storage SQL
Shutting down storage SQL... done
```