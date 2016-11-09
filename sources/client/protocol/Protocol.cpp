#include <algorithm>
#include <cstring>
#include "Protocol.hpp"

struct Protocol::BabelPacket          *Protocol::Protocol::createPacket(BabelPacket::Code code, unsigned char *data, unsigned int const &length)
{
  struct BabelPacket *packet = reinterpret_cast<BabelPacket *>(new char[sizeof(BabelPacket) + length]);

  packet->magicNbr = MAGIC_NUMBER;
  packet->code = code;
  packet->dataLength = length;
  std::memcpy(packet->data, data, length);
  return packet;
}


unsigned char                 *Protocol::Protocol::stringToPointer(std::string const &data)
{
  unsigned char *basicData = new unsigned char[data.size() + 1];
  std::copy(data.begin(), data.end(), basicData);
  basicData[data.size()] = '\0';
  return basicData;
}

std::string *Protocol::Protocol::extractData(BabelPacket const &packet)
{
  unsigned size = packet.dataLength;
  std::string *data = new std::string;
  for (unsigned i = 0; i < size; ++i)
  {
    data += packet.data[i];
  }
  return data;
}