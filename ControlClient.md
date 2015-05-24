# _Starting and controlling SPADE_ #

To start the SPADE server, use the following command (in the `SPADE/bin` directory):

```
spade-start.sh
```

<a href='Hidden comment: 
This will start the SPADE server as a background process. Note that the server allows multiple startup options. To start as a foreground process, use the following:

```
spade-server console
```

SPADE can also be installed as a service to be started every time the system is booted. However, installing this service can only be done by a super-user. To install SPADE as a service, use this command:

```
sudo spade-server install
```

To uninstall the SPADE service, use:

```
sudo spade-server remove
```

To see whether SPADE is currently running or not, use the following command:

```
spade-server status
```
'></a>

---


To start the controller used to configure the SPADE server, execute the following command (in the `SPADE/bin` directory):

```
spade-controller.sh
```

The following will appear:

```
SPADE 2.0 Control Client

Available commands:
       add reporter|storage <class name> <initialization arguments>
       add filter <class name> <index>
       add sketch <class name> <storage class name>
       remove reporter|storage|sketch <class name>
       remove filter <index>
       list reporters|storages|filters|sketches|all
       config load|save <filename>
       exit
       shutdown

-> 
```


---


At the outset, no reporters, storage, filters, or sketches are present. This can be seen with the `list` command:

```
-> list reporters
No reporters added

-> list storages
No storage added

-> list filters
No filters added

-> list sketches
No sketches added
```


---


To exit the controller without stopping the SPADE server, use the `exit` command:

```
-> exit
```


---


To stop the SPADE server completely, use the `shutdown` command:

```
-> shutdown
```