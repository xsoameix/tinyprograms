require 'rgl/adjacency'
require 'rgl/dot'
require 'set'
class Line

  attr_accessor :id
  attr_reader :from, :to

  def initialize(from, to)
    @from = from
    @to = to
  end

  def inspect
    "[#{@id} | #{@from} -> #{@to}]"
  end
end
class Node

  attr_accessor :done
  attr_reader :id, :to, :set, :traversed

  def initialize(id)
    @id = id
    @traversed = Set.new
    @to ||= []
    @set ||= Set.new
  end

  def add(node)
    @to << node
  end

  def <<(node)
    @set << node
    node.traversed_by self
  end

  def traversed_by?(node)
    (@traversed & node.set).size >= 1
  end

  def traversed_by(node)
    @traversed << node
  end

  def inspect
    "(#{@id} | #{@to.map &:id})"
  end

  def inspect_set
    "(#{@id} | #{@set.map &:id})"
  end
end
def read_file
  File.open 'graph' do |f|
    f.read
  end
end
def parse_file(file)
  lines = file.split /\n/
  lines.map!.with_index do |line, i|
    line = Line.new *(line.split /\s/)
    line.id = i
    line
  end
end
def parse_nodes(lines)
  nodes = (0..7).map { |x| Node.new x }
  lines.map do |line|
    nodes[line.from.to_i].add nodes[line.to.to_i]
  end
  nodes
end
def puts_graph(nodes)
  lines = nodes.map do |n|
    n.to.map { |t| [n.id, t.id] }
  end.flatten
  graph = RGL::DirectedAdjacencyGraph[*lines]
  graph.write_to_graphic_file
end

# puts "#{node.id} 完成了，#{node.id} 沒被 #{ancestor.id} 走過(#{ancestor.id} 的 set#{ancestor.set.to_a.map &:id} 與 #{node.id} 的 traversed#{node.traversed.to_a.map &:id} 無交集)，加 #{node.id} 的 set"
# puts "#{node.id} 沒被 #{ancestor.id} 走過(#{ancestor.id} 的 set#{ancestor.set.to_a.map &:id} 與 #{node.id} 的 traversed#{node.traversed.to_a.map &:id} 無交集)，加 #{node.id}"
# puts "#{node.id} 被 #{ancestor.id} 走過(#{ancestor.id} 的 set#{ancestor.set.to_a.map &:id} 與 #{node.id} 的 traversed#{node.traversed.to_a.map &:id} 有交集)，停止"

def traverse(node, ancestor)
  if not node.traversed_by? ancestor
    if node.done
      node.set.map do |n|
        ancestor << n
      end
    else
      ancestor << node
      node.to.map do |n|
        traverse n, ancestor
      end
    end
  end
end
file = read_file
lines = parse_file file
nodes = parse_nodes lines
nodes.map { |x| puts x.inspect }
#puts_graph nodes
nodes.map do |n|
  traverse n, n
  n.done = true
  puts n.inspect_set
  puts
end
