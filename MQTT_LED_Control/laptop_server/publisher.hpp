#ifndef _PUBLISHER_HPP
#define _PUBLISHER_HPP

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
    void connected(const std::string& msg) override;
    void connection_lost(const std::string& ) override;
    void delivery_complete (mqtt::delivery_token_ptr delivery) override;
};

class Publisher {
  private:
    mqtt::async_client client;
    PublisherCallBack  pubCb;
    std::string topic;
  public:
    Publisher(std::string topic);
    void input_publish();
    ~Publisher();
};


#endif // !_PUBLISHER_HPP

