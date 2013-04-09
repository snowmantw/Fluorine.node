var toy = require(__dirname+'/toy')
console.log("# Function -- Next line should be: \"H E L L O\"")
console.log(toy.foo())
console.log("# Arguments -- Next line should be: 1024")
console.log(toy.bar(768,256))
console.log("# Pass JS funcion in -- Next line should be: 1024")
console.log(toy.charlie(toy.bar))
console.log("# Object generation in C++ function -- Next line should be: \"H E L L O\"")
console.log(toy.delta("H E L ").msg+toy.delta("L O").msg)
console.log("# Function factory in C++, which generate another function to run -- Next line should be: \" H E L L O\"")
console.log(toy.eagle()())
console.log("# Function factory in C++; make sure the wrapped function, which named by another C++ function, had been registered -- Next line should be: \" H E L L O\"")
console.log(toy.eagleChild())

console.log("# Export instanceable function written in C++ -- Next line should be: 11")
var fluorine = new toy.Fluorine(10)
console.log(fluorine.plusOne())

console.log("# Export instanceable function written in C++ -- Next line should be: 12")
console.log(fluorine.plusOne())

console.log("# Export instanceable function written in C++; factory pattern -- Next line should be: 11")
var fluorine = toy.fluorineCreate(10)
console.log(fluorine.plusOne())

console.log("# Export instanceable function written in C++; factory pattern -- Next line should be: 12")
console.log(fluorine.plusOne())

console.log("# Pass wrapped C++ object -- Next line should be: 1024")
console.log(toy.galliumAdd(toy.galliumCreate(768), toy.galliumCreate(256)))
