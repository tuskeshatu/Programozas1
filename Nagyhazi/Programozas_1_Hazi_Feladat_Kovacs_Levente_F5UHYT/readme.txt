Budapesti Muszaki Es Gazdasagtudomanyi Egyetem
Villamosmernoki es Informatikai Kar
Programozas alapjai 1
Hazi feladat
Kovacs Levente F5UHYT

You can find the source code and a compiled .exe executable in the 'Code' directory.

debugmalloc.h in the 'Code' directory is necesarry for memory leak detection. It WILL prevent gcc from
compiling the source file if -Werror flag is present (see more: Develpoer guide). If you want to remove
debugmalloc.h remove the include in the top section of the source file too.

In the 'zebegeny-nagymaros_testfiles' directory you will find 12 .gpx files. These are the test files
containing a network of some trails near Zebegeny and Nagymaros used for testing and demonstration
purposes. You can read more about testing on the 'Testing documentation' page in the doxygen generated
documentation. There is also a stdin.txt file containing 2 example coordinates. They are a start and a
destination point of a demo route (see more: stdin_txt_test.png). In order to generate the map from the
.gpx files just give them as command prompt arguments after the name of the executable when launching
(see more: User manual). These files are route.gpx and track.gpx files in pairs (so 1 is the route of the
first trail, 2 is the track of the first trail...).

You can find the main page of the doxygen generated documentation in 'Documentation/Doxygen/html/index.html'.

There is also a Doxyfile with relative references to the source file, images and the working directory. If
you want to rerender the documentation with your own doxygen, you should use the provided 'Doxyfile' as a
config file.