class Origin

  def la
    puts 1
    raise RuntimeError
  end
end
#Origin.new.la
puts
module Patch1

  def la
    puts 2
    begin
      super
    rescue RuntimeError
      puts '2-detected'
    end
  end
end
class Origin

  prepend Patch1
end
Origin.new.la
puts
module Patch2

  def la
    puts 3
    super
  end
end
class Origin

  prepend Patch2
end
Origin.new.la
