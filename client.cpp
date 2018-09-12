

#include <opencv2/opencv.hpp>
#include "structs.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <iostream>

using boost::asio::ip::udp;

int main(void){

    boost::asio::io_service io_service;
	
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 9973);
    udp::socket socket(io_service);
    socket.open(udp::v4());

    boost::array<char, 1> send_buf = { { 0 } };
    socket.send_to(boost::asio::buffer(send_buf), endpoint);

    bool isFirst = true;
    int packetId = -1;
    std::vector<char> buffer;

    while(true){

        boost::array<char, sizeof(DataPacket)> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        DataPacket packet;
        memcpy(&packet, &recv_buf[0], sizeof(DataPacket));

        if(isFirst == packet.isFirst){
            if(isFirst)
                std::cout << packet.numPackets << ": ";

            std::cout << packet.packetId << "|";
            std::cout.flush();
            
            isFirst = false;
            if(packetId + 1 == packet.packetId){
                buffer.insert(buffer.end(), packet.buffer, packet.buffer+packet.packetSize);
                packetId++;
                if(packet.packetId == packet.numPackets-1){
                    // decode image
                    cv::Mat image = cv::imdecode(buffer, 1);
                    cv::imshow("image", image);
                    cv::waitKey(10);    

                    // reset data
                    isFirst = true;
                    packetId = -1;
                    buffer.clear();
                    std::cout << std::endl;
                }
            }
        }else{
            std::cout << std::endl;
        }

    }

}