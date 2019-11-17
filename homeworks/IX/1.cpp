//根据Dijkstra算法，求从起点0出发到达其它节点的最短路径，
//同时用数组pre[i]记录到达节点i的最短路径中离i最近的节点（前驱节点），
//如果最短路径不止一条，则记录边的数量最少的路径。
#include "../Graphs/grmat.h" //临界节点实现图
#include "../Heaps/Heap.cpp" //堆

const int INF = 9999;

struct vertex{
    int pre; //前驱节点
    int v; //该节点
    int dist; //到该点的距离
    int edge; //到该点要经过多少条边
    vertex(): pre(-1), v(-1), dist(-1), edge(-1){}
    vertex(int _pre, int _v, int d, int e): pre(_pre), v(_v), dist(d), edge(e){}
};

struct comp{
    static bool prior(vertex a, vertex b){
        //以距离少的优先，如果距离相同，则边少的优先
        if (a.dist < b.dist || a.dist == b.dist && a.edge < b.edge) return true;
        return false;
    }
};

void Dijkstra(Graph* G, int s, int* d, int* pre){
    int v, w; //v为当前点，w为相邻点
    vertex currv; //当前顶点结构体
    //建立heap
    vertex store[G->e()];
    heap<vertex, comp> pq(store, 0, G->e());
    //d初始化为INF
    fill(d, d+G->n(), INF);

    d[s] = 0;
    pq.insert(vertex(-1, s, 0, 0));

    while(pq.size()){
        //从堆中取出的节点就确定下来不再访问
        currv = pq.removefirst();
        v = currv.v;
        if (G->getMark(v) == UNVISITED)
            pre[v] = currv.pre; //第一次取出v时，v的最近前驱节点就确定了，以后取出的都不是

        G->setMark(v, VISITED);
        for(w = G->first(v); w<G->n(); w = G->next(v,w)){
            if(G->getMark(w) == UNVISITED){
                d[w] = min(d[w],  d[v] + G->weight(v,w));
                pq.insert(vertex(v, w, d[w], currv.edge + 1));
            }
        }
    }

}

int main(){
    Graph* G = new Graphm(5);
    G->setEdge(0, 1, 10);
    G->setEdge(0, 2, 5);
    G->setEdge(0, 4, 25);
    G->setEdge(1, 3, 3);
    G->setEdge(1, 4, 15);
    G->setEdge(2, 3, 2);
    G->setEdge(2, 4, 20);
    //Gprint(G);
    int d[G->n()], pre[G->n()];
    Dijkstra(G, 0, d, pre);
    for (int i = 0; i < G->n(); i++){
        cout<<"d["<<i<<"]="<<d[i]<<" "<<"pre["<<i<<"]="<<pre[i]<<endl;
    }
    
}

