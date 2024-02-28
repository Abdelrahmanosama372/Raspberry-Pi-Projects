#include "publisher.hpp"

void PublisherCallBack::connected(const std::string& msg) {
  std::cout << "connected to the broker" << std::endl;
}

void PublisherCallBack::connection_lost(const std::string& ) {
  std::cout << "connection lost" << std::endl;
}

void PublisherCallBack::delivery_complete (mqtt::delivery_token_ptr delivery){
  std::cout << "published data is " << delivery->get_message()->get_payload() << std::endl;
}

// publisher class methods definitions
Publisher::Publisher(std::string topic): client(SERVER_ADDRESS,CLIENT_ID),topic(topic){
  mqtt::connect_options conopt;
  conopt.set_keep_alive_interval(20);
  conopt.set_clean_session(true);
  try {
    client.set_callback(pubCb);      
    client.connect(conopt)->wait();
  }catch(mqtt::exception &execep){
    std::cout << "Error is " << execep.what() << std::endl;
  }
}

void Publisher::input_publish(){
  std::string payload;
  while(true){
    std::cin >> payload;
    try{
      client.publish(topic,payload,1,false)->wait();
    }catch(mqtt::exception &execep){
      std::cout << "Error is " << execep.what() << std::endl;
    }
        
    if(payload == "quit")
        break;
  }
}

Publisher::~Publisher(){
  client.disconnect()->wait();
}

