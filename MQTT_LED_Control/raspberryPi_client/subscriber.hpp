#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mqtt/async_client.h>
#include <mqtt/callback.h>
#include <mqtt/connect_options.h>
#include <mqtt/exception.h>
#include <string>
#include <thread>

#define SERVER_ADDRESS "tcp://192.168.1.109:1883"
#define CLIENT_ID "subscriber"

void controlLed(const std::string order);
void done_spining();

class SubscriberCallBack : public virtual mqtt::callback {
  private:
    bool &spining;
  public:
    SubscriberCallBack(bool &spining):spining(spining) {}
    void connected(const std::string& msg) override;
    void connection_lost(const std::string& ) override;
    void message_arrived(mqtt::const_message_ptr msg) override;
};

class Subscriber{
  private:
    mqtt::async_client client;
    SubscriberCallBack  subCb;
    std::string topic;
    bool spining;
  public:
    Subscriber(std::string topic);
    // blocking spin
    void spin(){
      while(spining);
    }
    ~Subscriber();
};
