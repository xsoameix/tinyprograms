require 'matrix'

len = 2 + Random.rand(9)
mat = len.times.map { len.times.map { 0 }}
len.times do |row|
  (row...len).each do |col|
    conn = Random.rand 2
    mat[row][col] = conn
    mat[col][row] = conn
  end
end
puts "#{len} #{Random.rand 10} #{Random.rand 10}"
len.times do |row|
  len.times do |col|
    print mat[row][col]
    if col != len - 1
      print ' '
    end
  end
  puts ''
end
