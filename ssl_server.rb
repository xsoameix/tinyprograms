require 'socket'
require 'openssl'

class TCBServer

  def initialize(port)
    @tcp_server = TCPServer.new find_host, port
    ctx = OpenSSL::SSL::SSLContext.new :TLSv1
    ctx.cert = OpenSSL::X509::Certificate.new File.read 'cert.crt'
    ctx.key = OpenSSL::PKey::RSA.new File.read 'priv.key'
    @ssl_server = OpenSSL::SSL::SSLServer.new @tcp_server, ctx
    puts "Listening on port #{port}"
  end

  def find_host
    host = Socket.ip_address_list.find do |ip|
      ip.ipv4? && !ip.ipv4_loopback?
    end
    host.ip_address
  end

  def run
    conn = @ssl_server.accept
    data = conn.gets
    puts "Retrieved Data {#{data}}"
    conn.puts "Data Retrieved {#{data}}"
    conn.close
  end
end

server = TCBServer.new 2000
server.run
