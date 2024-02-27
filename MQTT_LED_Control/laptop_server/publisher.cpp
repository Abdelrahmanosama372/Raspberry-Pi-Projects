#include <chrono>
#include <iostream>
#include <mqtt/async_client.h>
#include <mqtt/callback.h>
#include <mqtt/connect_options.h>
#include <mqtt/exception.h>
#include <string>
#include <thread>

#define SERVER_ADDRESS "tcp://localhost:1883"
#define CLIENT_ID "publisher"

class PublisherCallBack : public virtual mqtt::callback {
  public:
    void connected(const std::string& msg) override {
    std::cout << "connected to the broker" << std::endl;
    }

    void connection_lost(const std::string& ) override {
    std::cout << "connection lost" << std::endl;
    }

    void delivery_complete (mqtt::delivery_token_ptr delivery) override{
    std::cout << "published data is " << delivery->get_message()->get_payload() << std::endl;
    }

};

int main(int argc, const char** argv) {

  mqtt::async_client client(SERVER_ADDRESS,CLIENT_ID);
  try {
    PublisherCallBack  pubCb;
    client.set_callback(pubCb);

    mqtt::connect_options conopt;
    conopt.set_keep_alive_interval(20);
    conopt.set_clean_session(true);
    client.connect(conopt)->wait();

    std::string topic = "ledState";
    std::string payload = "on";
    int qos = 1;
    bool retained = false;

    while(true){
        std::cin >> payload;
        if(payload == "quit")
            break;
        client.publish(topic,payload,qos,retained)->wait();
    }
    client.disconnect()->wait();

    }catch(mqtt::exception &execep){
        std::cout << "Error is " << execep.what() << std::endl;
    }

    return 0;
}
