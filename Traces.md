# ProvBench Traces #

Below are provenance traces collected from three applications (Apache, BLAST, PostMark), each run on three operating systems (Linux, Mac OS X, and Windows). Each trace was collected using **SPADE** with a Linux / Mac OS X / Windows reporter and H2 SQL storage.

For more information about the workloads, please see:

  * Hasnain Lakhani, Rashid Tahir, Azeem Aqil, Fareed Zaffar, Dawood Tariq, and Ashish Gehani, **Optimized Rollback and Re-computation**, _46th IEEE Hawaii International Conference on Systems Science (HICSS)_, IEEE Computer Society, 2013. [[PDF](http://www.csl.sri.com/users/gehani/papers/HICSS-2013.Re-execution.pdf)]

The provenance traces are provided in compressed SQL script format. This can be imported into most SQL databases.

<table align='center' border='1'>
<tr>
<th width='80'></th>
<th width='210'>Linux (Linux Audit)</th>
<th width='210'>Mac OS X (OpenBSM)</th>
<th width='210'>Windows (Process Monitor)</th>
</tr>
<tr>
<th align='left'>Apache</th>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Linux/Apache/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Linux/Apache/linux_apache_h2.tar.gz'>H2 database</a>
</td>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Mac/Apache/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Mac/Apache/mac_apache_h2.tar.gz'>H2 database</a>
</td>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Windows/Apache/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Windows/Apache/windows_apache_h2.tar.gz'>H2 database</a>
</td>
</tr>
<tr>
<th align='left'>BLAST</th>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Linux/Blast/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Linux/Blast/linux_blast_h2.tar.gz'>H2 database</a>
</td>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Mac/Blast/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Mac/Blast/mac_blast_h2.tar.gz'>H2 database</a>
</td>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Windows/Blast/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Windows/Blast/windows_blast_h2.tar.gz'>H2 database</a>
</td>
</tr>
<tr>
<th align='left'>PostMark</th>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Linux/Postmark/script.tar.gz'>SQL script</a>, <a href='http://data-provenance.googlecode.com/svn/wiki/traces/Linux/Postmark/linux_postmark_h2.tar.gz'>H2 database</a>
</td>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Mac/Postmark/script.tar.gz'>SQL script</a>, <a href='http://data-provenance.googlecode.com/svn/wiki/traces/Mac/Postmark/mac_postmark_h2.tar.gz'>H2 database</a>
</td>
<td align='center'>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Windows/Postmark/script.tar.gz'>SQL script</a>,<br>
<a href='http://data-provenance.googlecode.com/svn/wiki/traces/Windows/Postmark/windows_postmark_h2.tar.gz'>H2 database</a>
</td>
</tr>
</table>

### Importing into MySQL ###

To import the provenance traces into MySQL, use the following command on Linux or Mac OS X, replacing `{user}` and `{password}` with your MySQL credentials:

```
gzip -dc < script.tar.gz | mysql -u {user} -p {password}
```

### Viewing the H2 SQL database ###

To browse the H2 SQL database without importing the SQL script into an existing database, follow the instructions [here](DBTools.md).

### Generating the provenance traces ###

For **Apache**, the following commands were used on Linux and Mac OS X:

```
./configure
make
```

The following command was used on Windows:

```
nmake /f Makefile.win _apached
```


---


For **Postmark**, the following configuration settings were used for the benchmark:

```
Base number of files: 500
Transactions: 500
Files range between 500 bytes and 9.77 kilobytes in size
Block sizes: read=512 bytes, write=512 bytes
```


---


For **BLAST**, the input data set was downloaded from [ftp://ftp.ncbi.nlm.nih.gov/genomes/INFLUENZA/influenza.faa](ftp://ftp.ncbi.nlm.nih.gov/genomes/INFLUENZA/influenza.faa) and the following command was used:

```
makeblastdb -in influenza.faa -parse_seqids -hash_index -out outputdb
```


---


|This material is based upon work supported by the National Science Foundation under Grants [OCI-0722068](http://www.nsf.gov/awardsearch/showAward?AWD_ID=0722068)<sup>1</sup> and [IIS-1116414](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1116414)<sup>2</sup>. Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.|
|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

<sup>1</sup> NSF Grant 0722068: [Scalable Authentication of Grid Data Provenance](http://www.nsf.gov/awardsearch/showAward?AWD_ID=0722068), PI: [Ashish Gehani](http://www.csl.sri.com/people/gehani/)

<sup>2</sup> NSF Grant 1116414: [Scalable Integration and Analysis of the Provenance of Diverse Scientific Data](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1116414), PI: [Ashish Gehani](http://www.csl.sri.com/people/gehani/)