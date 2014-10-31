4.times do
  ary = 10.times.map do
    Random.rand 10
  end
  ary.uniq!
  puts "#{ary.size} #{Random.rand 20}"
  str = ary.map do |y|
    "#{Random.rand 10} #{y}"
  end.join "\n"
  puts str
end
