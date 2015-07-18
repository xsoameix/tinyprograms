def words_of_page(p)
  i = p.at('.list-dic-index>dt>span').text.to_i; i/50+(i%50?1:0)
end
def keys_in_page(p) p./('dt.title.search-ttl-a').map(&:text) end
def build_link(l,i)
  a = l.scan(/[^\/]+/); a[-2] = "p#{i+1}u"; a[0]+"//"+a[1..-1].join('/')
end
def keys_of_links(ls, i, s)
  sum = 0
  ls[i..-1].each do |t, l|
    sleep(20); p = s.get l
    next if p.text_contains('検索結果は見つかりませんでした。').present?
    w = words_of_page p
    sum += w
    next
    ks = w.times.map do |i|
      c = build_link l, i; sleep(20); b = s.get c; keys_in_page b
    end.flatten.map{|x|[x.strip,true]}.to_h.keys
    File.open("datrie.c.in.5.#{i}.#{t}", 'w'){|f| ks.each {|k| f.puts k}}
  end
  puts sum
end
def all_keys(s, i = 0)
  s.user_agent = 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1627.0 Safari/537.36'
  p = s.get 'http://dictionary.goo.ne.jp/dicindex/thsrs/%E3%81%82/u/%E3%81%82/'
  r = (p.text_contains '五十音から探す')[0]
  ls = r.parent.parent./('.list-word>li>a').map do |x|
    [x.text, "http://dictionary.goo.ne.jp#{x.attr('href')}"]
  end
  keys_of_links ls, i, s; nil
end
