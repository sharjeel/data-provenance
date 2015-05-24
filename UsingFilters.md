# _Using filters_ #

### Adding filters ###

SPADE supports the use of multiple filters for processing provenance metadata. A list of currently configured filters is maintained. At the outset this does not contain any filters. To add a filter, its name must be specified along with the location in the list where it should be inserted. To add a new filter and make it the first to process incoming provenance, it should be inserted into location 0. For example:

```
-> add filter IORuns 0
Adding filter IORuns... done
```

Another filter may then be added **before** the IORuns filter by also specifying 0 as the location:

```
-> add filter CycleAvoidance 0
Adding filter CycleAvoidance... done
```

At this point, CycleAvoidance is located at index 0 and IORuns is located at index 1. Another filter can be added **after** CycleAvoidance and **before** IORuns by specifying 1 as the index:

```
-> add filter GraphFinesse 1
Adding filter GraphFinesse... done
```

Based on the list maintained by SPADE, data provenance will first be transformed by CycleAvoidance, then GraphFinesse, and finally by IORuns, before being delivered to storage.


---


### Removing filters ###

To remove a filter, simply specify the index:

```
-> remove filter 1
Removing filter GraphFinesse... done
```


---


### Listing filters ###

To show the list of filters currently attached to SPADE, use the following command:

```
-> list filters
3 filter(s) added:
    1. CycleAvoidance
    2. IORuns
```