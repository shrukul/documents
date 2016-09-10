#include <bits/stdc++.h>
using namespace std;

#define MAX 100001
#define INF (1<<20)
#define pii pair< int, int >
#define pb(x) push_back(x)

int index_node;

/*-------------------------------BINARY HEAP----------------------------------------------------------*/

/*Binary Heap*/
vector < pair<int,int> > binaryHeap;

int parent(int index)
{
    int res=(index-1)/2;

    if(index==0)
        return -1;
    else
        return res;
}

int value(int index)
{
    return binaryHeap[index].first;
}

void heapifyUpBinaryHeap(int index)
{
    if(index>=0&&parent(index)>=0&&value(parent(index))>value(index))
    {
        swap(binaryHeap[index],binaryHeap[parent(index)]);
        heapifyUpBinaryHeap(parent(index));
    }
}

void insertBinaryHeap( pair<int,int> element)
{
    binaryHeap.push_back(element);
    heapifyUpBinaryHeap(binaryHeap.size()-1);
}

int getLeft(int index)
{
    return index*2+1;
}

int getRight(int index)
{
    return index*2+2;
}

void heapifyDownBinaryHeap(int index)
{
    int left=getLeft(index);
    int right=getRight(index);
    int largest=index;

    if(left<binaryHeap.size()&&value(left)<=value(largest))
        largest=left;

    if(right<binaryHeap.size()&&value(right)<=value(largest))
        largest=right;

    if(largest!=index)
    {
        swap(binaryHeap[index],binaryHeap[largest]);
        heapifyDownBinaryHeap(largest);
    }

}

pair<int,int> deleteBinaryHeap()
{
    pair<int,int> res=binaryHeap[0];
    binaryHeap[0] = binaryHeap.at(binaryHeap.size() - 1);
    binaryHeap.pop_back();
    heapifyDownBinaryHeap(0);
    return res;
}


/*-------------------------------BINOMIAL HEAP--------------------------------------------------------*/
struct node
{
    int n;
    int index;      //added new
    int degree;
    node* parent;
    node* child;
    node* sibling;
};
/*
 * Class Declaration
 */
class BinomialHeap
{
    private:
        node *H;
        node *Hr;
        int count;
    public:
        node* Initializeheap();
        int Binomial_link(node*, node*);
        node* Create_node(int, int);
        node* Union(node*, node*);
        node* Insert(node*, node*);
        node* Merge(node*, node*);
        node* Extract_Min(node*);
        void pop(node *);


        int Revert_list(node*);
        int Display(node*);
        node* Search(node*, int);
        int Decrease_key(node*, int, int);
        int Delete(node*, int);
        BinomialHeap()
        {
            H = Initializeheap();
            Hr = Initializeheap();
            int count = 1;
        }
};


/*
 * Initialize Heap
 */
node* BinomialHeap::Initializeheap()
{
    node* np;
    np = NULL;
    return np;
}
/*
 * Linking nodes in Binomial Heap
 */
int BinomialHeap::Binomial_link(node* y, node* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
/*
 * Create Nodes in Binomial Heap
 */
node* BinomialHeap::Create_node(int k, int ind)
{
    node* p = new node;
    p->n = k;
    p->index = ind;
    return p;
}
/*
 * Insert Nodes in Binomial Heap
 */
node* BinomialHeap::Insert(node* H, node* x)
{
    node* H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}

/*
 * Union Nodes in Binomial Heap
 */
node* BinomialHeap::Union(node* H1, node* H2)
{
    node *H = Initializeheap();
    H = Merge(H1, H2);
    if (H == NULL)
        return H;
    node* prev_x;
    node* next_x;
    node* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return H;
}
/*
 * Merge Nodes in Binomial Heap
 */
node* BinomialHeap::Merge(node* H1, node* H2)
{
    node* H = Initializeheap();
    node* y;
    node* z;
    node* a;
    node* b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}
/*
 * Display Binomial Heap
 */
int BinomialHeap::Display(node* H)
{
    if (H == NULL)
    {
        cout<<"The Heap is empty"<<endl;
        return 0;
    }
    cout<<"The root nodes are: "<<endl;
    node* p;
    p = H;
    while (p != NULL)
    {
        cout<<p->n;
        if (p->sibling != NULL)
            cout<<"-->";
        p = p->sibling;
    }
    cout<<endl;
}
/*
 * Extract Minimum
 */
node* BinomialHeap::Extract_Min(node* H1)
{
    Hr = NULL;
    node* t = NULL;
    node* x = H1;
    if (x == NULL)
    {
        cout<<"Nothing to Extract"<<endl;
        return x;
    }
    int min = x->n;
    node* p = x;
    while (p->sibling != NULL)
    {
        if ((p->sibling)->n < min)
        {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
    {
        //cout<<"first\n";
        H1 = NULL;
    }
    else if (t == NULL)
    {
        //cout<<"sec\n";
        H1 = x->sibling;
    }
    else if (t->sibling == NULL)
    {
        //cout<<"third\n";
        t = NULL;
    }
    else
    {
        //cout<<"fourth\n";
        t->sibling = x->sibling;
    }
    if (x->child != NULL)
    {
        Revert_list(x->child);
        (x->child)->sibling = NULL;
    }
    H = Union(H1, Hr);
    if(H)
    {
        //cout<<"H->n "<<H->n<<endl;
        H->parent=NULL;
        /*if(H->parent) cout<<"H->parent "<<H->parent->n<<endl;
        if(H->child) cout<<"H->child "<<H->child->n<<endl;

        if(H->sibling) cout<<"H->sibling "<<H->sibling->n<<endl;*/
    }
    if(x)
    {
        index_node = x->index;

    }
    else{
        index_node = -1;
    }
    return H;
}
/*
 * Reverse List
 */
int BinomialHeap::Revert_list(node* y)
{
    if (y->sibling != NULL)
    {
        Revert_list(y->sibling);
        (y->sibling)->sibling = y;
    }
    else
    {
        Hr = y;
    }
}

/*
 * Search Nodes in Binomial Heap
 */
node* BinomialHeap::Search(node* H, int k)
{
    node* x = H;
    node* p = NULL;
    if (x->n == k)
    {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL)
        p = Search(x->child, k);
    if (x->sibling != NULL && p == NULL)
        p = Search(x->sibling, k);
    return p;
}
/*
 * Decrease key of a node
 */
int BinomialHeap::Decrease_key(node* H, int i, int k)
{
    int temp;
    node* p;
    node* y;
    node* z;
    p = Search(H, i);
    if (p == NULL)
    {
        cout<<"Invalid choice of key"<<endl;
        return 0;
    }
    if (k > p->n)
    {
        cout<<"Error!! New key is greater than current key"<<endl;
        return 0;
    }
    p->n = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->n < z->n)
    {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    cout<<"Key reduced successfully"<<endl;
}
/*
 * Delete Nodes in Binomial Heap
 */
int BinomialHeap::Delete(node* H, int k)
{
    node* np;
    if (H == NULL)
    {
        cout<<"\nHEAP EMPTY!!!!!";
        return 0;
    }
    Decrease_key(H, k, INT_MIN);
    np = Extract_Min(H);
    np->parent;
    if (np != NULL)
        cout<<"Node Deleted Successfully"<<endl;
}


/*--------------------------------FIBONACCI HEAP---------------------------------------------------------------------*/

struct nodef
{
    int n;
    int index;
    int degree;
    nodef* parent;
    nodef* child;
    nodef* left;
    nodef* right;

    char mark;
    char C;
};
/*
 * Class Declaration
 */
class FibonacciHeap
{
    private:
        int nH;
        nodef *H;
    public:
        nodef* InitializeHeap();
        int Fibonnaci_link(nodef*, nodef*, nodef*);
        nodef *Create_node(int, int);
        nodef *Insert(nodef *, nodef *);
        nodef *Union(nodef *, nodef *);
        nodef *Extract_Min(nodef *);

        void pop();
        int top();

        int Consolidate(nodef *);
        int Display(nodef *);
        nodef *Find(nodef *, int);
        int Decrease_key(nodef *, int, int);
        int Delete_key(nodef *,int);
        int Cut(nodef *, nodef *, nodef *);
        int Cascase_cut(nodef *, nodef *);
        FibonacciHeap()
        {
            H = InitializeHeap();
        }
};
/*
 * Initialize Heap
 */

void FibonacciHeap::pop()
{
    nodef *temp;
    temp = Extract_Min(H);
    Delete_key(H, temp->n);
}

int FibonacciHeap::top()
{
    nodef *temp = Extract_Min(H);
    return temp->index;
}

nodef* FibonacciHeap::InitializeHeap()
{
    nodef* np;
    np = NULL;
    return np;
}
/*
 * Create nodef
 */
nodef* FibonacciHeap::Create_node(int value, int ind)
{
    nodef* x = new nodef;
    x->n = value;
    x->index = ind;
    return x;
}
/*
 * Insert nodef
 */
nodef* FibonacciHeap::Insert(nodef* H, nodef* x)
{
    x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    x->mark = 'F';
    x->C = 'N';
    if (H != NULL)
    {
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->n < H->n)
            H = x;
    }
    else
    {
        H = x;
    }
    nH = nH + 1;
    return H;
}
/*
 * Link nodefs in Fibonnaci Heap
 */
int FibonacciHeap::Fibonnaci_link(nodef* H1, nodef* y, nodef* z)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (z->right == z)
        H1 = z;
    y->left = y;
    y->right = y;
    y->parent = z;
    if (z->child == NULL)
        z->child = y;
    y->right = z->child;
    y->left = (z->child)->left;
    ((z->child)->left)->right = y;
    (z->child)->left = y;
    if (y->n < (z->child)->n)
        z->child = y;
    z->degree++;
}
/*
 * Union nodefs in Fibonnaci Heap
 */
nodef* FibonacciHeap::Union(nodef* H1, nodef* H2)
{
    nodef* np;
    nodef* H = InitializeHeap();
    H = H1;
    (H->left)->right = H2;
    (H2->left)->right = H;
    np = H->left;
    H->left = H2->left;
    H2->left = np;
    return H;
}
/*
 * Display Fibonnaci Heap
 */
int FibonacciHeap::Display(nodef* H)
{
    nodef* p = H;
    if (p == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return 0;
    }
    cout<<"The root nodefs of Heap are: "<<endl;
    do
    {
        cout<<p->n;
        p = p->right;
        if (p != H)
        {
            cout<<"-->";
        }
    }
    while (p != H && p->right != NULL);
    cout<<endl;
}
/*
 * Extract Min nodef in Fibonnaci Heap
 */
nodef* FibonacciHeap::Extract_Min(nodef* H1)
{
    nodef* p;
    nodef* ptr;
    nodef* z = H1;
    p = z;
    ptr = z;
    if (z == NULL)
        return z;
    nodef* x;
    nodef* np;
    x = NULL;
    if (z->child != NULL)
        x = z->child;
    if (x != NULL)
    {
        ptr = x;
        do
        {
            np = x->right;
            (H1->left)->right = x;
            x->right = H1;
            x->left = H1->left;
            H1->left = x;
            if (x->n < H1->n)
                H1 = x;
            x->parent = NULL;
            x = np;
        }
        while (np != ptr);
    }
    (z->left)->right = z->right;
    (z->right)->left = z->left;
    H1 = z->right;
    if (z == z->right && z->child == NULL)
        H = NULL;
    else
    {
        H1 = z->right;
        Consolidate(H1);
    }
    nH = nH - 1;
    if(p)
        index_node = p->index;
    else
        index_node = -1;
    return H;
}
/*
 * Consolidate nodef in Fibonnaci Heap
 */
int FibonacciHeap::Consolidate(nodef* H1)
{
    int d, i;
    float f = (log(nH)) / (log(2));
    int D = f;
    nodef* A[D];
    for (i = 0; i <= D; i++)
        A[i] = NULL;
    nodef* x = H1;
    nodef* y;
    nodef* np;
    nodef* pt = x;
    do
    {
        pt = pt->right;
        d = x->degree;
        while (A[d] != NULL)
        {
            y = A[d];
            if (x->n > y->n)
            {
                np = x;
                x = y;
                y = np;
            }
            if (y == H1)
                H1 = x;
            Fibonnaci_link(H1, y, x);
            if (x->right == x)
                H1 = x;
                A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
        x = x->right;
    }
    while (x != H1);
    H = NULL;
    for (int j = 0; j <= D; j++)
    {
        if (A[j] != NULL)
        {
            A[j]->left = A[j];
            A[j]->right =A[j];
            if (H != NULL)
            {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->n < H->n)
                H = A[j];
            }
            else
            {
                H = A[j];
            }
            if(H == NULL)
                H = A[j];
            else if (A[j]->n < H->n)
                H = A[j];
        }
    }
}

/*
 * Decrease key of nodefs in Fibonnaci Heap
 */
int FibonacciHeap::Decrease_key(nodef*H1, int x, int k)
{
    nodef* y;
    if (H1 == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return 0;
    }
    nodef* ptr = Find(H1, x);
    if (ptr == NULL)
    {
        cout<<"nodef not found in the Heap"<<endl;
        return 1;
    }
    if (ptr->n < k)
    {
        cout<<"Entered key greater than current key"<<endl;
        return 0;
    }
    ptr->n = k;
    y = ptr->parent;
    if (y != NULL && ptr->n < y->n)
    {
        Cut(H1, ptr, y);
        Cascase_cut(H1, y);
    }
    if (ptr->n < H->n)
        H = ptr;
    return 0;
}
/*
 * Cut nodefs in Fibonnaci Heap
 */
int FibonacciHeap::Cut(nodef* H1, nodef* x, nodef* y)
{
    if (x == x->right)
        y->child = NULL;
    (x->left)->right = x->right;
    (x->right)->left = x->left;
    if (x == y->child)
        y->child = x->right;
    y->degree = y->degree - 1;
    x->right = x;
    x->left = x;
    (H1->left)->right = x;
    x->right = H1;
    x->left = H1->left;
    H1->left = x;
    x->parent = NULL;
    x->mark = 'F';
}

/*
 * Cascade Cutting in Fibonnaci Heap
 */
int FibonacciHeap::Cascase_cut(nodef* H1, nodef* y)
{
    nodef* z = y->parent;
    if (z != NULL)
    {
        if (y->mark == 'F')
        {
            y->mark = 'T';
	}
        else
        {
            Cut(H1, y, z);
            Cascase_cut(H1, z);
        }
    }
}

/*
 * Find nodefs in Fibonnaci Heap
 */
nodef* FibonacciHeap::Find(nodef* H, int k)
{
    nodef* x = H;
    x->C = 'Y';
    nodef* p = NULL;
    if (x->n == k)
    {
        p = x;
        x->C = 'N';
        return p;
    }
    if (p == NULL)
    {
        if (x->child != NULL )
            p = Find(x->child, k);
        if ((x->right)->C != 'Y' )
            p = Find(x->right, k);
    }
    x->C = 'N';
    return p;
}
/*
 * Delete nodefs in Fibonnaci Heap
 */
int FibonacciHeap::Delete_key(nodef* H1, int k)
{
    nodef* np = NULL;
    int t;
    t = Decrease_key(H1, k, -5000);
    if (!t)
        np = Extract_Min(H);
    if (np != NULL)
        cout<<"Key Deleted"<<endl;
    else
        cout<<"Key not Deleted"<<endl;
    return 0;
}


vector< pii > G[MAX];
int D[MAX];
bool F[MAX];
int i, u, v, w, sz, nodes, edges, starting;

void binary_heap()
{
            memset(F, 0, sizeof F);

            for(int i=0;i<=nodes;i++)
                D[i]=INT_MAX;

            int start = starting;
            insertBinaryHeap(make_pair(0,start));
            D[start]=0;

            while(binaryHeap.size()!=0)
            {
                pair<int,int> res=deleteBinaryHeap();

                int u=res.second;

                if(F[u]==1)
                    continue;

                for(vector< pair< int,int > >::iterator it=G[u].begin();it!=G[u].end();it++ )
                {
                    int v=(*it).first;
                    int d=(*it).second;
                    if(F[v]==0 && D[v] >D[u]+d)
                    {
                        D[v] = D[u] + d;
                        insertBinaryHeap(make_pair(D[v],v));
                    }

                }

                F[u]=1;
            }

            for(int i=1;i<=nodes;i++)
                printf("Distance=%d\n",D[i]);
}

void binomial_heap()
{
    memset(F, 0, sizeof F);
    BinomialHeap bh;
    node* p;
    node *H;
    H = bh.Initializeheap();

    // initialize distance vector
    for(i=1; i<=nodes; i++) D[i] = INF;

    D[starting] = 0;
    p = bh.Create_node(0, starting);
    H = bh.Insert(H, p);

    // dijkstra

    index_node=starting;
    while(H!=NULL) {


        H=bh.Extract_Min(H);
        u = index_node;
        if(u == -1)
            break;
        if(F[u]) continue;
        sz = G[u].size();
        //cout<<"top - "<<u<<endl;
        for(i=0; i<sz; i++) {
            v = G[u][i].first;
            w = G[u][i].second;
            if(!F[v] && D[u]+w < D[v]) {
                D[v] = D[u] + w;
                p = bh.Create_node(D[v], v);
                H=bh.Insert(H, p);
                //Q.push(pii(v, D[v]));
                //cout<<v<<" ";
            }
        }
        //cout<<endl;
        F[u] = 1; // done with u
    }

    // result
    for(i=1; i<=nodes; i++) printf("Node %d, min weight = %d\n", i, D[i]);
}

void fibonacci_heap()
{
    memset(F, 0, sizeof F);
    FibonacciHeap bh;
    nodef* p;
    nodef *H;
    H = bh.InitializeHeap();

    // initialize distance vector
    for(i=1; i<=nodes; i++) D[i] = INF;

    D[starting] = 0;
    p = bh.Create_node(0, starting);
    H = bh.Insert(H, p);

    // dijkstra

    index_node=starting;
    while(H!=NULL) {

        //cout<<"a\n";
        H=bh.Extract_Min(H);
        u = index_node;
        if(u == -1)
            break;
        if(F[u]) continue;
        sz = G[u].size();
        //cout<<"tp - "<<u<<endl;
        for(i=0; i<sz; i++) {
            v = G[u][i].first;
            w = G[u][i].second;
            if(!F[v] && D[u]+w < D[v]) {
                D[v] = D[u] + w;
                p = bh.Create_node(D[v], v);
                H=bh.Insert(H, p);
                //Q.push(pii(v, D[v]));
                //cout<<v<<" ";
            }
        }
        //cout<<endl;
        F[u] = 1; // done with u
    }

    // result
    for(i=1; i<=nodes; i++) printf("Node %d, min weight = %d\n", i, D[i]);
}

int main() {

    // create graph
    scanf("%d %d", &nodes, &edges);
    for(i=0; i<edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        G[u].pb(pii(v, w));
        G[v].pb(pii(u, w)); // for undirected
    }
    while(1){


        int type;
        printf("Select type of Heap\n1.Binary Heap\n2.Binomial Heap\n3.Fibonacci Heap\n4.Exit\n");
        scanf("%d",&type);
        printf("Enter Start Vertex : ");
        scanf("%d", &starting);

        if(type==1)
        {
            //long long initialTime=
            binary_heap();

        }
        else if(type==2)
        {
            binomial_heap();
        }
        else if(type==3)
        {
            fibonacci_heap();
        }
        else
            return 0;

    }

    return 0;
}
