#include <iostream>
#include <boost/asio.hpp>

int main()
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);

        // Connections
        socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345));

        std::array<char, 128> buffer;

        // Reading message
        std::size_t length = socket.read_some(boost::asio::buffer(buffer));
        std::cout << "Message: " << std::string(buffer.data(), length) << std::endl;

        // Closes data transfer
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

        socket.close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    system("pause");
    return 0;
}