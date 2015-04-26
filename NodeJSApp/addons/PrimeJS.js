function calculatePrime(number) {
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
}

module.exports = {
    findPrime: function (number) {
        return calculatePrime(number);
    },
    
    findPrimeAsync: function (number, callback) {
        process.nextTick(function () {
            callback(calculatePrime(number));
        });
    }
};