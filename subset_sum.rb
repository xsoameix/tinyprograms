require 'active_support/all'
def positive_sum_of(set)
  set.select { |x| x > 0 }.sum
end
def negative_sum_of(set)
  set.select { |x| x < 0 }.sum
end
def subsum?(set, i = set.size - 1, sum)
  positive_sum = positive_sum_of set
  negative_sum = negative_sum_of set
  case
  when (sum < negative_sum or
        sum > positive_sum)
    false
  when i == 0
    set[i] == sum
  else
    (set[i] == sum or
     subsum?(set, i - 1, sum) or
     subsum?(set, i - 1, sum - set[i])
  end
end

a = [-12,-5,-3,-2,1,3,5]
puts subsum? a, -14
