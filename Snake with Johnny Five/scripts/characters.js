S = ["10001111", "10001001", "10001001", "10001001", "10001001", "10001001", "10001001", "11111001"];
N = ["11111111", "00000010", "00000100", "00001000", "00010000", "00100000", "01000000", "11111111"];
A = ["00000000", "01111000", "00010100", "00010010", "00010010", "00010100", "01111000", "00000000"];
K = ["00000000", "11111111", "00011000", "00100100", "01000010", "10000001", "00000000", "00000000"];
E = ["00000000", "11111111", "10011001", "10011001", "10011001", "10011001", "10011001", "00000000"];
L = ["00000000", "11111111", "10000000", "10000000", "10000000", "10000000", "10000000", "00000000"];
O = ["00000000", "11111111", "10000001", "10000001", "10000001", "10000001", "11111111", "00000000"];
T = ["00000000", "00000001", "00000001", "11111111", "00000001", "00000001", "00000001", "00000000"];
N3 = ["00000000", "10011001", "10011001", "10011001", "10011001", "10011001", "11111111", "00000000"];
N2 = ["00000000", "11111001", "10001001", "10001001", "10001001", "10001001", "10001111", "00000000"];
N1 = ["00000000", "00000000", "00000100", "00000010", "11111111", "00000000", "00000000", "00000000"];
N0 = ["00000000", "01111110", "10000001", "10000001", "10000001", "10000001", "01111110", "00000000"];
Empty = ["00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000"];

module.exports = {
    getLetterS: function () {
        return S;
    },
    getLetterN: function () {
        return N;
    },
    getLetterA: function () {
        return A;
    },
    getLetterK: function () {
        return K;
    },
    getLetterE: function () {
        return E;
    },
    getLetterL: function () {
        return L;
    },
    getLetterO: function () {
        return O;
    },
    getLetterT: function () {
        return T;
    },
    getLetterN3: function () {
        return N3;
    },
    getLetterN2: function () {
        return N2;
    },
    getLetterN1: function () {
        return N1;
    },
    getLetterN0: function () {
        return N0;
    },
    getLetterEmpty: function () {
        return Empty;
    },
}