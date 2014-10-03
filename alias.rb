require 'active_support/all'
class Origin

  def la
    puts 1
  end
end
Origin.new.la
puts
class Origin

  def la2
    if not @called
      puts 2
      la1
    end
  end
  alias_method :la1, :la
  alias_method :la, :la2
end
Origin.new.la
puts
class Origin

  def la3
    puts 3
    la1
  end
  alias_method :la1, :la
  alias_method :la, :la3
end
Origin.new.la
