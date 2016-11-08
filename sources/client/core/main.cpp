#include <cstdlib>
#include "client.hpp"
#include "gui.hh"

int             main(int argc, char **argv)
{
  Client        client;
  Gui gui(argc, argv, &client);

  client.setGUI(&gui);
  return (EXIT_SUCCESS);
}
