#include <cstdlib>
#include "client.hpp"
#include "gui.hh"

int             main(int argc, char **argv)
{
  Gui gui(argc, argv);
  Client        client(&gui);

  gui.setClient(&client);
  client.startGUI();
  return (EXIT_SUCCESS);
}
