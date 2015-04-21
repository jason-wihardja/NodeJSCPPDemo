var cluster = require('cluster');
cluster.schedulingPolicy = cluster.SCHED_RR;

if (cluster.isMaster) {
    var numberOfCPUs = require('os').cpus().length;
    
    for (var i = 0; i < numberOfCPUs; i++) {
        cluster.fork();
    }
    
    Object.keys(cluster.workers).forEach(function (id) {
        console.log("Worker is running with PID : " + cluster.workers[id].process.pid);
    });
    
    cluster.on('exit', function (worker, code, signal) {
        console.log('Worker ' + worker.process.pid + ' died');
    });
} else {
    require('./app.js');
}