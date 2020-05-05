#include <stdio.h>

#define VERTICES 2001

struct v {
    unsigned to;
    unsigned w;
};

struct v table[VERTICES][VERTICES - 1];
unsigned links[VERTICES];
unsigned visited[VERTICES];

unsigned vertices;
unsigned answer;

struct elem {
    unsigned to;
    unsigned len_to_source;
} stack_elem[VERTICES];
unsigned stack_top;
struct v tmp;

void solving(void)
{

}

int main(void)
{
    unsigned cases;
    unsigned from, to, weight;
    unsigned idx;

    scanf("%u", &cases);
    cases++;

    for (unsigned i = 1; i < cases; i++) {
        scanf("%u", &vertices);
        for (unsigned v = 1; v < vertices; v++) {
            scanf("%u %u %u", &weight, &from, &to);
//            printf("%u %u %u\n", weight, from, to);
            idx = links[from]++;
            table[from][idx].to = to;
            table[from][idx].w = weight;
            idx = links[to]++;
            table[to][idx].to = from;
            table[to][idx].w = weight;
        }
//        solving();
        printf("#%u %u\n", i, answer);
        for (unsigned y = 1; y <= vertices; y++) {
            links[y] = 0;
        }
    }

    return 0;
}
