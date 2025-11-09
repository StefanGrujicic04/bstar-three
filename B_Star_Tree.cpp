//
// Created by Stefan Grujicic on 16.11.24..
//
#include "B_Star_Tree.h"
void BStarTree::find_name(){
    if (!root){
        std::cout<<"Stablo je prazno!\n";
        return;
    }
    std::string ime;
    std::cout<<"Napisite ime za pretragu:\n";
    std::cin>>ime;
    std::queue<Node*> children;
    std::queue<int> level;
    children.push(root);
    level.push(0);

    Node* tren;
    int tren_level;
    while(!children.empty())
    {
        tren=children.front();
        tren_level=level.front();
        children.pop();
        level.pop();
        for (auto child : tren->children) {
            if(child!= nullptr)
                children.push(child);
            level.push(tren_level+1);
        }
        for(int i=0;i<tren->ID.size();i++)
        {
            if(ime==tren->customer[i]->first_name) {
                std::cout<<"U "<<tren_level<<" koraka se nasao: ";
                print_Node(tren, i);
            }
        }

    }
}
void BStarTree::k_search() {
    int k;
    std::cout<<"Napisite broj k:\n";
    std::cin>>k;
    std::vector<long long> ID;
    long long id1;
    std::cout<<"Napisite k kljuceva:\n";
    for(int i=0;i<k;i++)
    {
        std::cin>>id1;
        ID.push_back(id1);
    }
    int full_koraci=0;
    Node* element;
    for(int i=0;i<k;i++)
    {
        element=find_key(ID[i]);
        if(element)
            full_koraci+= koraci(element,ID[i]);
    }
    std::cout<<"Ukupan broj koraka je :"<<full_koraci<<std::endl;
}
int BStarTree:: koraci(Node* element,long long key)
{
    int korak=0;
    Node*parent=element->parent;
    while(parent!= nullptr)
    {
        korak++;
        parent=parent->parent;
    }
    int i=0;
    for(;i<element->ID.size();i++)
    {
        if(element->ID[i]==key)
            break;
    }
    print_Node(element,i);
    std::cout<<"broj koraka je bio:"<<korak<<std::endl;
    return korak;
}
void BStarTree::find_key_call(){
    long long key;
    std::cout<<"Napisite kljuc:\n";
    std::cin>>key;
    Node* element= find_key(key);
    if(!element)
    {
        std::cout<<"Element ne postoji!\n";
        return ;
    }
    koraci(element,key);
}
void BStarTree::delete_one() {
    std::cout<<"Napisite ID\n";
    long long key;
    std::cin>>key;
    Delete(key);
}
void BStarTree::insert_one() {
    long long key, ad_id;
    std::string first_name, last_name, email;
    std::cout<<"Napsite kljuc:\n";
    std::cin>>key;
    std::cout<<"Napsite ime:\n";
    std::cin>>first_name;
    std::cout<<"Napsite prezime:\n";
    std::cin>>last_name;
    std::cout<<"Napsite mail:\n";
    std::cin>>email;
    std::cout<<"Napsite kluc druge tabele:\n";
    std::cin>>ad_id;
    Customer* novi_kupac=new Customer(first_name,last_name,email,ad_id);
    Insert(key,novi_kupac);
}
void BStarTree::parser(std::ifstream &file) {
    std::string red;
    while (std::getline(file, red)) {
        std::istringstream red1(red);
        std::string token;

        long long key, ad_id;
        std::string first_name, last_name, email;

        std::getline(red1, token, '|');
        key = std::strtoll(token.c_str(), nullptr, 10);
        std::getline(red1,first_name,'|');
        std::getline(red1,last_name,'|');
        std::getline(red1,email,'|');

        std::getline(red1, token, '|');
        ad_id = std::strtoll(token.c_str(), nullptr, 10);
        Customer * customer=new Customer(first_name,last_name,email,ad_id);
        Insert(key,customer);
    }
}
void BStarTree::Print_keys()
{
    if (!root){
        std::cout<<"Stablo je prazno!\n";
        return;
    }
    std::queue<Node*> children;
    std::queue<int> level;
    children.push(root);
    level.push(0);

    Node* tren;
    int tren_level;
    while(!children.empty())
    {
        tren=children.front();
        tren_level=level.front();
        children.pop();
        level.pop();
        for (auto child : tren->children) {
            if(child!= nullptr)
                children.push(child);
            level.push(tren_level+1);
        }
        for(int i=0;i<tren->ID.size();i++)
        {
            print_tabs(tren_level);
            print_Node(tren,i);
        }

    }
}
BStarTree::BStarTree(int new_m) : m(new_m) {
    root=new Node(true);
    max_root = 2 * static_cast<int>(std::floor((2.0 * m - 2.0) / 3.0)) ;
    min_rest = static_cast<int>(std::ceil((2.0 * m - 1.0) / 3.0))-1;
    max_rest = m-1;
}
BStarTree::~BStarTree(){
    delete_Node(root);
}
void BStarTree::delete_Node(Node* node) {
    if (!node) return;
    std::stack<Node*> children;
    children.push(node);
    Node* tren;
    while(!children.empty())
    {
        tren=children.top();
        children.pop();
        for (auto child : tren->children) {
            if(child!= nullptr)
                children.push(child);
        }
        for (auto child : tren->customer) {
            delete(child);
        }
        delete(tren);
    }
}
Node* BStarTree::find_brother_delete(Node *element) {
    if(element->parent== nullptr)
        return nullptr;
    Node* tren=element->parent;
    int i=0;
    int n=tren->children.size();
    for(;i<n&&tren->children[i]!=element;i++);
    if(i+1<n &&  tren->children[i+1]->ID.size()>min_rest)
        return tren->children[i+1];

    if(i-1>=0&&tren->children[i+1]->ID.size()>min_rest)
        return tren->children[i-1];

    if(i+2<n&&tren->children[i+1]->ID.size()>min_rest)
        return tren->children[i+2];

    if(i-2>=0&&tren->children[i+1]->ID.size()>min_rest)
        return tren->children[i-2];
    return nullptr;
}
Node* BStarTree::find_brother_insert(Node *element) {
    if(element->parent== nullptr)
        return nullptr;
    Node* tren=element->parent;
    int i=0;
    int n=tren->children.size();
    for(;i<n&&tren->children[i]!=element;i++);
    if(i+1<n && tren->children[i+1]->ID.size()<max_rest)
        return tren->children[i+1];

    if(i-1>=0&&tren->children[i-1]->ID.size()<max_rest )
        return tren->children[i-1];

    if(i+2<n&&tren->children[i+2]->ID.size()<max_rest )
        return tren->children[i+2];

    if(i-2>=0&&tren->children[i-2]->ID.size()<max_rest)
        return tren->children[i-2];
    return nullptr;
}
void BStarTree::take_from_younger(Node* parent, int k, int j) {
    for(int z=j+1;z<=k;z++)
    {
        parent->children[z]->ID.insert(parent->children[z]->ID.begin(),parent->ID[z-1]);
        parent->children[z]->customer.insert(parent->children[z]->customer.begin(),parent->customer[z-1]);

        parent->ID[z-1]=parent->children[z-1]->ID[parent->children[z-1]->ID.size()-1];
        parent->customer[z-1]=parent->children[z-1]->customer[parent->children[z-1]->customer.size()-1];

        parent->children[z-1]->ID.pop_back();
        parent->children[z-1]->customer.pop_back();

        if(!parent->children[z-1]->leaf)
        {
            parent->children[z]->children.insert(parent->children[z]->children.begin(),parent->children[z-1]->children[parent->children[z-1]->children.size()-1]);
            parent->children[z-1]->children.pop_back();
            for(auto dete:parent->children[z]->children)
                dete->parent=parent->children[z];
        }

    }
}
void BStarTree::take_from_older(Node* parent, int k, int j) {
    for(int z=j-1;z>=k;z--)
    {
        parent->children[z]->ID.insert(parent->children[z]->ID.end(),parent->ID[z]);
        parent->children[z]->customer.insert(parent->children[z]->customer.end(),parent->customer[z]);

        parent->ID[z]=parent->children[z+1]->ID[0];
        parent->customer[z]=parent->children[z+1]->customer[0];

        parent->children[z+1]->ID.erase(parent->children[z+1]->ID.begin());
        parent->children[z+1]->customer.erase(parent->children[z+1]->customer.begin());

        if(!parent->children[z+1]->leaf)
        {
            parent->children[z]->children.push_back(parent->children[z+1]->children[0]);
            parent->children[z+1]->children.erase(parent->children[z+1]->children.begin());
            for(auto dete:parent->children[z]->children)
                dete->parent=parent->children[z];
        }
    }
}
void BStarTree::giving(Node *tren,Node *brat){
    Node* parent=tren->parent;

    int k=0;
    for(;k<parent->children.size()&&brat!=parent->children[k];k++);
    int j=0;
    for(;j<parent->children.size()&&tren!=parent->children[j];j++);

    if(j<k)
    {
        take_from_younger(parent,k,j);
    }
    else
    {
        take_from_older(parent,k,j);
    }
}
void BStarTree::propagacija_na_gore(Node *element) {
    Node* tren=element;
    if(tren==root){
        int i=max_root/2;
        Node* new_root=new Node(false);
        Node* brat= new Node(tren->leaf);
        tren->parent=new_root;
        brat->parent=new_root;
        new_root->ID.push_back(tren->ID[i]);
        new_root->customer.push_back(tren->customer[i]);
        i++;
        new_root->children.push_back(tren);
        new_root->children.push_back(brat);
        root=new_root;
        if(!tren->leaf)
        {
            int k=tren->children.size()/2;
            for(int j=k;j<tren->children.size();j++)
            {
                brat->children.push_back(tren->children[j]);
            }
            for(auto child:brat->children){
                child->parent=brat;
            }
            while(tren->children.size()>k)
                tren->children.erase(tren->children.end()-1);

            for(auto child:tren->children){
                child->parent=tren;
            }
        }
        for(;i<tren->ID.size();i++)
        {
            brat->ID.push_back(tren->ID[i]);
            brat->customer.push_back(tren->customer[i]);

        }
        while(tren->ID.size()>max_root/2)
        {
            tren->ID.erase(tren->ID.end()-1);
            tren->customer.erase(tren->customer.end()-1);

        }


    }
    else {
        bool new_leaf = tren->leaf;
        Node *brother = new Node(new_leaf);
        brother->parent=tren->parent;
        Node *parent = tren->parent;
        int i = 0;
        for (; i < parent->children.size() && parent->children[i] != tren; i++);
        int j = i < parent->children.size() - 1 ? i + 1 : i - 1;
        if (i > j) {
            i = j;
            j = i + 1;
        }
        std::vector<long long> ID;
        std::vector<Customer*> customer;
        std::vector<Node *> sinovi;
        for (auto ID_child: parent->children[i]->ID) {
            ID.push_back(ID_child);
        }
        for (auto customer_child: parent->children[i]->customer) {
            customer.push_back(customer_child);
        }
        ID.push_back(parent->ID[i]);
        customer.push_back(parent->customer[i]);

        for (auto ID_child: parent->children[j]->ID) {
            ID.push_back(ID_child);
        }
        for (auto customer_child: parent->children[j]->customer) {
            customer.push_back(customer_child);
        }
        if (!tren->leaf) {
            for (auto ID_child: parent->children[i]->children) {
                sinovi.push_back(ID_child);
            }

            for (auto ID_child: parent->children[j]->children) {
                sinovi.push_back(ID_child);
            }
        }
        parent->children[i]->ID.clear();
        parent->children[i]->customer.clear();
        parent->children[i]->children.clear();
        parent->children[j]->ID.clear();
        parent->children[j]->customer.clear();
        parent->children[j]->children.clear();
        int numb1 = static_cast<int>(std::floor((2.0 * m - 2.0) / 3.0));
        int numb2 = static_cast<int>(std::floor((2.0 * m - 1.0) / 3.0));
        for (int k = 0; k < numb1; k++) {
            parent->children[i]->ID.push_back(ID[k]);
            parent->children[i]->customer.push_back(customer[k]);
        }
        parent->ID[i] = ID[numb1];
        parent->customer[i] = customer[numb1];
        for (int k = numb1 + 1; k < numb1 + 1 + numb2; k++) {
            brother->ID.push_back(ID[k]);
            brother->customer.push_back(customer[k]);
        }
        for (int k = numb1 + 2 + numb2; k < ID.size(); k++) {
            parent->children[j]->ID.push_back(ID[k]);
            parent->children[j]->customer.push_back(customer[k]);
        }
        parent->ID.insert(parent->ID.begin() + i + 1, ID[numb1 + numb2 + 1]);
        parent->customer.insert(parent->customer.begin() + i + 1, customer[numb1 + numb2 + 1]);
        if (!tren->leaf) {
            for (int k = 0; k < numb1 + 1; k++) {
                parent->children[i]->children.push_back(sinovi[k]);
            }
            for(auto child:parent->children[i]->children)
                child->parent=parent->children[i];
            for (int k = numb1 + 1; k < numb1 + 2 + numb2; k++) {
                brother->children.push_back(sinovi[k]);
            }
            for(auto child:brother->children)
                child->parent=brother;
            for (int k = numb1 + 2 + numb2; k < sinovi.size(); k++) {
                parent->children[j]->children.push_back(sinovi[k]);
            }
            for(auto child:parent->children[j]->children)
                child->parent=parent->children[j];
        }
        parent->children.insert(parent->children.begin() + i + 1, brother);

    }

}

void BStarTree::Insert(long long key,Customer* customer){
    Node* tren=root;
    while(!tren->leaf){
        int i=0;
        for(;i<tren->ID.size()&&key>tren->ID[i];i++);
        tren=tren->children[i];
    }

    int doz_velicina=root==tren?max_root:max_rest;
    int i=0;
    for(;i<tren->ID.size()&&key>tren->ID[i];i++);
    tren->ID.insert(tren->ID.begin()+i,key);
    tren->customer.insert(tren->customer.begin()+i,customer);
    while(tren->ID.size()>doz_velicina) {
        Node* brat= find_brother_insert(tren);
        if (brat == nullptr) {
            propagacija_na_gore(tren);
            tren = tren->parent;
            doz_velicina = root == tren ? max_root : max_rest;

        } else {
            giving(tren, brat);
        }

    }
}
Node* BStarTree::find_key(long long key){
    Node* tren=root;
    while(tren!= nullptr)
    {
        int i=0;
        for(;i<tren->ID.size();i++)
        {
            if(key<=tren->ID[i])
                break;
        }
        if (tren->ID[i]==key)
        {
            return tren;
        }
        else if(!tren->leaf)
        {
            tren=tren->children[i];
        }
        else{
            return nullptr;
        }
    }
    return nullptr;
}
void BStarTree::merge3(Node* parent, int i) {
    Node* child=parent->children[i];
    Node* sibling1=parent->children[i+1];
    Node* sibling2=parent->children[i+2];
    std::vector<Node*> sinovi;
    std::vector<long long>ID;
    std::vector<Customer*>customer;
    for(auto ID1:child->ID)
        ID.push_back(ID1);
    for(auto child_customer:child->customer)
        customer.push_back(child_customer);
    ID.push_back(parent->ID[i]);
    customer.push_back(parent->customer[i]);

    for(auto ID1:sibling1->ID)
        ID.push_back(ID1);
    for(auto sibling_customer:sibling1->customer)
        customer.push_back(sibling_customer);

    ID.push_back(parent->ID[i+1]);
    customer.push_back(parent->customer[i+1]);

    for(auto ID1:sibling2->ID)
        ID.push_back(ID1);
    for(auto sibling_customer:sibling2->customer)
        customer.push_back(sibling_customer);
    if(!child->leaf)
    {
        for(auto ID1:child->children)
            sinovi.push_back(ID1);

        for(auto ID1:sibling1->children)
            sinovi.push_back(ID1);

        for(auto ID1:sibling2->children)
            sinovi.push_back(ID1);
    }
    child->ID.clear();
    sibling1->ID.clear();
    child->customer.clear();
    sibling1->customer.clear();
    child->children.clear();
    sibling1->children.clear();
    delete sibling2;
    parent->children.erase(parent->children.begin()+i+2);
    parent->ID.erase(parent->ID.begin()+i+1);
    parent->customer.erase(parent->customer.begin()+i+1);

    int half=ID.size()/2;
    for(int j=0;j<half;j++)
    {
        child->ID.push_back(ID[j]);
        child->customer.push_back(customer[j]);

    }
    parent->ID[i]=ID[half];
    parent->customer[i]=customer[half];

    for(int j=half+1;j<ID.size();j++)
    {
        sibling1->ID.push_back(ID[j]);
        sibling1->customer.push_back(customer[j]);

    }
    if(!child->leaf)
    {
        int full=sinovi.size();
        int half1=full/2;
        for(int j=0;j<half1;j++)
        {
            child->children.push_back(sinovi[j]);
        }

        for(int j=half1;j<full;j++)
        {
            sibling1->children.push_back(sinovi[j]);
        }
        for(auto dete:child->children)
            dete->parent=child;

        for(auto dete:sibling1->children)
            dete->parent=child;
    }
}
void BStarTree::merge2(Node* parent, int i) {
    Node* child = parent->children[i];
    Node* sibling = parent->children[i + 1];

    child->ID.push_back(parent->ID[i]);
    child->customer.push_back(parent->customer[i]);

    for (auto key : sibling->ID) {
        child->ID.push_back(key);
    }
    for (auto customer : sibling->customer) {
        child->customer.push_back(customer);
    }
    if (!child->leaf) {
        for (Node* childNode : sibling->children) {
            child->children.push_back(childNode);
        }
        for(auto dete:child->children)
            dete->parent=child;
    }

    parent->ID.erase(parent->ID.begin() + i);
    parent->customer.erase(parent->customer.begin() + i);
    parent->children.erase(parent->children.begin() + i + 1);

    delete sibling;
}
void BStarTree::merge(Node* element){
    if(element==root)
    {
        if(!element->leaf&&element->children.size()>0)
        {
            root=element->children[0];
            root->parent= nullptr;
            delete element;
        }
        return;
    }
    int i=0;
    Node*parent=element->parent;
    for(;parent->children[i]!=element;i++);
    if(parent->children.size()==2)
    {
        merge2(parent,0);
    }
    else
    {
        if(i==0)
            merge3(parent,i);
        else if(i==parent->children.size()-1)
            merge3(parent,i-2);
        else
            merge3(parent,i-1);
    }
}
void BStarTree::Delete(long long key) {
    Node* element= find_key(key);
    if(element== nullptr)
    {
        std::cout<<"Ovaj kljuc ne postoji\n";
        return;
    }

    int place=0;
    for(;place<element->ID.size()&&element->ID[place]<key;place++);
    if(!element->leaf)
    {

        Node*tren=element->children[place+1];
        while(!tren->leaf)
        {
            tren=tren->children[0];
        }
        element->ID[place]=tren->ID[0];
        Customer* t=element->customer[place];
        element->customer[place]=tren->customer[0];
        tren->ID[0]=key;
        tren->customer[0]=t;
        element=tren;
        place=0;
    }
    element->ID.erase(element->ID.begin()+place);
    delete(element->customer[place]);
    element->customer.erase(element->customer.begin()+place);
    int doz_velicina=root==element?min_root:min_rest;
    while(element->ID.size()<doz_velicina&&element!=root)
    {
        Node* brat= find_brother_delete(element);
        if(brat!= nullptr)
        {
            giving(brat,element);
        }
        else
        {
            merge(element);
            element=element->parent;
            doz_velicina=root==element?min_root:min_rest;
        }
    }
    if(element==root && doz_velicina>element->ID.size())
        merge(element);
}