#include <iostream>
#include <map>
#include <cstdio>
#include <queue>

using namespace std;

int n;

class Cache
{
public:
    int size;
    int cnt;
public:
    Cache(int size){this->size = size;};
    virtual void clear(){};
    virtual void push(int id){};
    virtual int pop(){return 0;};
    virtual bool contain(int id){return false;};
    virtual bool isfull(){return false;};
    virtual void begin(vector<int> inputPage){
        this->clear();
        // n = read();
        for (int i = 0; i < n; i++)
            this->push(inputPage[i]);
        
    }
};


class FIFO : public Cache
{
private:
    map<int, int> mp;
    queue<int> q;
public:
    FIFO(int id) : Cache(id) {}
    void clear() override{
        this->cnt = 0;
        mp.clear();
        while (!q.empty()) {
            q.pop();
        }
    }

    bool contain(int id) override{
        return mp.find(id) != mp.end();
    }
    bool isfull() override{
        return mp.size() == this->size;
    }
    int pop () override{
        int tmp = q.front();
        q.pop();
        if ((--mp[tmp]) == 0) {
            mp.erase(tmp);
        }
        return tmp;
    }
    void push(int id) override{
        if (this->contain(id))
            this->cnt = this->cnt + 1;
        else
        {
            if (this->isfull())
                this->pop();
            q.push(id);
            mp[id]=1;
        }
    }
};

class LRU : public Cache
{
private:
    struct node
    {
        int id;
        node *next,*pre;
        node(int id) {
            this->id = id;
            pre = next = NULL;
            }
    };
    map<int, node *> mp;
    node *head, *tail;

public:
    LRU(int id) : Cache(id) {}
    void clear() override{
        this->cnt = 0;
        mp.clear();
        head = tail = NULL;
    }
    void insert(node *now) {
        now->next = head;
        if (head == NULL)
            head = tail = now;
        else
        {
            head->pre = now;
            now->next = head;
            now->pre = NULL;
            head = now;
        }
    }
    void remove(node *now) {
        if (now->pre == NULL)
        {
            head = now->next;
            // head->pre = NULL;
        }
        else
        {
            now->pre->next = now->next;
            // now->next->pre = now->pre;
        }
        if (now->next == NULL)
        {
            tail = now->pre;
            // now->pre->next = NULL;
        }
        else
        {
            now->next->pre = now->pre;
            // now->pre->next = now->next;
        }
    }

    node *pop(int id) {
        if (mp.find(id) != mp.end()) {
            remove(mp.find(id)->second);
            return mp.find(id)->second;
        }
        return NULL;
    }

    bool contain(int id) override{
        return mp.find(id) != mp.end();
    }
    bool isfull() override{
        return mp.size() == this->size;
    }
    int pop () override{
        node *tmp = tail;
        mp.erase(tmp->id);
        remove(tmp);
        delete tmp;
    }

    void push(int id) override{
        node *now = pop(id);
        if (now == NULL)
        {
            if (this->isfull())
                this->pop();
            now = new node(id);
            mp[id]=now;
        }
        else
            this->cnt = this->cnt + 1;
        insert(now);
    }
};

class Min : public Cache
{

private:
    map<int, int> mp;
    priority_queue<pair<int, int> > pq;
    vector<int> a, nx;

public:
    Min(int id) : Cache(id) {}

    void clear() override{
        this->cnt = 0;
        a.clear();
        nx.clear();
        mp.clear();
        while (!pq.empty()) {
            pq.pop();
        }
    }

    bool contain(int id) override{
        return mp.find(id) != mp.end();
    }
    bool isfull() override{
        return mp.size() == this->size;
    }
    void push(int id,int next){
        if (mp.find(id) != mp.end()) {
            ++this->cnt;
        } else {
            if (this->isfull()) {
                pair<int, int> tp = pq.top();
                pq.pop();
                mp.erase(tp.second);
            }
            mp[id] = 1;
        }
        pq.push(make_pair(next, id));
    }
    void begin(vector<int> inputPage) override{
        this->clear();
        for (int i = 0; i < n; i++)
        {
            a.push_back(inputPage[i]);
            nx.push_back(0x7fffffff);
        }
        for (int i = n - 1; i >= 0; --i) {
            if (mp.find(a[i]) != mp.end()) {
                nx[i] = mp.find(a[i])->second;
            }
            mp[a[i]] = i;
        }
        mp.clear();
        for (int i = 0; i < n; ++i) {
            this->push(a[i], nx[i]);
        }
    }

};

class Clock : public Cache
{

private:
    struct node {
        int id;
        int valid = 0;
        node *pre, *next;

        node(int id) {
            this->id = id;
            pre = next = NULL;
            valid = false;
        }
    };

    map<int, node *> mp;
    node *head;

public:
    Clock(int id) : Cache(id) {}
    void clear() override{
        this->cnt = 0;
        mp.clear();
        head = NULL;
    }

    bool contain(int id) override{
        return mp.find(id) != mp.end();
    }
    bool isfull() override{
        return mp.size() == this->size;
    }

    void insert(node *now){
        if (head == NULL)
        {
            now->pre = now->next = now;
            head = now;
        }
        else{
            now->next=head;
            now->pre=head->pre;
            head->pre->next = now;
            head->pre = now;
        }
    }

    void remove(node *now){
        if (now->pre != NULL)
        {
            now->pre->next = now->next;
        }
        if (now->next != NULL)
        {
            now->next->pre = now->pre;
        }
        if (now == head)
        {
            head = now->next;
        }
    }

    int pop() override{
        node *tmp = head;
        while (tmp != NULL && tmp->valid)
        {
            tmp->valid = 0;
            tmp=tmp->next;
        }
        head = tmp->next;
        mp.erase(tmp->id);
        remove(tmp);
        delete(tmp);
    }
    void push(int id) override{
        node *now;
        if (mp.find(id) != mp.end()) {
            now = mp.find(id)->second;
            ++this->cnt;
        } else {
            if (this->isfull()) {
                this->pop();
            }
            now = new node(id);
            mp[id] = now;
            insert(now);
        }
        now->valid = true;
    }
};

int main(){
    int size;
    cin>>size;
    int algorithm;
    cin>>algorithm;
    vector<int> inputPage;
    cin>>n;
    for (int i = 0; i < n; i++){
        int tmp;
        cin>> tmp;
        inputPage.push_back(tmp);
    }
    Cache *cache = NULL;
    switch (algorithm)
    {
    case 0:
        cache = new FIFO(size);
        break;
    case 1:
        cache = new LRU(size);
        break;
    case 2:
        cache = new Min(size);
        break;
    case 3:
        cache = new Clock(size);
        break;
    
    }
    cache->begin(inputPage);
    printf("Hit ratio = %05.2lf%%", (double) cache->cnt / n * 100);
}