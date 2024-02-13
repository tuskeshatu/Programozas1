\page user_manual User manual
\tableofcontents

# Input files

The program builds a map of trails. The way to provide these trails is to have 2 .gpx extension files for each trail.
The .gpx extension is basically an xml file, which is optimised and standardised to include gps points in it. There are
multiple types of .gpx file, which are intended for different purposes. The ones you will be dealing with are the route
and the trail types.

\attention In order for the program to function correctly, you need to have a route and a trail type of gpx files for each trail
you want to include in the built map.

## Route .gpx files

The route type is optimised to give directions. This means that it only has the intersections (in some cases other points of interest)
marked in it, without elevation data. This comes in handy, as the program only has to store the intersections in memory, which can drastically reduce memory usage.

## Track .gpx files

The track type holds every recorded gps point with elevation data along a path. This is needed in order to calculate the distance and the
climb and descent of the trail in between intersections.

\note You can acquire route and trail files by clicking [here](https://turistautak.openstreetmap.hu/turautvonal.php) and then
manually selecting a few points along a trail you want to include in your map. When you finished highlighting the trail, you can
click **route.gpx** and **ele-track.gpx** on the left to download the route and trail files.

\warning Be careful! Don't mix up different trail's route and track files because this will result in an error!

# Running the program

## Specifying trails

If you have a compiled version of the source C file, you can specify which files you want to use to build the map by specifying them
as command line arguments. Eg. to build a map of the *red trail* with *route-red.gpx* and *ele-track-red.gpx* you want to run the program
with the following prompt: **<program_executable_name_with_extension> route-red.gpx ele-track-red.gpx**

\warning Make sure to provide the .gpx files in the correct order: **First route and then the corresponding track file.**

\warning Do not forget to put the .gpx extension after the file names!

You also may want to include multiple trails, which you can do by just writing the route and track file names after eachother in pairs.

## Specifying start and end points for the planning

If the map building process finished succesfully the program will ask you to provide start and destination coordinates. Coordinates should
be provided as a decimal number with the latitude and the longitude in this order. You may separate the lat and lon parts by any number of
whitespace charachters (such as spaces or new lines), the program will not proceed until it reads two coordinates succesfully.

The program will snap the coordinates provided to the nearest intersection on the map and will provide you information about the start and
end point of the route it is planning on.

\note If you provide valid coordinates further than 1 km away from the nearest intersection on the trail, there will be a prompt asking you
to confirm.

# Results of planning

If everything went smoothly, the program should output the basic data about your route. It will plan a shortest route and calculate an ITRA-score
for it.

\note The ITRA-score of a route is the **distance** (km) **+ elevation difference**(m) / **100**.