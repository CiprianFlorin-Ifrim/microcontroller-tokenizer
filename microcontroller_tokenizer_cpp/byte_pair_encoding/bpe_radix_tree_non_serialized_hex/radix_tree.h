#ifndef RADIX_TREE_H
#define RADIX_TREE_H

typedef struct RadixNode {
    const int8_t tokenID;
    struct {
        const uint32_t prefix;  // Store 4-char prefix as uint32_t
        const struct RadixNode *node;
    } children[46];  // Adjusted based on the max children needed
} RadixNode;

const RadixNode root_child0_child0_child0_child0 = {.tokenID = 8, .children = {}};
const RadixNode root_child0_child0_child0_child1 = {.tokenID = 9, .children = {}};
const RadixNode root_child0_child0_child0 = {.tokenID = -1, .children = {
    {0x65000000, &root_child0_child0_child0_child0},  // "e"
    {0x6e696e67, &root_child0_child0_child0_child1},  // "ning"
}};
const RadixNode root_child0_child0_child1 = {.tokenID = 10, .children = {}};
const RadixNode root_child0_child0 = {.tokenID = -1, .children = {
    {0x72000000, &root_child0_child0_child0},  // "r"
    {0x76650000, &root_child0_child0_child1},  // "ve"
}};
const RadixNode root_child0_child1 = {.tokenID = 11, .children = {}};
const RadixNode root_child0_child2_child0 = {.tokenID = 13, .children = {}};
const RadixNode root_child0_child2 = {.tokenID = 12, .children = {
    {0x5f000000, &root_child0_child2_child0},  // "_"
}};
const RadixNode root_child0 = {.tokenID = -1, .children = {
    {0x6f000000, &root_child0_child0},  // "o"
    {0x7573745f, &root_child0_child1},  // "ust_"
    {0x79000000, &root_child0_child2},  // "y"
}};
const RadixNode root_child1_child0_child0 = {.tokenID = 15, .children = {}};
const RadixNode root_child1_child0 = {.tokenID = 14, .children = {
    {0x73000000, &root_child1_child0_child0},  // "s"
}};
const RadixNode root_child1_child1_child0 = {.tokenID = 16, .children = {}};
const RadixNode root_child1_child1_child1 = {.tokenID = 17, .children = {}};
const RadixNode root_child1_child1 = {.tokenID = -1, .children = {
    {0x67687400, &root_child1_child1_child0},  // "ght"
    {0x6e74685f, &root_child1_child1_child1},  // "nth_"
}};
const RadixNode root_child1_child2_child0 = {.tokenID = 19, .children = {}};
const RadixNode root_child1_child2_child1 = {.tokenID = 20, .children = {}};
const RadixNode root_child1_child2_child2_child0 = {.tokenID = 21, .children = {}};
const RadixNode root_child1_child2_child2_child1 = {.tokenID = 22, .children = {}};
const RadixNode root_child1_child2_child2 = {.tokenID = -1, .children = {
    {0x5f000000, &root_child1_child2_child2_child0},  // "_"
    {0x68696e67, &root_child1_child2_child2_child1},  // "hing"
}};
const RadixNode root_child1_child2_child3 = {.tokenID = 23, .children = {}};
const RadixNode root_child1_child2 = {.tokenID = 18, .children = {
    {0x626f6479, &root_child1_child2_child0},  // "body"
    {0x72746500, &root_child1_child2_child1},  // "rte"
    {0x74000000, &root_child1_child2_child2},  // "t"
    {0x775f0000, &root_child1_child2_child3},  // "w_"
}};
const RadixNode root_child1 = {.tokenID = -1, .children = {
    {0x65770000, &root_child1_child0},  // "ew"
    {0x69000000, &root_child1_child1},  // "i"
    {0x6f000000, &root_child1_child2},  // "o"
}};
const RadixNode root_child2_child0_child0 = {.tokenID = 25, .children = {}};
const RadixNode root_child2_child0 = {.tokenID = 24, .children = {
    {0x74656e00, &root_child2_child0_child0},  // "ten"
}};
const RadixNode root_child2_child1_child0 = {.tokenID = 27, .children = {}};
const RadixNode root_child2_child1 = {.tokenID = 26, .children = {
    {0x65000000, &root_child2_child1_child0},  // "e"
}};
const RadixNode root_child2_child2 = {.tokenID = 28, .children = {}};
const RadixNode root_child2 = {.tokenID = -1, .children = {
    {0x66000000, &root_child2_child0},  // "f"
    {0x6e000000, &root_child2_child1},  // "n"
    {0x72000000, &root_child2_child2},  // "r"
}};
const RadixNode root_child3_child0_child0_child0 = {.tokenID = 30, .children = {}};
const RadixNode root_child3_child0_child0 = {.tokenID = 29, .children = {
    {0x73000000, &root_child3_child0_child0_child0},  // "s"
}};
const RadixNode root_child3_child0_child1_child0 = {.tokenID = 32, .children = {}};
const RadixNode root_child3_child0_child1_child1 = {.tokenID = 33, .children = {}};
const RadixNode root_child3_child0_child1 = {.tokenID = 31, .children = {
    {0x6963616c, &root_child3_child0_child1_child0},  // "ically"
    {0x73000000, &root_child3_child0_child1_child1},  // "s"
}};
const RadixNode root_child3_child0 = {.tokenID = -1, .children = {
    {0x6d000000, &root_child3_child0_child0},  // "m"
    {0x74000000, &root_child3_child0_child1},  // "t"
}};
const RadixNode root_child3_child1_child0_child0 = {.tokenID = 35, .children = {}};
const RadixNode root_child3_child1_child0_child1_child0 = {.tokenID = 37, .children = {}};
const RadixNode root_child3_child1_child0_child1_child1 = {.tokenID = 38, .children = {}};
const RadixNode root_child3_child1_child0_child1 = {.tokenID = 36, .children = {
    {0x67617665, &root_child3_child1_child0_child1_child0},  // "gave"
    {0x696e0000, &root_child3_child1_child0_child1_child1},  // "in"
}};
const RadixNode root_child3_child1_child0 = {.tokenID = 34, .children = {
    {0x64000000, &root_child3_child1_child0_child0},  // "d"
    {0x73000000, &root_child3_child1_child0_child1},  // "s"
}};
const RadixNode root_child3_child1_child1 = {.tokenID = 39, .children = {}};
const RadixNode root_child3_child1 = {.tokenID = -1, .children = {
    {0x65000000, &root_child3_child1_child0},  // "e"
    {0x6e670000, &root_child3_child1_child1},  // "ng"
}};
const RadixNode root_child3_child2 = {.tokenID = 40, .children = {}};
const RadixNode root_child3_child3 = {.tokenID = 41, .children = {}};
const RadixNode root_child3_child4 = {.tokenID = 42, .children = {}};
const RadixNode root_child3_child5_child0 = {.tokenID = 44, .children = {}};
const RadixNode root_child3_child5_child1 = {.tokenID = 45, .children = {}};
const RadixNode root_child3_child5_child2 = {.tokenID = 46, .children = {}};
const RadixNode root_child3_child5_child3_child0 = {.tokenID = 47, .children = {}};
const RadixNode root_child3_child5_child3_child1 = {.tokenID = 48, .children = {}};
const RadixNode root_child3_child5_child3_child2 = {.tokenID = 49, .children = {}};
const RadixNode root_child3_child5_child3 = {.tokenID = -1, .children = {
    {0x6e670000, &root_child3_child5_child3_child0},  // "ng"
    {0x73680000, &root_child3_child5_child3_child1},  // "sh"
    {0x74000000, &root_child3_child5_child3_child2},  // "t"
}};
const RadixNode root_child3_child5 = {.tokenID = 43, .children = {
    {0x63616e74, &root_child3_child5_child0},  // "cant"
    {0x666f7200, &root_child3_child5_child1},  // "for"
    {0x68697300, &root_child3_child5_child2},  // "his"
    {0x69000000, &root_child3_child5_child3},  // "i"
}};
const RadixNode root_child3 = {.tokenID = -1, .children = {
    {0x68697300, &root_child3_child0},  // "his"
    {0x69000000, &root_child3_child1},  // "i"
    {0x6c650000, &root_child3_child2},  // "le"
    {0x73000000, &root_child3_child3},  // "s"
    {0x75000000, &root_child3_child4},  // "u"
    {0x79000000, &root_child3_child5},  // "y"
}};
const RadixNode root_child4 = {.tokenID = 51, .children = {}};
const RadixNode root_child5 = {.tokenID = 52, .children = {}};
const RadixNode root_child6 = {.tokenID = 53, .children = {}};
const RadixNode root_child7 = {.tokenID = 54, .children = {}};
const RadixNode root_child8 = {.tokenID = 55, .children = {}};
const RadixNode root_child9 = {.tokenID = 56, .children = {}};
const RadixNode root_child10 = {.tokenID = 57, .children = {}};
const RadixNode root_child11 = {.tokenID = 58, .children = {}};
const RadixNode root_child12 = {.tokenID = 59, .children = {}};
const RadixNode root_child13 = {.tokenID = 60, .children = {}};
const RadixNode root_child14 = {.tokenID = 61, .children = {}};
const RadixNode root_child15 = {.tokenID = 62, .children = {}};
const RadixNode root_child16 = {.tokenID = 63, .children = {}};
const RadixNode root_child17 = {.tokenID = 64, .children = {}};
const RadixNode root_child18_child0 = {.tokenID = 50, .children = {}};
const RadixNode root_child18 = {.tokenID = 65, .children = {
    {0x73706163, &root_child18_child0},  // "space>"
}};
const RadixNode root_child19 = {.tokenID = 66, .children = {}};
const RadixNode root_child20 = {.tokenID = 67, .children = {}};
const RadixNode root_child21 = {.tokenID = 68, .children = {}};
const RadixNode root_child22 = {.tokenID = 69, .children = {}};
const RadixNode root_child23 = {.tokenID = 70, .children = {}};
const RadixNode root_child24 = {.tokenID = 71, .children = {}};
const RadixNode root_child25 = {.tokenID = 72, .children = {}};
const RadixNode root_child26 = {.tokenID = 73, .children = {}};
const RadixNode root_child27 = {.tokenID = 74, .children = {}};
const RadixNode root_child28 = {.tokenID = 75, .children = {}};
const RadixNode root_child29 = {.tokenID = 76, .children = {}};
const RadixNode root_child30 = {.tokenID = 77, .children = {}};
const RadixNode root_child31 = {.tokenID = 78, .children = {}};
const RadixNode root_child32 = {.tokenID = 79, .children = {}};
const RadixNode root_child33 = {.tokenID = 80, .children = {}};
const RadixNode root_child34 = {.tokenID = 81, .children = {}};
const RadixNode root_child35 = {.tokenID = 82, .children = {}};
const RadixNode root_child36_child0_child0_child0 = {.tokenID = 0, .children = {}};
const RadixNode root_child36_child0_child0_child1 = {.tokenID = 1, .children = {}};
const RadixNode root_child36_child0_child0_child2 = {.tokenID = 2, .children = {}};
const RadixNode root_child36_child0_child0 = {.tokenID = 3, .children = {
    {0x31000000, &root_child36_child0_child0_child0},  // "1"
    {0x33000000, &root_child36_child0_child0_child1},  // "3"
    {0x38000000, &root_child36_child0_child0_child2},  // "8"
}};
const RadixNode root_child36_child0_child1_child0 = {.tokenID = 4, .children = {}};
const RadixNode root_child36_child0_child1_child1 = {.tokenID = 5, .children = {}};
const RadixNode root_child36_child0_child1_child2 = {.tokenID = 6, .children = {}};
const RadixNode root_child36_child0_child1 = {.tokenID = 7, .children = {
    {0x31000000, &root_child36_child0_child1_child0},  // "1"
    {0x33000000, &root_child36_child0_child1_child1},  // "3"
    {0x35000000, &root_child36_child0_child1_child2},  // "5"
}};
const RadixNode root_child36_child0 = {.tokenID = -1, .children = {
    {0x31000000, &root_child36_child0_child0},  // "1"
    {0x32000000, &root_child36_child0_child1},  // "2"
}};
const RadixNode root_child36 = {.tokenID = 83, .children = {
    {0x30000000, &root_child36_child0},  // "0"
}};
const RadixNode root_child37 = {.tokenID = 84, .children = {}};
const RadixNode root_child38 = {.tokenID = 85, .children = {}};
const RadixNode root_child39 = {.tokenID = 86, .children = {}};
const RadixNode root_child40 = {.tokenID = 87, .children = {}};
const RadixNode root_child41 = {.tokenID = 88, .children = {}};
const RadixNode root_child42 = {.tokenID = 89, .children = {}};
const RadixNode root_child43 = {.tokenID = 90, .children = {}};
const RadixNode root_child44 = {.tokenID = 91, .children = {}};
const RadixNode root_child45 = {.tokenID = 92, .children = {}};
const RadixNode root = {.tokenID = -1, .children = {
    {0x6d000000, &root_child0},  // "m"
    {0x6e000000, &root_child1},  // "n"
    {0x6f000000, &root_child2},  // "o"
    {0x62756464, &root_child3},  // "budd"
    {0x2e000000, &root_child4},  // "."
    {0x2c000000, &root_child5},  // ","
    {0x3b000000, &root_child6},  // ";"
    {0x3a000000, &root_child7},  // ":"
    {0x27000000, &root_child8},  // "'"
    {0x22000000, &root_child9},  // """
    {0x21000000, &root_child10},  // "!"
    {0x3f000000, &root_child11},  // "?"
    {0x28000000, &root_child12},  // "("
    {0x29000000, &root_child13},  // ")"
    {0x5b000000, &root_child14},  // "["
    {0x5d000000, &root_child15},  // "]"
    {0x7b000000, &root_child16},  // "{"
    {0x7d000000, &root_child17},  // "}"
    {0x3c000000, &root_child18},  // "<"
    {0x3e000000, &root_child19},  // ">"
    {0x2f000000, &root_child20},  // "/"
    {0x5c000000, &root_child21},  // "\"
    {0x7c000000, &root_child22},  // "|"
    {0x2d000000, &root_child23},  // "-"
    {0x5f000000, &root_child24},  // "_"
    {0x2b000000, &root_child25},  // "+"
    {0x3d000000, &root_child26},  // "="
    {0x2a000000, &root_child27},  // "*"
    {0x26000000, &root_child28},  // "&"
    {0x5e000000, &root_child29},  // "^"
    {0x25000000, &root_child30},  // "%"
    {0x24000000, &root_child31},  // "$"
    {0x23000000, &root_child32},  // "#"
    {0x40000000, &root_child33},  // "@"
    {0x7e000000, &root_child34},  // "~"
    {0x60000000, &root_child35},  // "`"
    {0x30000000, &root_child36},  // "0"
    {0x31000000, &root_child37},  // "1"
    {0x32000000, &root_child38},  // "2"
    {0x33000000, &root_child39},  // "3"
    {0x34000000, &root_child40},  // "4"
    {0x35000000, &root_child41},  // "5"
    {0x36000000, &root_child42},  // "6"
    {0x37000000, &root_child43},  // "7"
    {0x38000000, &root_child44},  // "8"
    {0x39000000, &root_child45},  // "9"
}};

#endif // RADIX_TREE_H
