300000.times do
  n = 5
  q = 4
  puts "#{n} #{q}"
  n.times do
    print "#{rand 10} "
  end
  puts
  q.times do |i|
    puts i + 1
  end
end
puts "0 0"
