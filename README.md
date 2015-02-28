# Visual GTK+
A Glade plugin to include a hack of Christian Hergert GtkBuilderScript and enable edit JavaScript.

![screenshot](https://dl.dropboxusercontent.com/u/36581494/captura-13.png "Screenshot")

## From the original README

GtkBuilder + Inline JavaScript.

This is a quick hack to allow writing javascript inside of a GtkBuilder xml
file and attaching signals to said javascript functions.

GScriptJs is an object that can be created from within the GtkBuilder file.
The "script" property is used to eval javascript into the JSContext.

Use a connect callback similar to connect_func in script.c.

Cheers, and Happy Hacking,

Christian Hergert <chris@dronelabs.com>

# Usage

## Install dependencies

In Ubuntu 14.10, install (at least) these packages:

* **libcjs-dev**: Required.
* **libgirepository1.0-dev**: Required.
* **libgladeui-dev**: For Glade plugin.
* **libgtksourceview-3.0-dev**: For editor, also required by Glade plugin.
* **gir1.2-gstreamer-1.0**: For guitar tuner example.
* **gir1.2-gda-5.0**: For phonebook example.

```
$ apt-get install libcjs-dev libgladeui-dev libgtksourceview-3.0-dev libgirepository1.0-dev gir1.2-gda-5.0 gir1.2-gstreamer-1.0
```

And, of course, a C compiler, make and pkg-config utilities and you probably want Glade too!

## Get source

```
git clone https://github.com/jmouriz/visual-gtk
```

## Set the environment

```
cd visual-gtk
. set-glade-environment.sh
```

This will exports:

* **PATH**: Search path to binary application.
* **LD_LIBRARY_PATH**: Search path to shared objects (.so) library.
* **GI_TYPELIB_PATH**: Search path to GObject Introspection .typelib file.
* **GLADE_CATALOG_SEARCH_PATH**: Search path to Glade catalog .xml file.
* **GLADE_MODULE_SEARCH_PATH**: Search path to Glade plugin (.so) file.
* **XDG_DATA_DIRS**: Search path to Glade palette icon.
* **GSCRIPT_MODULE_SEARCH_PATH**: Search path for GScript internal modules (.js).

## Build all

```
make
```

## Run examples

### Calculator

`g-script` [`examples/calculator/calculator.ui`](https://github.com/jmouriz/visual-gtk/blob/master/examples/calculator/calculator.ui)

[[Download](https://raw.githubusercontent.com/jmouriz/visual-gtk/master/examples/calculator/calculator.ui)]

![screenshot](https://dl.dropboxusercontent.com/u/36581494/calculator.png "Screenshot")

### Phone book

`g-script` [`examples/phonebook/phonebook.ui`](https://github.com/jmouriz/visual-gtk/blob/master/examples/phonebook/phonebook.ui)

[[Download](https://raw.githubusercontent.com/jmouriz/visual-gtk/master/examples/phonebook/phonebook.ui)]

![screenshot](https://dl.dropboxusercontent.com/u/36581494/phonebook.png "Screenshot")

### Guitar tuner

`g-script` [`examples/tuner/tuner.ui`](https://github.com/jmouriz/visual-gtk/blob/master/examples/tuner/tuner.ui)

[[Download](https://raw.githubusercontent.com/jmouriz/visual-gtk/master/examples/tuner/tuner.ui)]

![screenshot](https://dl.dropboxusercontent.com/u/36581494/tuner.png "Screenshot")

### Image viewer

`g-script` [`examples/viewer/viewer.ui`](https://github.com/jmouriz/visual-gtk/blob/master/examples/viewer/viewer.ui)

[[Download](https://raw.githubusercontent.com/jmouriz/visual-gtk/master/examples/viewer/viewer.ui)]

![screenshot](https://dl.dropboxusercontent.com/u/36581494/viewer.png "Screenshot")

And enjoy with Glade.

Juan Manuel Mouriz <jmouriz@gmail.com>
