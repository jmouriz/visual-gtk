#!/usr/bin/env cjs

const Gtk = imports.gi.Gtk;
const GScript = imports.gi.G;
const Lang = imports.lang;

const Callbacks = new Lang.Class({
    Name: 'Callbacks',

    _init: function () {},

    onClicked: function () {
      print("onClicked")
    },

    onQuit: function () {
      Gtk.main_quit()
    },

    _connector: function(builder, object, signal, handler) {
      object.connect(signal, Lang.bind(this, this[handler]));
    },
});


Gtk.init(null);

let script = new GScript.Script(); /* unused object, just a hack for register type */

let builder = new Gtk.Builder();
let callbacks = new Callbacks();

builder.add_from_file("test-5.ui");
builder.connect_signals_full(Lang.bind(callbacks, callbacks._connector));

let w = builder.get_object("window");

w.present();

Gtk.main();
