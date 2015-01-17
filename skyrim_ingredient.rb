require 'set'
require 'hi_banks'

class Ingredient

  attr_reader :name, :effects

  def initialize(name, effects)
    @name = name
    @effects = Set.new effects
  end

  def to_s
    lines = @effects.to_a.map { |x| "  #{x}\n"}
    "#{@name}\n#{lines.join}"
  end
end

class Effect

  def initialize(name)
    @name = name
    @ingredients = Set.new
  end

  def add(ingredient)
    @ingredients.add ingredient
  end

  def to_s
    header = @ingredients.map &:name
    content = ingredients_effects.map do |effect|
      cols = @ingredients.map do |ingredient|
        has = ingredient.effects.include? effect
        has ? 'o' : ' '
      end
      "#{effect.ljust 22}#{cols.join ' '}"
    end
    lines = [header, content].map { |rows| rows.join "\n" }
    lines.join "\n"
  end

  def ingredients_effects
    effects = Set.new
    @ingredients.each do |ingredient|
      ingredient.effects.each do |effect|
        effects.add effect
      end
    end
    effects
  end
end

class Effects

  extend Forwardable

  def_delegators :@effects, :[], :[]=

  def initialize
    @effects = {}
  end

  def to_s
    @effects.keys.join "\n"
  end
end

c = HiBanks::Taiwan::ANZ::CreditCardClient.new(personal_no: '', user_id: '', password: '')
# If the wiki website is done,
#   checkout the file `Ingredients (Skyrim) - The Elder Scrolls Wiki.html`
page = c.session.get 'http://elderscrolls.wikia.com/wiki/Ingredients_%28Skyrim%29'
table = page.table_contains 'Abecean Longfin'
rows = table.rows
effects_names = ['Primary Effect', 'Secondary Effect',
                 'Tertiary Effect', 'Quaternary Effect']
effects = Effects.new
ingredients = {}
rows.each do |row|
  ingredient_name = row['Ingredient']
  ingredient_effects = effects_names.map { |name| row[name] }
  ingredient = Ingredient.new ingredient_name, ingredient_effects
  ingredient_effects.each do |e|
    effects[e] ||= Effect.new e
    effects[e].add ingredient
  end
  ingredients[ingredient.name] = ingredient
end
require 'pry-nav'
binding.pry
# Then you can type:
#     puts effects
#     puts effects['Restore Health']
#     puts effects['Invisibility']
#     puts ingredients['Luna Moth Wing']
