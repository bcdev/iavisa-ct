  HOW TO INSTALL

Build the IAVISA Cloud Test library by changing  in either the
Release or Debug directory and type 'make'. Move the resulting
libiavisa-1.2.a static library  to a path appropriate for your
development environment.

Create a new IAVISA home directory and  copy the 'auxdata' and 
'optdata' folders into the newly created directory.

Set the environment variable 'IAVISA_HOME' to your IAVISA home
directory.

In order to use the IAVISA library build your source code with
gcc using the '-c' option and  link the resulting object files
with g++ to build the executable.
 

  CONTACT

Ralf Quast
Brockmann Consult

ralf.quast@brockmann-consult.de
