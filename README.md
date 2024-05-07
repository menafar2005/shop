
# MyPlanets

## CSV database of various space objects with viewing, editing and creation modes

## Application designed and built with Qt6 in C++

### Authors: A.V. Saganenko

#### Saint Petersburg State University of Telecunications

### Description

Desktop application for managing csv database. The database provides information about various space objects: planets, stars, galaxies, and so on. From the information provided: name, type, subtype, radius, weight, number of satellites, population, rotation period, temperature of various space objects. The application is implemented on Qt6.3.0 in C++. The main elements of the model are container classes: STL's vector, Qt's QStringList, the developed queue. There are three separate modes of the program: viewing, editing, creating.

### Development notes

* PL: C++/C (>11)
* IDE: Qt 6.3.0
* Compiler: MinGw 11.2.0 64bit
* Debugger: GNU gdb 11.2.0
* CMake: CMake 3.21.1 Qt
* Dev OS: Windows 10 (19044)

View mode uses Qt's QStringList, create mode uses queue.h's Queue class container, edit mode uses STL's vector. Most bugs were detected at edit mode. Be careful while working with parsing and open/save file. Otherwise, everything should work properly. Note, optimization should be improved with load and saving functions. A lot of work should be done with images.

### Launch conditions

* To launch, fix bugs and test, update, write and develop new functionality, open MyPlanets.pro in Qt Creator. Build debug, release or whatever configured version. Latest compatible version is 6.3.0. Probably compatible with older and newer versions, still better not to use with < Qt5 and > Qt7. When developing and optimizing, you should pay attention to the editing mode, as it has many pitfalls. Also be advised that queue.h is a custom-made class container, be sure to read it thoroughly in case of improving creating mode. Use source files located at src folder; use ui files located at forms
* To launch in release mode, use generated MyPlanets.exe which will be present in GitHub release's zip named release. Be sure not to lose any DLLs. Tested on clear Win10 22h2 64bit. So it should be compatible with most systems.

#### Additional note

Build contains a testing Qt resource file, called demo_package.qrc. It can be removed, however it is not recommended (be ready for undefined behavior). Main resource file package.qrc should not be removed ever.

### Features

* Browsing databases. Every line field, every image is displayed. The database must be created in the same application and have csv or txt format. Navigation via buttons or list. Opening other modes is done through the menubar at the top of the window
* Browsing database's CSV file
* Database creation. One can enter each field, select an image. There is a preview of the final file. It is possible to clear the fields and the database, to save the database to the selected location on the disk
* Database editing. Change any column of any row in the database. Adding new lines, deleting old ones. Saving the database. Merging of several databases into one. Navigation through the list
* Most of the exceptions have been handled. Easy navigation. Acceptable and convenient visual style.
  
##### More information at Doc_RU.pdf (russian language)
