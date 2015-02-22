#!/usr/bin/env cjs

const Gtk = imports.gi.Gtk;
const GScriptJs = imports.gi.GScriptJs;
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

let builder = new Gtk.Builder();
let callbacks = new Callbacks();

builder.add_from_file("test-5.ui");
builder.connect_signals_full(Lang.bind(callbacks, callbacks._connector));

let window = builder.get_object("window");

window.present();

Gtk.main();
