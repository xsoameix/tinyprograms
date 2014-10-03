class Car

  attr_reader :max_speed, :turbo_p

  class << self

    def new_many
      puts 'Please input the number of cars: '
      size = gets
      while out_of_range? size
        puts 'Out of range!'
        puts 'Please input the number of cars: '
        size = gets
      end
      size.to_i.times.map { |i| Car.new i }
    end

    def out_of_range?(input)
      not input =~ /^[1-9]\d*$/
    end
  end

  def initialize(id)
    @id = id
    @max_speed = get_max_speed
    @turbo_p = true
  end

  def get_max_speed
    puts "Please input the max speed of this car(#{@id}): "
    speed = gets
    while too_fast? speed
      puts 'Out of range!'
      puts "Please input the max speed of this car(#{@id}): "
      speed = gets
    end
    speed.to_f
  end

  def too_fast?(input)
    not input =~ /^([1-9]\d*(\.\d+)?|0\.\d+)$/
  end

  def status
    puts "Car id is #{@id}"
    puts "Car max speed is #{@max_speed}"
    puts "Car turbo is #{@turbo_p}"
  end
end

def main
  cars = Car.new_many
  puts 'Output car status'
  cars.map &:status
end

main
