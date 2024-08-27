#ifndef RADIX_TREE_H
#define RADIX_TREE_H

typedef struct RadixNode {
    int tokenID;
    struct {
        const char *prefix;
        struct RadixNode *node;
    } children[46];  // Adjusted based on the max children needed
} RadixNode;

// Node Definitions
RadixNode root_child0_child0_child0_child0 = {.tokenID = 8, .children = {}};
RadixNode root_child0_child0_child0_child1 = {.tokenID = 9, .children = {}};
RadixNode root_child0_child0_child0 = {.tokenID = -1, .children = {
    {"e", &root_child0_child0_child0_child0},
    {"ning", &root_child0_child0_child0_child1},
}};
RadixNode root_child0_child0_child1 = {.tokenID = 10, .children = {}};
RadixNode root_child0_child0 = {.tokenID = -1, .children = {
    {"r", &root_child0_child0_child0},
    {"ve", &root_child0_child0_child1},
}};
RadixNode root_child0_child1 = {.tokenID = 11, .children = {}};
RadixNode root_child0_child2_child0 = {.tokenID = 13, .children = {}};
RadixNode root_child0_child2 = {.tokenID = 12, .children = {
    {"_", &root_child0_child2_child0},
}};
RadixNode root_child0 = {.tokenID = -1, .children = {
    {"o", &root_child0_child0},
    {"ust_", &root_child0_child1},
    {"y", &root_child0_child2},
}};
RadixNode root_child1_child0_child0 = {.tokenID = 15, .children = {}};
RadixNode root_child1_child0 = {.tokenID = 14, .children = {
    {"s", &root_child1_child0_child0},
}};
RadixNode root_child1_child1_child0 = {.tokenID = 16, .children = {}};
RadixNode root_child1_child1_child1 = {.tokenID = 17, .children = {}};
RadixNode root_child1_child1 = {.tokenID = -1, .children = {
    {"ght", &root_child1_child1_child0},
    {"nth_", &root_child1_child1_child1},
}};
RadixNode root_child1_child2_child0 = {.tokenID = 19, .children = {}};
RadixNode root_child1_child2_child1 = {.tokenID = 20, .children = {}};
RadixNode root_child1_child2_child2_child0 = {.tokenID = 21, .children = {}};
RadixNode root_child1_child2_child2_child1 = {.tokenID = 22, .children = {}};
RadixNode root_child1_child2_child2 = {.tokenID = -1, .children = {
    {"_", &root_child1_child2_child2_child0},
    {"hing", &root_child1_child2_child2_child1},
}};
RadixNode root_child1_child2_child3 = {.tokenID = 23, .children = {}};
RadixNode root_child1_child2 = {.tokenID = 18, .children = {
    {"body", &root_child1_child2_child0},
    {"rte", &root_child1_child2_child1},
    {"t", &root_child1_child2_child2},
    {"w_", &root_child1_child2_child3},
}};
RadixNode root_child1 = {.tokenID = -1, .children = {
    {"ew", &root_child1_child0},
    {"i", &root_child1_child1},
    {"o", &root_child1_child2},
}};
RadixNode root_child2_child0_child0 = {.tokenID = 25, .children = {}};
RadixNode root_child2_child0 = {.tokenID = 24, .children = {
    {"ten", &root_child2_child0_child0},
}};
RadixNode root_child2_child1_child0 = {.tokenID = 27, .children = {}};
RadixNode root_child2_child1 = {.tokenID = 26, .children = {
    {"e", &root_child2_child1_child0},
}};
RadixNode root_child2_child2 = {.tokenID = 28, .children = {}};
RadixNode root_child2 = {.tokenID = -1, .children = {
    {"f", &root_child2_child0},
    {"n", &root_child2_child1},
    {"r", &root_child2_child2},
}};
RadixNode root_child3_child0_child0_child0 = {.tokenID = 30, .children = {}};
RadixNode root_child3_child0_child0 = {.tokenID = 29, .children = {
    {"s", &root_child3_child0_child0_child0},
}};
RadixNode root_child3_child0_child1_child0 = {.tokenID = 32, .children = {}};
RadixNode root_child3_child0_child1_child1 = {.tokenID = 33, .children = {}};
RadixNode root_child3_child0_child1 = {.tokenID = 31, .children = {
    {"ically", &root_child3_child0_child1_child0},
    {"s", &root_child3_child0_child1_child1},
}};
RadixNode root_child3_child0 = {.tokenID = -1, .children = {
    {"m", &root_child3_child0_child0},
    {"t", &root_child3_child0_child1},
}};
RadixNode root_child3_child1_child0_child0 = {.tokenID = 35, .children = {}};
RadixNode root_child3_child1_child0_child1_child0 = {.tokenID = 37, .children = {}};
RadixNode root_child3_child1_child0_child1_child1 = {.tokenID = 38, .children = {}};
RadixNode root_child3_child1_child0_child1 = {.tokenID = 36, .children = {
    {"gave", &root_child3_child1_child0_child1_child0},
    {"in", &root_child3_child1_child0_child1_child1},
}};
RadixNode root_child3_child1_child0 = {.tokenID = 34, .children = {
    {"d", &root_child3_child1_child0_child0},
    {"s", &root_child3_child1_child0_child1},
}};
RadixNode root_child3_child1_child1 = {.tokenID = 39, .children = {}};
RadixNode root_child3_child1 = {.tokenID = -1, .children = {
    {"e", &root_child3_child1_child0},
    {"ng", &root_child3_child1_child1},
}};
RadixNode root_child3_child2 = {.tokenID = 40, .children = {}};
RadixNode root_child3_child3 = {.tokenID = 41, .children = {}};
RadixNode root_child3_child4 = {.tokenID = 42, .children = {}};
RadixNode root_child3_child5_child0 = {.tokenID = 44, .children = {}};
RadixNode root_child3_child5_child1 = {.tokenID = 45, .children = {}};
RadixNode root_child3_child5_child2 = {.tokenID = 46, .children = {}};
RadixNode root_child3_child5_child3_child0 = {.tokenID = 47, .children = {}};
RadixNode root_child3_child5_child3_child1 = {.tokenID = 48, .children = {}};
RadixNode root_child3_child5_child3_child2 = {.tokenID = 49, .children = {}};
RadixNode root_child3_child5_child3 = {.tokenID = -1, .children = {
    {"ng", &root_child3_child5_child3_child0},
    {"sh", &root_child3_child5_child3_child1},
    {"t", &root_child3_child5_child3_child2},
}};
RadixNode root_child3_child5 = {.tokenID = 43, .children = {
    {"cant", &root_child3_child5_child0},
    {"for", &root_child3_child5_child1},
    {"his", &root_child3_child5_child2},
    {"i", &root_child3_child5_child3},
}};
RadixNode root_child3 = {.tokenID = -1, .children = {
    {"his", &root_child3_child0},
    {"i", &root_child3_child1},
    {"le", &root_child3_child2},
    {"s", &root_child3_child3},
    {"u", &root_child3_child4},
    {"y", &root_child3_child5},
}};
RadixNode root_child4 = {.tokenID = 51, .children = {}};
RadixNode root_child5 = {.tokenID = 52, .children = {}};
RadixNode root_child6 = {.tokenID = 53, .children = {}};
RadixNode root_child7 = {.tokenID = 54, .children = {}};
RadixNode root_child8 = {.tokenID = 55, .children = {}};
RadixNode root_child9 = {.tokenID = 56, .children = {}};
RadixNode root_child10 = {.tokenID = 57, .children = {}};
RadixNode root_child11 = {.tokenID = 58, .children = {}};
RadixNode root_child12 = {.tokenID = 59, .children = {}};
RadixNode root_child13 = {.tokenID = 60, .children = {}};
RadixNode root_child14 = {.tokenID = 61, .children = {}};
RadixNode root_child15 = {.tokenID = 62, .children = {}};
RadixNode root_child16 = {.tokenID = 63, .children = {}};
RadixNode root_child17 = {.tokenID = 64, .children = {}};
RadixNode root_child18_child0 = {.tokenID = 50, .children = {}};
RadixNode root_child18 = {.tokenID = 65, .children = {
    {" ", &root_child18_child0},
}};
RadixNode root_child19 = {.tokenID = 66, .children = {}};
RadixNode root_child20 = {.tokenID = 67, .children = {}};
RadixNode root_child21 = {.tokenID = 68, .children = {}};
RadixNode root_child22 = {.tokenID = 69, .children = {}};
RadixNode root_child23 = {.tokenID = 70, .children = {}};
RadixNode root_child24 = {.tokenID = 71, .children = {}};
RadixNode root_child25 = {.tokenID = 72, .children = {}};
RadixNode root_child26 = {.tokenID = 73, .children = {}};
RadixNode root_child27 = {.tokenID = 74, .children = {}};
RadixNode root_child28 = {.tokenID = 75, .children = {}};
RadixNode root_child29 = {.tokenID = 76, .children = {}};
RadixNode root_child30 = {.tokenID = 77, .children = {}};
RadixNode root_child31 = {.tokenID = 78, .children = {}};
RadixNode root_child32 = {.tokenID = 79, .children = {}};
RadixNode root_child33 = {.tokenID = 80, .children = {}};
RadixNode root_child34 = {.tokenID = 81, .children = {}};
RadixNode root_child35 = {.tokenID = 82, .children = {}};
RadixNode root_child36_child0_child0_child0 = {.tokenID = 0, .children = {}};
RadixNode root_child36_child0_child0_child1 = {.tokenID = 1, .children = {}};
RadixNode root_child36_child0_child0_child2 = {.tokenID = 2, .children = {}};
RadixNode root_child36_child0_child0 = {.tokenID = 3, .children = {
    {"1", &root_child36_child0_child0_child0},
    {"3", &root_child36_child0_child0_child1},
    {"8", &root_child36_child0_child0_child2},
}};
RadixNode root_child36_child0_child1_child0 = {.tokenID = 4, .children = {}};
RadixNode root_child36_child0_child1_child1 = {.tokenID = 5, .children = {}};
RadixNode root_child36_child0_child1_child2 = {.tokenID = 6, .children = {}};
RadixNode root_child36_child0_child1 = {.tokenID = 7, .children = {
    {"1", &root_child36_child0_child1_child0},
    {"3", &root_child36_child0_child1_child1},
    {"5", &root_child36_child0_child1_child2},
}};
RadixNode root_child36_child0 = {.tokenID = -1, .children = {
    {"1", &root_child36_child0_child0},
    {"2", &root_child36_child0_child1},
}};
RadixNode root_child36 = {.tokenID = 83, .children = {
    {"0", &root_child36_child0},
}};
RadixNode root_child37 = {.tokenID = 84, .children = {}};
RadixNode root_child38 = {.tokenID = 85, .children = {}};
RadixNode root_child39 = {.tokenID = 86, .children = {}};
RadixNode root_child40 = {.tokenID = 87, .children = {}};
RadixNode root_child41 = {.tokenID = 88, .children = {}};
RadixNode root_child42 = {.tokenID = 89, .children = {}};
RadixNode root_child43 = {.tokenID = 90, .children = {}};
RadixNode root_child44 = {.tokenID = 91, .children = {}};
RadixNode root_child45 = {.tokenID = 92, .children = {}};
RadixNode root = {.tokenID = -1, .children = {
    {"m", &root_child0},
    {"n", &root_child1},
    {"o", &root_child2},
    {"budd", &root_child3},
    {".", &root_child4},
    {",", &root_child5},
    {";", &root_child6},
    {":", &root_child7},
    {"\'", &root_child8},
    {"\"", &root_child9},
    {"!", &root_child10},
    {"?", &root_child11},
    {"(", &root_child12},
    {")", &root_child13},
    {"[", &root_child14},
    {"]", &root_child15},
    {"{", &root_child16},
    {"}", &root_child17},
    {"<", &root_child18},
    {">", &root_child19},
    {"/", &root_child20},
    {"\\", &root_child21},
    {"|", &root_child22},
    {"-", &root_child23},
    {"_", &root_child24},
    {"+", &root_child25},
    {"=", &root_child26},
    {"*", &root_child27},
    {"&", &root_child28},
    {"^", &root_child29},
    {"%", &root_child30},
    {"$", &root_child31},
    {"#", &root_child32},
    {"@", &root_child33},
    {"~", &root_child34},
    {"`", &root_child35},
    {"0", &root_child36},
    {"1", &root_child37},
    {"2", &root_child38},
    {"3", &root_child39},
    {"4", &root_child40},
    {"5", &root_child41},
    {"6", &root_child42},
    {"7", &root_child43},
    {"8", &root_child44},
    {"9", &root_child45},
}};

#endif // RADIX_TREE_H
