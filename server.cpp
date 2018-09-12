
#include <opencv2/opencv.hpp>
#include "MultiClientServer.h"
#include "structs.h"

int main(void){


    cv::Mat image1 = cv::imread("/home/bardo91/Pictures/arms_coordinates.png");
    cv::Mat image2 = cv::imread("/home/bardo91/Pictures/Selection_039.png");

    std::vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(30); //image quality
    bool imageSelector = false;

    mcs::MultiClientServer<mcs::eSocketType::UDP> server(9973);

    while(true){
        std::vector<uchar> buffer;
        if(imageSelector)
            cv::imencode(".jpg", image1, buffer, params);
        else
            cv::imencode(".jpg", image2, buffer, params);

        int numPackets = buffer.size()/PACKET_SIZE + 1;
        for(unsigned i = 0; i < numPackets ; i++){
            DataPacket packet;
            packet.packetId = i;
            packet.isFirst = i == 0;
            packet.numPackets = numPackets;
            packet.totalSize = buffer.size();

            int endSize = (i == numPackets-1)? buffer.size() % PACKET_SIZE : PACKET_SIZE;
            packet.packetSize = endSize;

            std::copy(  buffer.begin()+i*PACKET_SIZE, 
                        buffer.begin()+(i+1)*endSize, 
                        packet.buffer);
                        

            server.writeOnClients<DataPacket>(packet);
        }
        imageSelector = !imageSelector;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


}