#include <stdio.h>

#define MAX(a, b) ((a) < (b)) ? (a) : (b);
#define VERTICES 2001

struct v {
    unsigned to;
    unsigned w;
};

struct adj {
    unsigned length;
    unsigned first_vert_path;
};

struct v table[VERTICES][VERTICES - 1];
struct adj arr_adj[VERTICES][VERTICES];
unsigned links[VERTICES];
unsigned visited[VERTICES];

unsigned vertices;
unsigned answer;
unsigned d1, d2;
unsigned max_edge_vert;

struct elem {
    unsigned to;
    unsigned len_to_source;
    unsigned prev_vert;
    unsigned first_vert_path;
} stack_elem[VERTICES];
unsigned stack_top;
struct elem put, get;
struct v edge;

void resolve(unsigned from, unsigned exclude)
{
    (void)from;
    (void)exclude;
}

void deep(unsigned start)
{
    stack_top = 0;
    //search paths from vertice with max edges.
    visited[start] = 1;
    put.to = start;
    put.len_to_source = 0;
    stack_elem[stack_top++] = put;
//    get = stack_elem[--stack_top];
/*    for (unsigned edges = 0; edges < links[start]; edges++) {
        edge = table[get.to][edges];
//        printf("edge.to = %u, edge.w = %u\n", edge.to, edge.w);
        if (visited[edge.to] == 0) {
            put.to = edge.to;
            put.len_to_source = edge.w;
            put.prev_vert = get.to;
            put.first_vert_path = edge.to;
            visited[put.to] = 1;
            stack_elem[stack_top++] = put;
            arr_adj[start][edge.to].length = arr_adj[edge.to][start].length = edge.w;
        }
    }*/
    while (stack_top != 0) {
        get = stack_elem[--stack_top];
        printf("get.to = %u, get.len_to_source = %u\n", get.to, get.len_to_source);
        for (unsigned edges = 0; edges < links[get.to]; edges++) {
            edge = table[get.to][edges];
//            printf("edge.to = %u, edge.w = %u\n", edge.to, edge.w);
            if (visited[edge.to] == 0) {
//                printf("edge.to = %u, edge.w = %u\n", edge.to, edge.w);
                put.to = edge.to;
                put.len_to_source = get.len_to_source + edge.w;
//                put.prev_vert = get.to;
//                put.first_vert_path = get.first_vert_path;
                arr_adj[start][edge.to].length = arr_adj[edge.to][start].length = put.len_to_source;
                visited[put.to] = 1;
                stack_elem[stack_top++] = put;
            } else {
//                printf("Try to resolve\n");
            }
        }
    }
    for (unsigned x = 1; x <= vertices; x++) {
        visited[x] = 0;
    }
}

void solving(void)
{
    answer = 0;
    deep(max_edge_vert);
    deep(1);
}

int main(void)
{
    unsigned cases;
    unsigned from, to, weight;
    unsigned idx;

    scanf("%u", &cases);
    cases++;

    for (unsigned i = 1; i < cases; i++) {
        max_edge_vert = 0;
        scanf("%u", &vertices);
        for (unsigned v = 1; v < vertices; v++) {
            scanf("%u %u %u", &weight, &from, &to);
//            printf("%u %u %u\n", weight, from, to);
            idx = links[from]++;
            table[from][idx].to = to;
            table[from][idx].w = weight;
            max_edge_vert = (links[max_edge_vert] > links[from]) ? max_edge_vert : from;
            idx = links[to]++;
            table[to][idx].to = from;
            table[to][idx].w = weight;
            max_edge_vert = (links[max_edge_vert] > links[to]) ? max_edge_vert : to;
//            arr_adj[from][to].length = arr_adj[to][from].length = weight;
        }
        solving();
        for (unsigned y = 1; y <= vertices; y++) {
            for (unsigned x = 1; x <= vertices; x++) {
                printf("%u ", arr_adj[y][x].length);
            }
            printf("\n");
        }
        printf("max_edge_vert = %u\n", max_edge_vert);
        printf("#%u %u\n", i, answer);
        for (unsigned y = 1; y <= vertices; y++) {
            links[y] = 0;
        }
    }

    return 0;
}
