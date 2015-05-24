# _Collecting system-wide provenance on Linux_ #

The Audit reporter is built automatically when the `make` command is issued.

Before this reporter can be used, the following commands must be executed. These commands only need to be executed once after SPADE is compiled.

The first command allows SPADE to configure the audit rules needed to generate the provenance graph. The second command launches the audit daemon. Finally, the last two commands grant SPADE access to the audit stream:

```
sudo chmod ug+s `which auditctl`
sudo auditd
sudo chown root lib/spadeLinuxAudit
sudo chmod ug+s lib/spadeLinuxAudit
```

Furthermore, to allow this reporter access to the audit stream, edit the file `/etc/audisp/plugins.d/af_unix.conf` and activate this plugin by changing the line that says

```
active = no
```

to

```
active = yes
```


---


To activate the transformation of the audit event stream into provenance records, the following command must be executed in the SPADE controller:

```
-> add reporter Audit
Adding reporter Audit... done
```