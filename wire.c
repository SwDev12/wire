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
unsigned d1, d2;

struct elem {
    unsigned to;
    unsigned len_to_source;
} stack_elem[VERTICES];
unsigned stack_top;
struct v tmp, diameter_tmp;
unsigned max_path, max_path_v, check;

unsigned diameter(unsigned start, unsigned exclude)
{
    struct elem put, get;
    max_path = max_path_v = 0;
//    printf("start = %u, exclude = %u\n", start, exclude);
    put.to = start;
    put.len_to_source = 0;
    visited[start] = 1;
    visited[exclude] = 1;

    stack_elem[stack_top++] = put;
    while (stack_top != 0) {
        get = stack_elem[--stack_top];
        for (register unsigned edges = 0; edges < links[get.to]; edges++) {
            diameter_tmp = table[get.to][edges];
            if (visited[diameter_tmp.to] == 0) {
                put.to = diameter_tmp.to;
                put.len_to_source = get.len_to_source + diameter_tmp.w;
                visited[put.to] = 1;
                stack_elem[stack_top++] = put;
                if (links[put.to] == 1) {
                    if (max_path < put.len_to_source) {
                        max_path_v = put.to;
                        max_path = put.len_to_source;
                    }
                }
            }
        }
    }
    for (register unsigned x = 1; x <= vertices; x++) {
        visited[x] = 0;
    }

    put.to = max_path_v;
    put.len_to_source = 0;
    visited[max_path_v] = 1;
    visited[exclude] = 1;
    stack_elem[stack_top++] = put;
    while (stack_top != 0) {
        get = stack_elem[--stack_top];
        for (register unsigned edges = 0; edges < links[get.to]; edges++) {
            diameter_tmp = table[get.to][edges];
            if (visited[diameter_tmp.to] == 0) {
                put.to = diameter_tmp.to;
                put.len_to_source = get.len_to_source + diameter_tmp.w;
                visited[put.to] = 1;
                stack_elem[stack_top++] = put;
                if (links[put.to] == 1) {
                    if (max_path < put.len_to_source) {
                        max_path_v = put.to;
                        max_path = put.len_to_source;
                    }
                }
            }
        }
    }
    for (register unsigned x = 1; x <= vertices; x++) {
        visited[x] = 0;
    }
//    printf("max_path = %u\n", max_path);

    return max_path;
}

void solving(void)
{
    answer = 0;

    for (unsigned i = 1; i <= vertices; i++) {
        for (unsigned l = 0; l < links[i]; l++) {
            tmp = table[i][l];
            if (i < tmp.to) {
                check = diameter(i, tmp.to) + diameter(tmp.to, i) + tmp.w;
                if (answer < check) {
                    answer = check;
                }
            }
        }
    }
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
        solving();
        printf("#%u %u\n", i, answer);
        for (unsigned y = 1; y <= vertices; y++) {
            links[y] = 0;
        }
    }

    return 0;
}
