#include "Protocol.hpp"

static struct BabelPacket          *Protocol::Protocol::createPacket(Protocol::BabelPacket::Code const code, unsigned int const &length, unsigned char *data)
{
  struct BabelPacket *packet = reinterpret_cast<Protocol::BabelPacket *>(new char[sizeof(Protocol::BabelPacket) + length]);

  packet->magicNbr = MAGIC_NUMBER;
  packet->code = code
  packet->dataLength = length;
  packet->data = data
  return packet;
}

