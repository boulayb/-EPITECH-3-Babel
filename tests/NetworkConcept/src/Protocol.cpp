#include "Protocol.hpp"

struct Protocol::BabelPacket          *Protocol::Protocol::createPacket(BabelPacket::Code code, unsigned char *data, unsigned int const &length)
{
  struct BabelPacket *packet = reinterpret_cast<BabelPacket *>(new char[sizeof(BabelPacket) + length]);

  packet->magicNbr = MAGIC_NUMBER;
  packet->code = code;
  packet->dataLength = length;
  packet->data[0] = *data;
  return packet;
}

