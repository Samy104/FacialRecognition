/*
 * Code taken from the WebSocketPP Telemetry Client Example.
 * Credits to the WebSocketPP developper
 *
 */

#include "WebSocketConnector.h"

WebSocketConnector::WebSocketConnector() : m_open(false), m_done(false)
{
    // set up access channels to only log interesting things
    m_client.clear_access_channels(websocketpp::log::alevel::all);
    m_client.set_access_channels(websocketpp::log::alevel::connect);
    m_client.set_access_channels(websocketpp::log::alevel::disconnect);
    m_client.set_access_channels(websocketpp::log::alevel::app);

    // Initialize the Asio transport policy
    m_client.init_asio();

    // Bind the handlers we are using
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::bind;
    m_client.set_open_handler(bind(&WebSocketConnector::on_open,this,::_1));
    m_client.set_close_handler(bind(&WebSocketConnector::on_close,this,::_1));
    m_client.set_fail_handler(bind(&WebSocketConnector::on_fail,this,::_1));
}

// This method will block until the connection is complete
void WebSocketConnector::run(const std::string & uri) {
    // Create a new connection to the given URI
    websocketpp::lib::error_code ec;
    client::connection_ptr con = m_client.get_connection(uri, ec);
    if (ec) {
        m_client.get_alog().write(websocketpp::log::alevel::app,
                                  "Get Connection Error: "+ec.message());
        return;
    }

    // Grab a handle for this connection so we can talk to it in a thread
    // safe manor after the event loop starts.
    m_hdl = con->get_handle();

    // Queue the connection. No DNS queries or network connections will be
    // made until the io_service event loop is run.
    m_client.connect(con);

    // Create a thread to run the ASIO io_service event loop
    websocketpp::thread asio_thread(&client::run, &m_client);


    asio_thread.join();
}


void WebSocketConnector::on_open(websocketpp::connection_hdl hdl)
{
    m_client.get_alog().write(websocketpp::log::alevel::app,
                              "Connection opened, starting telemetry!");

    scoped_lock guard(m_lock);
    m_open = true;
}

void WebSocketConnector::on_close(websocketpp::connection_hdl hdl)
{
    m_client.get_alog().write(websocketpp::log::alevel::app,
                              "Connection closed, stopping telemetry!");

    scoped_lock guard(m_lock);
    m_done = true;
}

void WebSocketConnector::on_fail(websocketpp::connection_hdl hdl)
{
    m_client.get_alog().write(websocketpp::log::alevel::app,
                              "Connection failed, stopping telemetry!");

    scoped_lock guard(m_lock);
    m_done = true;
}