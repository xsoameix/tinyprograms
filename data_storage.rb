class Node

  attr_reader :left, :right

  def initialize(left, right)
    @left = left
    @right = right
  end

  def +(node)
    Node.new(self.left + node.left,
             self.right + node.right)
  end

  def left_path
    "%2d" % @left
  end

  def right_path
    "%2d" % @right
  end
end

def bfs(left, parent, right, i, ary)
  if i >= 2**65535
    return
  end
  left_child = left + parent
  right_child = right + parent
  ary[i * 2 + 1] = left_child
  ary[i * 2 + 2] = right_child
  bfs(left, left_child, parent, i * 2 + 1, ary)
  bfs(parent, right_child, right, i * 2 + 2, ary)
end
left = Node.new 0, 1
parent = Node.new 1, 1
right = Node.new 1, 0
ary = []
bfs(left, parent, right, 0, ary)
level = 1
sum = 2 ** level
aary = ary[1..-1].select do |node|
  !node.nil? &&
  node.left == node.right
end
aary.map do |node|
  puts "#{node.left_path} #{left_path}"
end
#ary[1..-1].each_slice(1).with_index do |slice, i|
#  key = slice.map(&:left_path).join ' '
#  value = slice.map(&:right_path).join ' '
#  puts "#{key} #{value}"
#  if i == sum - 1
#    puts ""
#    level += 1
#    sum += 2 ** level
#  end
#end
