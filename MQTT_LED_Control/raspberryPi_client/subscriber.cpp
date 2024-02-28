#include "subscriber.hpp"

void controlLed(const std::string order){
  std::ofstream fs;
  fs.open("/sys/class/leds/test/brightness");
  if(!fs.is_open()){
    std::cout << "failed to open the file" << std::endl;
    return;
  }
  if(order == "on")
    fs << 1 << std::endl;
  else
    fs << 0 << std::endl;
  fs.close();
}

// SubscriberCallBack class methods definitions
void SubscriberCallBack::connected(const std::string& msg){
    std::cout << "connected to the broker" << std::endl;
}

void SubscriberCallBack::connection_lost(const std::string& ){
    std::cout << "connection lost" << std::endl;
}

void SubscriberCallBack::message_arrived(mqtt::const_message_ptr msg){
    std::cout << "Message Received: ["
              << "Topic: " << msg->get_topic()
              << ", Payload: " << msg->to_string()  << " ]" << std::endl;
    if(msg->to_string() == "quit"){
      // stop spining
      spining = false;
      return;
    }
    controlLed(msg->to_string());
}

// subscriber class methods definitions
Subscriber::Subscriber(std::string topic):client(SERVER_ADDRESS,CLIENT_ID), 
  topic(topic), spining(true), subCb(spining){
  mqtt::connect_options conopt;
  conopt.set_keep_alive_interval(20);
  conopt.set_clean_session(true);
  try {
    client.set_callback(subCb);      
    client.connect(conopt)->wait();
    client.subscribe(topic,1)->wait();
  }catch(mqtt::exception &execep){
    std::cout << "Error is " << execep.what() << std::endl;
  }
}

Subscriber::~Subscriber(){
    client.unsubscribe(topic)->wait();
    client.disconnect()->wait();
}

