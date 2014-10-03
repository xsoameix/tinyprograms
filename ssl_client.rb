require 'openssl'
require 'socket'

class TCBSocket

  def initialize(host, port)
    @tcp_socket = TCPSocket.new host, port
    cert = OpenSSL::X509::Certificate.new File.read 'cert.crt'
    @ssl_socket = OpenSSL::SSL::SSLSocket.new @tcp_socket
    @ssl_socket.sync_close = true
    @ssl_socket.connect
    if @ssl_socket.peer_cert.to_s != cert.to_s
      $stderr.puts 'Unexpected certificate !'
      exit 1
    end
  end

  def run
    data = 'hello'
    puts "Sending Data [#{data}]"
    @ssl_socket.puts data
    data = @ssl_socket.gets
    data += @ssl_socket.gets
    puts "Data Retrieved [#{data}]"
  end
end

socket = TCBSocket.new 'howrich-ruby.cloudapp.net', 2000
socket.run
