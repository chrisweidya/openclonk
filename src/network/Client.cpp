#include <iostream>
#include <Client.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

Client::Client() {
}
bool Client::Execute() {
	try
	{
		boost::asio::io_service aios;

		boost::asio::ip::tcp::resolver resolver(aios);
		boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
			boost::asio::ip::tcp::resolver::query("openclonkplus.comp.nus.edu.sg", "80"));
		/*
		boost::asio::ip::tcp::socket socket(aios);
		boost::system::error_code error = boost::asio::error::host_not_found;
		boost::asio::ip::tcp::resolver::iterator end;
		while(error && endpoint != end)
		{
		socket.close();
		socket.connect(*endpoint++, error);
		}
		if(error)
		throw boost::system::system_error(error);
		*/
		boost::asio::ip::tcp::socket socket(aios);
		// open the connection for the specified endpoint, or throws a system_error
		boost::asio::connect(socket, endpoint);

		for (;;)
		{
			std::array<char, 4> buf;
			boost::system::error_code error;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer
			else if (error)
				throw boost::system::system_error(error);

			std::cout.write(buf.data(), len);
			std::cout << '|';
		}
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}