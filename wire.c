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
unsigned calculated[VERTICES];

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
unsigned leaf_list[VERTICES];
unsigned leaf_list_cnt;
struct elem put, get;
struct v edge;
unsigned d1, d1;

void resolve(unsigned from, unsigned exclude)
{
    (void)from;
    (void)exclude;
}

void deep(unsigned start)
{
//    unsigned new_length;
    stack_top = 0;
//    printf("start = %u\n", start);

    for (unsigned edges = 0; edges < links[start]; edges++) {
        edge = table[start][edges];
        put.to = edge.to;
        put.len_to_source = edge.w;
        put.prev_vert = start;
        put.first_vert_path = edge.to;
        stack_elem[stack_top++] = put;
        arr_adj[start][edge.to].length = put.len_to_source;
        arr_adj[start][edge.to].first_vert_path = edge.to;
    }

    while (stack_top != 0) {
        get = stack_elem[--stack_top];
//        printf("get.to = %u, get.len_to_source = %u, get.first_vert_path = %u, get.prev_vert = %u\n", get.to, get.len_to_source, get.first_vert_path, get.prev_vert);
        if (calculated[get.to] == 1) {
//            printf("start = %u, get.to = %u, get.prev.vert = %u, first_vert_path = %u\n", start, get.to, get.prev_vert, get.first_vert_path);
            for (unsigned x = 1; x <= vertices; x++) {
                if (arr_adj[get.to][x].first_vert_path != get.prev_vert
                        && (x != get.to && x != get.prev_vert)) {
                    arr_adj[start][x].length = get.len_to_source + arr_adj[get.to][x].length;
                    arr_adj[start][x].first_vert_path = /*(get.first_vert_path == start) ? start : */get.first_vert_path;
                }
            }
            continue;
        }

        for (unsigned edges = 0; edges < links[get.to]; edges++) {
            edge = table[get.to][edges];
//            printf("edge.to = %u, edge.w = %u\n", edge.to, edge.w);
            if (get.prev_vert != edge.to) {
//                printf("edge.to = %u, edge.w = %u\n", edge.to, edge.w);
                put.to = edge.to;
                put.len_to_source = get.len_to_source + edge.w;
                put.prev_vert = get.to;
                put.first_vert_path = get.first_vert_path;
//                printf("to = %u, first_vert_path = %u\n", put.to, get.first_vert_path);
//              top triangle
                arr_adj[start][edge.to].length = put.len_to_source;
                arr_adj[start][edge.to].first_vert_path = put.first_vert_path;
//              bottom triangle
//                arr_adj[edge.to][start].length = put.len_to_source;
//                arr_adj[edge.to][start].first_vert_path = put.prev_vert;
                stack_elem[stack_top++] = put;
            }
        }
    }
    calculated[start] = 1;
}

/*unsigned get_diameter(unsigned v1, unsigned v2)
{
    return 0;
}*/

void solving(void)
{
    answer = 0;
    deep(max_edge_vert);
    for (unsigned x = 1; x < max_edge_vert; x++) {
        deep(x);
    }
    for (unsigned x = max_edge_vert + 1; x <= vertices; x++) {
        deep(x);
    }
    for (unsigned v = 1; v <= vertices; v++) {
        for (unsigned edges = 0; edges < links[v]; edges++) {
            edge = table[v][edges];
//            d1 = get_diameter(v, edge.to);
//            d2 = get_diameter(edge.to, v);
        }
    }
//    deep(1);
//    deep(2);
//    deep(3);
//    deep(4);
//    deep(5);
//    deep(6);
//    deep(7);
//    deep(1);
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
        leaf_list_cnt = 0;
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
        for (unsigned x = 1; x <= vertices; x++) {
            if (links[x] == 1) {
                leaf_list[leaf_list_cnt++] = x;
            }
        }
/*        for (unsigned x = 0; x < leaf_list_cnt; x++) {
            printf("leaf[%u] = %u\n", x, leaf_list[x]);
        }*/
        solving();
        for (unsigned y = 1; y <= vertices; y++) {
            for (unsigned x = 1; x <= vertices; x++) {
                printf("%2u %2u|", arr_adj[y][x].length, arr_adj[y][x].first_vert_path);
            }
            printf("\n");
        }
        printf("max_edge_vert = %u\n", max_edge_vert);
        printf("#%u %u\n", i, answer);
        for (unsigned y = 1; y <= vertices; y++) {
            links[y] = 0;
            calculated[y] = 0;
        }
    }

    return 0;
}
