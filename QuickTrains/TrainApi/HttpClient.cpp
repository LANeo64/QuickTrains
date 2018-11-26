#include "stdafx.h"
#include "HttpClient.h"


HttpClient::HttpClient()
{
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

bool HttpClient::Connect(ConnectionMode mode)
{
	m_mode = mode;
	try {
		tcp::resolver resolver(m_io_context);
		tcp::resolver::results_type endpoints = resolver.resolve(m_host, "http");
		m_socket = tcp::socket(m_io_context);
		boost::asio::connect(m_socket, endpoints);
	}
	catch (std::exception& e)
	{
		m_lastError = e.what();
		return false;
	}
	return true;
}

std::string HttpClient::GetData(Request Q)
{
	std::ostringstream data;

	try {
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
		request_stream << " HTTP/1.0\r\n";
		request_stream << "Host: " << m_host << m_subURI << "\r\n";
		request_stream << "Accept: */*\r\n";
		switch (m_mode) {
		case SINGLE:request_stream << "Connection: close\r\n"; break;
		case BURST:request_stream << "Connection: Keep-Alive\r\n"; break;
		default:
			throw std::invalid_argument("Invalid data stream connection type");
			break;
		}
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
			//std::cout << "Response returned with status code " << status_code << "\n";
			throw std::runtime_error(Utils::Concat("Invalid response from server: ", status_code).c_str());
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			data << header << "\n";
		data << "\n";

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

bool HttpClient::CheckAddress(IpAddr address)
{
	if (
		(address.A < 256) &&
		(address.B < 256) &&
		(address.C < 256) &&
		(address.D < 256) &&
		(address.A > 0)
		) {
		bool good = true;
		switch (address.A) {
		case 10:
			if ((address.B == 0) && (address.C == 0) && (address.D == 0)) {
				good = false;
			}
			break;
		case 127:
			if ((address.B == 0) && (address.C == 0) && (address.D == 0)) {
				good = false;
			}
			break;
		case 192:
			if ((address.B != 168) || ((address.C == 0) && (address.D == 0))) {
				good = false;
			}
			break;
		}

		return good;
	}
	else {
		return false;
	}
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

HttpClient::IpAddr HttpClient::GatherAddress(std::string address)
{
	HttpClient::IpAddr add;
	std::vector<std::string> ip = Utils::Explode(address, '.');
	if (ip.size() == 4) {
		add.A = Utils::ToInt(ip.at(0));
		add.B = Utils::ToInt(ip.at(1));
		add.C = Utils::ToInt(ip.at(2));
		add.D = Utils::ToInt(ip.at(3));
	}
	else {
		add.A = 127;
		add.B = 0;
		add.C = 0;
		add.D = 1;
	}
	return add;
}
