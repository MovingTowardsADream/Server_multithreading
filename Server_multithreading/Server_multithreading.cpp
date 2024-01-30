#include <iostream>
#include <boost/asio.hpp>
#include <thread>

/**
 * The session function is responsible for handling each connection.
 *
 * @param socket Socket for sending messages to the client and receiving a response
 */

void session(boost::asio::ip::tcp::socket socket)
{
    try
    {
        std::string message = "kaspersky";
        boost::system::error_code ignored_error;

        // Sending a message to a user
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

        // Closes data transfer
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

        while (true)
        {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Processing a client in a thread
            std::thread session_thread(session, std::move(socket));
            session_thread.detach();
        }
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}