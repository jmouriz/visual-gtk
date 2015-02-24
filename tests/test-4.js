imports.searchPath.unshift('.'); 

var module = imports.module;

function onClicked(widget, data)
{
  let window = document.get_object("window");

  window.title = "It's works";
}

function onQuit()
{
  module.quit(); // document.quit();
}
