\page test_doc Testing documentation
\tableofcontents

# Full-scale operational testing

The full scale testing with multiple trails was carried out by building a map consisting of 6 trails in total (with around a total of 850 gps points recorded) all around the Nagymaros-Zebegeny area with numerous intersections and circles in the trail. The program uses around 37 kB of memory.

\image html nagymaros-zebegeny.png "Nagymaros-Zebegeny trail system for testing"

## Points near or on the path

When a start and destination point was specified near or on the mapped trails, the program found the correct nearest point and planned the route accordingly. The output distances were always within a few percentile of the actual path length.

## Points far off the path

The program behaves as expected and warns the user of the distance between the nearest trail point and the selected point. If the aswser to the warning is not y/Y the program terminates with exit code 1 and displays the help message.

# User input errors

## Command line arguments - input files

### Order of files or not matching route and track files

If the user specifies the files in the wrong order (track after route) or the track file doesn't match up with the route file read_nodes_from_route() fails. The program displays error messages of the files that failed to be read, displays help message and terminates with exit code 1.

### Missing file extension

If the user fails to specify file extension read_nodes_from_route() fails. The program displays error messages of the files that failed to be read, displays warning about missing file extension, displays help message and terminates with exit code 1.

### Missing route or track files

If the user doesn't specify all route and track files (the number of arguments are odd) the program displays error messages of the missing files,  displays help message and terminates with exit code 1.

## Coordinate format error

If the input coordinates for start and/or destination points are not matching the specified format (Expected coordinate input format: Decimal coordinates (with decimal point). Latitude and longitude should be separated with any whitespace character. Example: 48.0976397 20.7301719) the program displays error about coordinate formats, displays help message and terminates with exit code 1.

# File errors, corrupted files

Empty or extra lines differing from the ones outlined in the .gpx format guide are not a problem as long as the coordinates are untouched. If there is a disruption of the sequence or the format of coordinate records (not lat=* lon=* format, missing <trkpt and <ele> markers, extra whitespace in these specific lines) the program can read and process the records. If there is an error encountered read_nodes_from_route() fails. The program displays error messages of the files that failed to be read, displays help message and terminates with exit code 1.

\note No memory leaks were experienced during testing. Fail conditions always free up memory, display relevant error messages on stderr, display help message and the program terminates with exit code 1.