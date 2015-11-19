#pragma once


#define BOOST_SYSTEM_NO_DEPRECATED

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// WebSocket Connector
class WebSocketConnector {

public:
    WebSocketConnector();
    ~WebSocketConnector();

    typedef websocketpp::lib::lock_guard<websocketpp::lib::mutex> scoped_lock;
    typedef websocketpp::client<websocketpp::config::asio_client> client;

    client m_client;

    void run(const std::string & uri);
    void on_open(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_fail(websocketpp::connection_hdl hdl);

    websocketpp::lib::thread *asio_thread;

    websocketpp::lib::thread* getAsioThread() {return asio_thread;}

    websocketpp::connection_hdl& getNetworkHandle();
    websocketpp::lib::error_code& getErrorCode();

private:
    websocketpp::lib::error_code m_ec;
    websocketpp::connection_hdl m_hdl;
    websocketpp::lib::mutex m_lock;
    bool m_open;
    bool m_done;

};

