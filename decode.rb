require 'base64'
require 'json'
require 'yaml'

class Account

  class << self

    def inspect_head
      head = []
      head.push 'Bank'.ljust 17
      head.push 'Name'.ljust 6
      head.push 'Personal no'.rjust 14
      head.push 'User id'.rjust 14
      head.push 'Password'.rjust 11
      head.push 'Extra password'.rjust 14
      head.join ' '
    end
  end

  def initialize(bank, name, personal_no, user_id, password, extra_password = nil)
    @bank = bank
    @name = name == 'CreditCardClient' ? '信用卡' : '  存款'
    @personal_no = personal_no || ''
    @user_id = user_id || ''
    @password = password
    @extra_password = extra_password || ''
  end

  def inspect
    tokens = []
    tokens.push @bank.ljust 17
    tokens.push @name
    tokens.push @personal_no.rjust 14
    tokens.push @user_id.rjust 14
    tokens.push @password.rjust 11
    tokens.push @extra_password.rjust 14
    tokens.join ' '
  end
end

def file_of(path)
  "#{ENV['HOME']}/#{path}"
end

encoded = File.read file_of 'credential_encoded'
encoded = encoded.to_json
encoded = Base64.decode64 encoded
encoded = encoded.reverse
decoded = Base64.decode64 encoded
decoded = JSON.parse decoded
decoded.map! do |args|
  account = Account.new *args
  account.inspect
end
decoded.unshift Account.inspect_head
decoded = decoded.join "\n"
File.open file_of('credential'), 'w' do |f|
  f.write decoded
end
