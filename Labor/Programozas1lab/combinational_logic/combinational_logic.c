#include <stdlib.h>

typedef enum
{
    AND,
    OR,
    NAND,
    NOR,
    NOT,
    FALSE,
    TRUE
} type_t;

typedef struct g
{
    type_t type;
    struct g *in1, *in2;
} gate_t, *gate_tree;

int eval(gate_tree root)
{
    switch (root->type)
    {
    case AND:
        return eval(root->in1) && eval(root->in2);

    case OR:
        return eval(root->in1) || eval(root->in2);

    case NAND:
        return !(eval(root->in1) && eval(root->in2));

    case NOR:
        return !(eval(root->in1) || eval(root->in2));

    case NOT:
        return !eval(root->in1);

    case FALSE:
        return 0;

    case TRUE:
        return 1;

    default:
        return -1;
    }
}