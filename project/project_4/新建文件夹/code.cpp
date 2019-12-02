
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>


using namespace std;
const int INF = 9999;

class graph{
private:
    int nv, ne; //结点总数，边总数
    int **m;    //邻接矩阵

    void init(){
        ne = 0;
        m = new int*[nv+1];

        for (int i = 1; i <= nv; i++){
            m[i] = new int[nv+1];
            for (int j = 1; j <= nv; j++){
                m[i][j] = 0;
            }
        }
    }

public:
    graph(int numV){
        nv = numV;
        init();
    }
    
    ~graph() {
        for (int i = 1; i <= nv; i++){
            delete [] m[i];
        }
        delete [] m;
    }

    int n() { return nv; }
    int e() { return ne; }

    inline int weight(int v1, int v2){
        return m[v1][v2];
    }

    int first(int v) {
        for (int i = 1; i <= nv; i++)
            if (m[v][i])
                return i;
        return nv+1;
    }

    int next(int v, int w){
        for (int i = w + 1; i <= nv; i++)
            if (m[v][i])
                return i;
        return nv+1;
    }

    void setEdge(const int v1, const int v2, const int wt){
        assert(wt>0);
        if (!m[v1][v2])
            ne++;
        m[v1][v2] = wt;
    }

    void delEdge(const int v1, const int v2){
        assert(v1 >0 && v1 <= nv && v2 > 0 && v2 <= nv);
        if(m[v1][v2])
            ne--;
        m[v1][v2] = 0;
    }

    bool isEdge(const int v1, const int v2){
        return m[v1][v2] != 0;
    }

};

struct edge{
        int v1, v2;
        int d;
        edge(){ v1 = -1; v2 = -1; d = -1;}
        edge(int _v1, int _v2, int _d){
            v1 = _v1;
            v2 = _v2;
            d = _d;
        }
    };

class graphutil{
private:
    graph *g;
    graphutil();

    bool *seen; //是否访问过某个节点
    queue<int> q; //bfs用队列

    //dijkstra-----------------------
    
    struct comp{
        bool operator ()(const edge n1, const edge n2){
            //默认大顶堆
            return n1.d > n2.d;
        }
    };

    priority_queue<edge, vector<edge>, comp> pq; 
    int *d; //其他点到v点的最短距离数组

    //-------------------------------

    void visit(const int v, bool end = false){
        if(end)
            cout << v;
        else
            cout << v << " ";
    }

    //dfs
    void dfs_help(const int v, int count){
        seen[v] = true;
        visit(v, count == g->n());
        for (int i = g->first(v); i <= g->n(); i = g->next(v, i))
            if (!seen[i])
                dfs_help(i, count + 1);
    }
    //-------------------------------
    //并查集
    int *p;

    void init_set(){
        p = new int[g->n()+1];
        for (int i = 1; i <= g->n(); i++){
            p[i] = i;
        }
    }

    int root(const int v){
        if (v == p[v]) return v;
        return p[v] = root(p[v]);
    }

    bool same(const int v1, const int v2){
        return root(v1) == root(v2);
    }

    bool unite(int v1, int v2){
        v1 = root(v1);
        v2 = root(v2);
        if(v1 == v2) return false;
        p[v2] = p[v1];
        return true;
    }

    vector<edge> *edges;

public:
    graphutil(graph *_g){
        g = _g;
        seen = new bool[g->n()+1];
        fill(seen + 1, seen + g->n() + 1, false);
        d = new int[g->n()+1];
        
        edges = new vector<edge>[g->n()+1];
        for (int i = 1; i <= g->n(); i++){
            for (int j = i + 1; j <= g->n(); j++){
                if(g->isEdge(i, j))
                    edges[i].push_back(edge(i, j, g->weight(i, j)));
            }
        }

        init_set();
    }
    ~graphutil() {
        delete []seen;
        delete []d;
    }

    void dfs(){
        //初始化
        fill(seen + 1, seen + g->n() + 1, false);
        //对每个没访问过的点dfs一遍，保证非连通图能被完整搜索
        for (int i = 1; i <= g->n(); i++)
            if (!seen[i])
                dfs_help(i, 1);
    }

    void bfs(){
        //初始化
        fill(seen + 1, seen + g->n() + 1, false);
        
        while(!q.empty()) q.pop();
        int v;
        int count = 0;

        for (int i = 1; i <= g->n(); i++){
            //对每个没访问过的点放入队列中等待搜索
            if (!seen[i])
                q.push(i);
            
            //遍历队首点的所有邻接节点
            while (!q.empty()){
                v = q.front(); q.pop();
                if (!seen[v]){
                    count++; 
                    visit(v, count == g->n());
                }
                seen[v] = true;
                for (int i = g->first(v); i <= g->n(); i = g->next(v, i))
                    if (!seen[i])
                        q.push(i);
            }
        }
    }

    int* dijkstra(const int v, int *pre){ //pre数组回溯用
        //初始化
        delete []d;
        d = new int[g->n()+1];
        fill(d + 1, d + g->n() + 1, INF);
        fill(seen + 1, seen + g->n() + 1, false);
        while(!pq.empty()) pq.pop();

        d[v] = 0;
        pq.push(edge(v, v, 0));
        
        int w;
        while(!pq.empty()){
            edge n = pq.top(); pq.pop();
            w = n.v2;
            if (!seen[w]){
                d[w] = n.d;
                pre[w] = n.v1;
            }
            seen[w] = true;

            for (int i = g->first(w); i <= g->n(); i = g->next(w, i))
                if(!seen[i] && (d[w] + g->weight(w, i)) < d[i])
                    pq.push(edge(w, i, d[w] + g->weight(w, i)));
        }
        return d;
    }

    void gen_path(int v1, int v2, int *d, int *pre){
        stack<int> s;
        int dist = d[v2];
        while(v2 != v1){
            s.push(v2);
            v2=pre[v2];
        }
        cout<<v1<<" ";
        while(!s.empty()){
            cout<<s.top()<<" ";
            s.pop();
        }
        cout<<dist;
    }

    bool _has_circle = false;

    void kruskal(queue<edge>& res){
        //初始化
        _has_circle = false;
        
        while(!pq.empty()) pq.pop();
        
        for(int i = 1; i <= g->n(); i++){
            for (int j = 0; j < edges[i].size(); j++){
                pq.push(edges[i][j]);
            }
        }

        while(!pq.empty()){
            edge e = pq.top(); pq.pop();
            int v1 = e.v1, v2 = e.v2;
            if (unite(v1, v2))
                res.push(e);
            else
                _has_circle = true;
        }
    }

    inline bool has_circle(){ return _has_circle; }

};

int main(){
    int nv, ne;
    int v, w, wt;
    cin>>nv>>ne;
    graph *g = new graph(nv);
    for (int i = 0; i < ne; i++){
        cin>>v>>w>>wt;
        g->setEdge(v, w, wt);
        g->setEdge(w, v, wt);
    }

    graphutil gu(g);
    gu.bfs();
    cout<<endl;
    gu.dfs();
    cout<<endl;
    
    int *pre = new int[g->n()+1];
    int *d = gu.dijkstra(1, pre);
    for (int i = 2; i <= g->n(); i++){
        gu.gen_path(1, i, d, pre);
        cout << endl;
    }

    queue<edge>res;

    gu.kruskal(res);

    while(!res.empty()){
        edge e = res.front(); res.pop();
        printf("%d %d %d\n", e.v1, e.v2, e.d);
    }

    cout<<(gu.has_circle() ? "YES" : "NO");
    
}