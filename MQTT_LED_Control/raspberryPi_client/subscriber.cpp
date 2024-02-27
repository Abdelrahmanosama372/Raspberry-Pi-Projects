#include <chrono>
#include <iostream>
#include <mqtt/async_client.h>
#include <mqtt/callback.h>
#include <mqtt/connect_options.h>
#include <mqtt/exception.h>
#include <string>
#include <thread>

#define SERVER_ADDRESS "tcp://192.168.1.109:1883"
#define CLIENT_ID "subscriber"

class SubscriberCallBack : public virtual mqtt::callback {
  public:
    void connected(const std::string& msg) override {
      std::cout << "connected to the broker" << std::endl;
    }

    void connection_lost(const std::string& ) override {
      std::cout << "connection lost" << std::endl;
    }

   void message_arrived(mqtt::const_message_ptr msg) override {
    std::cout << "Message Received: ["
              << "Topic: " << msg->get_topic()
              << ", Payload: " << msg->to_string()  << " ]" << std::endl;
  }
};

int main(int argc, const char** argv) {

  mqtt::async_client client(SERVER_ADDRESS,CLIENT_ID);
  try {
    SubscriberCallBack  subCb;
    client.set_callback(subCb);

    mqtt::connect_options conopt;
    conopt.set_keep_alive_interval(20);
    conopt.set_clean_session(true);
    client.connect(conopt)->wait();

    std::string topic = "ledState";
  
    client.subscribe(topic,1)->wait();
    std::this_thread::sleep_for(std::chrono::seconds(100));
    client.unsubscribe(topic)->wait();
    client.disconnect()->wait();
  }catch(mqtt::exception &execep){
    std::cout << "Error is " << execep.what() << std::endl;
  }

    return 0;
}
