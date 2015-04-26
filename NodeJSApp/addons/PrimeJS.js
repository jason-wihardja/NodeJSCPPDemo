module.exports = {
    calculatePrime: function (number) {
        var primeNumbers = [];
        for (var i = 2; i <= number; i++) {
            var isPrime = true;
            for (var j = 2; j < i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primeNumbers.push(i);
            }
        }
        
        return primeNumbers;
    },
    
    findPrime: function (number) {
        return this.calculatePrime(number);
    },
    
    findPrimeAsync: function (number, callback) {
        var self = this;
        process.nextTick(function () {
            callback(self.calculatePrime(number));
        });
    }
};