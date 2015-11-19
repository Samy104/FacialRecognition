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
    m_client.set_open_handler(bind(&WebSocketConnector::on_open,this,::_1));
    m_client.set_close_handler(bind(&WebSocketConnector::on_close,this,::_1));
    m_client.set_fail_handler(bind(&WebSocketConnector::on_fail,this,::_1));
}

WebSocketConnector::~WebSocketConnector()
{
    if(asio_thread != NULL)
    {
        delete asio_thread;
        asio_thread = NULL;
    }
}

// This method will block until the connection is complete
void WebSocketConnector::run(const std::string & uri) {
    // Create a new connection to the given URI
    client::connection_ptr con = m_client.get_connection(uri, m_ec);
    if (m_ec) {
        std::string errorMsg = "Get Connection Error: ";
        errorMsg.append(m_ec.message());
        m_client.get_alog().write(websocketpp::log::alevel::app,
                                  errorMsg );
        return;
    }

    // Grab a handle for this connection so we can talk to it in a thread
    // safe manor after the event loop starts.
    m_hdl = con->get_handle();

    // Queue the connection. No DNS queries or network connections will be
    // made until the io_service event loop is run.
    m_client.connect(con);

    // Create a thread to run the ASIO io_service event loop
    asio_thread = new websocketpp::lib::thread(&client::run, &m_client);

    asio_thread->detach();
}


void WebSocketConnector::on_open(websocketpp::connection_hdl hdl)
{
    m_client.get_alog().write(websocketpp::log::alevel::app,
                              "Connection opened, starting connection!");

    scoped_lock guard(m_lock);
    m_open = true;
}

void WebSocketConnector::on_close(websocketpp::connection_hdl hdl)
{
    m_client.get_alog().write(websocketpp::log::alevel::app,
                              "Connection closed, stopping connection!");

    scoped_lock guard(m_lock);
    m_done = true;
}

void WebSocketConnector::on_fail(websocketpp::connection_hdl hdl)
{
    m_client.get_alog().write(websocketpp::log::alevel::app,
                              "Connection failed, stopping connection!");

    scoped_lock guard(m_lock);
    m_done = true;
}

websocketpp::connection_hdl& WebSocketConnector::getNetworkHandle()
{
    return this->m_hdl;
}

websocketpp::lib::error_code& WebSocketConnector::getErrorCode()
{
    return this->m_ec;
}