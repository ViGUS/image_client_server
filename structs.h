
const int PACKET_SIZE = 1024;

struct DataPacket{
    bool isFirst = false;
    int packetId = 0;
    int numPackets = 0;
    int totalSize = 0;
    int packetSize = 0;
    char buffer[PACKET_SIZE];
};