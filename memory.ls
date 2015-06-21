!function Obj(data)
  @data = data
global = map: [] get: -> global.map.0
obj = new Obj 'hey ! i am an object.'
global.map.push obj
global.map.0 = null
obj = null
global = null
