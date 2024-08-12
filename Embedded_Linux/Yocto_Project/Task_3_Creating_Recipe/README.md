# Recipe (.bb)

recipe is a set of instructions used by the build system to compile and install a package, create an image, or perform other tasks. 
Recipes are written in a specific format, typically as .bb files (BitBake recipes), and they describe how to fetch, configure, compile, and install software or other components.





## Metadata


This section provides essential information about the package, such as its name, version, and licensing details. 
For example, the recipe will specify the name of the software, a brief summary, and a description of what the package does. 
It will also declare the license under which the software is distributed, ensuring that the legal aspects are handled properly.


```
SUMMARY = "Hello From myrecipe"

DESCRIPTION = "Recipe created by Mohamed Saker"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

```

The license here is the contract between you and the Yocto Porject so don't take this as a trivial aspect so for ensuring the we have to make a hash value for it using md5

To generate digest for the checksum


```
md5sum MIT
```


and to list all the possible licenses



```
cd /poky/meta/files/common-licenses

```



## Source Fetching

This section of the recipe describes where the source code of the software can be found. 
The source code could be hosted in a variety of places, such as a Git repository, a URL pointing to a compressed file, or a local directory. 
The recipe includes instructions on how to fetch this source code. Often, checksums are provided to ensure that the downloaded source code has not been altered or corrupted.

1- To get the source from a repo

```
SRC_URL="git://<repo link>,protocol=<protocol>,branch=<branch>"
SRC_URL="git://git...com,protocol=https,branch=main"
```




```

#check specific hash commit
SRC_REV="commit hash"

```


2- To get the file in the local machine

```
SRC_URL="file://<filename>"

```


## Hidden Local Variables


Formula -> PV_PV-PR.bb


PV: Package Version

PR: Package Release

PN: package Name

S: source directory for recipe (un pack gz & zip)

D: destination directory used by package feeder

B: build directory (compile)

WORKDIR: top directory include S, D and B directories




## Build Instructions

This is where the actual work of compiling the software happens. The recipe provides instructions on how to configure the build environment and compile the source code. 
Yocto has default processes for common tasks like configuring the build or compiling the code, but these can be customized if the software requires special handling.


```
do_compile()
{
	{CC} {CFLAGS} main.c -o {B}/myapp
}


do_install()
{
    mkdir -p ${D}${bindir}

	  cp ${B}/myapp ${D}${bindir}
}



```


