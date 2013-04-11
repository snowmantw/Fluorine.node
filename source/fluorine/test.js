var fluorine = require(__dirname+'/fluorine')

console.log("# Print out Process function")
console.dir(fluorine.Process)
console.log("# Print out applied Process")
console.dir(fluorine.Process())
console.log("# Callback as next step of Process instance")
var process = fluorine.Process().next(function(a){ console.log(a) }).next(function(a){ console.log(a) })
console.log(process)
console.log("# Execute one step in the Process instance, with a parameter. The next line will be \"Hello\"")
process.run("Hello")
console.log("# Execute one step of the process with a result from previous step. The next line will be \"World\"")
process.run("World")
