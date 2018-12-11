#include "stdafx.h"
#include "HttpClient.h"


HttpClient::HttpClient()
{
	m_host = "127.0.0.1";
	m_port = 80;
	m_subURI = "/";
	m_encryption = HTTP;
}

HttpClient::HttpClient(std::string host)
{
	if (CheckAddress(host) || CheckName(host)) {
		m_host = host;
	}
	else {
		m_host = "127.0.0.1";
	}
	m_port = 80;
	m_subURI = "/";
	m_encryption = HTTP;
}

HttpClient::HttpClient(std::string host, int port, Encryption enc)
{
	if (CheckAddress(host) || CheckName(host)) {
		m_host = host;
	}
	else {
		m_host = "127.0.0.1";
	}
	
	if ((port > 0) && ((port != 80)||(port != 443))) {
		m_port = port;
		m_encryption = enc;
	}

	if((port == 80)&&(enc == HTTP)) {
		m_port = port;
		m_encryption = enc;
	}

	if ((port == 443) && (enc == HTTPS)) {
		m_port = port;
		m_encryption = enc;
	}

	if (((port == 443) && (enc == HTTP))||((port == 80) && (enc == HTTPS))) {
		m_port = port;
		m_encryption = AUTO;
	}
	m_subURI = "/";
}

HttpClient::HttpClient(std::string host, int port, std::string subURI, Encryption enc)
{
	if (CheckAddress(host) || CheckName(host)) {
		m_host = host;
	}
	else {
		m_host = "127.0.0.1";
	}

	if ((port > 0) && ((port != 80) || (port != 443))) {
		m_port = port;
		m_encryption = enc;
	}

	if ((port == 80) && (enc == HTTP)) {
		m_port = port;
		m_encryption = enc;
	}

	if ((port == 443) && (enc == HTTPS)) {
		m_port = port;
		m_encryption = enc;
	}

	if (((port == 443) && (enc == HTTP)) || ((port == 80) && (enc == HTTPS))) {
		m_port = port;
		m_encryption = AUTO;
	}

	if (CheckSubURI(subURI)) {
		m_subURI = subURI;
	}
	else {
		m_subURI = "/";
	}
}

HttpClient::~HttpClient()
{
}

bool HttpClient::SetHost(std::string host)
{
	if (CheckAddress(host) || CheckName(host)) {
		m_host = host;
		return true;
	}
	else {
		return false;
	}
}

bool HttpClient::SetPort(int port)
{
	if (port > 0) {
		m_port = port;
		return true;
	}
	else {
		return false;
	}
}

bool HttpClient::SetSubURI(std::string uri)
{
	if (CheckSubURI(uri)) {
		m_subURI = uri;
		return true;
	}
	else {
		return false;
	}
}

std::string HttpClient::GetData(Request Q, ConnectionMode mode)
{
	std::ostringstream data;

	try {
		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints = resolver.resolve(m_host, "http");
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << m_subURI;
		switch (Q.com) {
		case BLOKY: request_stream << "/bloky"; break;
		case BLOKSTAV: request_stream << "/blokstav/" << Q.id; break;
		case LOKS: request_stream << "/loks"; break;
		case LOKSTAV: request_stream << "/lokstav/" << Q.id; break;
		default: 
			throw std::invalid_argument("Invalid Command type");
			break;
		}
		request_stream << "/index.php HTTP/1.0\r\n";
		request_stream << "Host: " << m_host << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n";
		request_stream << "\r\n";
		
		boost::asio::write(socket, request);
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			//std::cout << "Invalid response\n";
			throw std::runtime_error("Invalid response from server");
		}
		if (status_code != 200)
		{
			std::ostringstream os;
			os << "Http version: " << http_version << "\n";
			os << "return code: " << status_code << "\n";
			os << "status message: " << status_message << "\n";
			//std::cout << "Response:\n\n" <<  os.str() << "\n";
			throw std::runtime_error(Utils::Concat("Invalid response from server: ", os.str()).c_str());
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r") {
			//std::cout << header << "\n";
		}
		//std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
			data << &response;

		// Read until EOF, writing data to output as we go.
		boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
			data << &response;
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);
	}
	catch (std::exception& e)
	{
		//std::cout << "Exception: " << e.what() << "\n";
		throw std::runtime_error(Utils::Concat("Invalid response from server: ", e.what()).c_str());
	}

	return data.str();
}

bool HttpClient::SetData(Request Q, std::string json, ConnectionMode mode)
{
	try {
		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints = resolver.resolve(m_host, "http");
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "POST " << m_subURI;
		switch (Q.com) {
		case BLOKY: request_stream << "/bloky"; break;
		case BLOKSTAV: request_stream << "/blokstav/" << Q.id; break;
		case LOKS: request_stream << "/loks"; break;
		case LOKSTAV: request_stream << "/lokstav/" << Q.id; break;
		default:
			throw std::invalid_argument("Invalid Command type");
			break;
		}
		request_stream << "/index.php HTTP/1.0\r\n";
		request_stream << "Host: " << m_host << "\r\n";
		request_stream << "User-Agent: C/1.0\r\n";
		request_stream << "Content-Type: application/json; charset=utf-8 \r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Content-Length: " << json.length() << "\r\n";
		request_stream << "Connection: close\r\n";
		request_stream << "\r\n";
		request_stream << json;

		boost::asio::write(socket, request);
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			//std::cout << "Invalid response\n";
			throw std::runtime_error("Invalid response from server");
		}
		if (status_code != 200)
		{
			std::ostringstream os;
			os << "Http version: " << http_version << "\n";
			os << "return code: " << status_code << "\n";
			os << "status message: " << status_message << "\n";
			//std::cout << "Response:\n\n" <<  os.str() << "\n";
			throw std::runtime_error(Utils::Concat("Invalid response from server: ", os.str()).c_str());
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r") {
			//std::cout << header << "\n";
		}
		//std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
			data << &response;

		// Read until EOF, writing data to output as we go.
		boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
			data << &response;
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);
	}
	catch (std::exception& e)
	{
		//std::cout << "Exception: " << e.what() << "\n";
		throw std::runtime_error(Utils::Concat("Invalid response from server: ", e.what()).c_str());
	}

	return false;
}

int HttpClient::Test()
{
	try
	{
		boost::asio::io_context io_context;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints = resolver.resolve(m_host, "http");

		// Try each endpoint until we successfully establish a connection.
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << m_subURI << "/blokstav/127/index.php" << " HTTP/1.0\r\n";
		request_stream << "Host: " << m_host << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return 1;
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code " << status_code << "\n";
			//return 1;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
			std::cout << &response;

		// Read until EOF, writing data to output as we go.
		boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
			std::cout << &response;
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}

int HttpClient::Test2() {
	

	return 0;
}

bool HttpClient::CheckAddress(std::string address) {
	std::regex ip4pattern("^([1-9]{1}[0-9]{0,2}\.){3}[1-9]{1}[0-9]{0,2}$");
	if (std::regex_match(address, ip4pattern)) {
		return true;
	}
	else {
		return false;
	}
}

bool HttpClient::CheckName(std::string server)
{
	//std::regex URLpattern("^(https?:\/\/)?([a-zA-Z0-9]*\.)+([a-zA-Z0-9]*)(\/[a-zA-Z0-9]*)*\/?$");		// this is whole URL with everything
	std::regex URLpattern("^(https?:\/\/)?([a-zA-Z0-9]*\.)+([a-zA-Z0-9]*)$");							// this is only host
	if (std::regex_match(server, URLpattern)) {
		return true;
	}
	else {
		return false;
	}
}

bool HttpClient::CheckSubURI(std::string uri)
{
	std::regex URLpattern("^(\/[a-zA-Z0-9~_#-]*)+\/?$");
	if (std::regex_match(uri, URLpattern)) {
		return true;
	}
	else {
		return false;
	}
}
