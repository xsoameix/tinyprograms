n = 1024
case ARGV[0]
when "-i"
  s = (2*n-1).times.map do |i| rand 1000 end.map(&:to_s).join ' '
  puts n, s
when "-o"
  s = STDIN.readlines[1].scan(/\d+/).map(&:to_i).reduce :+
  puts s
  puts s % n
end
