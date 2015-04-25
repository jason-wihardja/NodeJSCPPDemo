module.exports = {
    findPrime: function (number) {
        var primeNumbers = [];
        for (var i = 2; i <= number; i++) {
            var isPrime = true;
            if (number > 2) {
                for (var j = 2; j < i; j++) {
                    if (i % j == 0) {
                        isPrime = false;
                        break;
                    }
                }
            }
            if (isPrime) {
                primeNumbers.push(i);
            }
        }

        return primeNumbers;
    }
};