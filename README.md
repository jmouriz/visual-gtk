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

## Get source

```shell
git clone https://github.com/jmouriz/visual-gtk
```

## Install dependencies

In Ubuntu 14.10, install (at least) these packages:

* libcjs-dev
* libgladeui-dev
* libgtksourceview-3.0-dev

```shell
$ apt-get install libcjs-dev libgladeui-dev libgtksourceview-3.0-dev
```

(TODO: And GObject Introspection stuff)

## Build all

```shell
cd visual-gtk
make
```

## Set the environment

```shell
. set-glade-environment.sh
```

And enjoy (test) with Glade, tests and examples.

Juan Manuel Mouriz <jmouriz@gmail.com>
