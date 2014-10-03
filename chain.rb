require 'active_support/all'
class Origin

  def la
    puts 1
  end
end
Origin.new.la
puts
class Origin

  def la_with_la2
    if not @called
      puts 2
      la_without_la2
    end
  end
  alias_method_chain :la, :la2
end
Origin.new.la
puts
class Origin

  def la_with_la2
    puts 3
    la_without_la2
  end
  alias_method_chain :la, :la2
end
Origin.new.la
