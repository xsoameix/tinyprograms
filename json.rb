require 'mechanize'
require 'json'
session = Mechanize.new
page = session.get 'http://127.0.0.1:3000/v0/collections/ttsinterpellation/'
json = page.body
json = json.force_encoding 'utf-8'
File.open '/home/lien/temp.json', 'w' do |f|
  f.write JSON.pretty_generate JSON.parse json
end
