//
// Created by Stefan Grujicic on 16.11.24..
//
#ifndef UNTITLED14_B_STAR_TREE_H
#define UNTITLED14_B_STAR_TREE_H
#include <cmath> // Za ceil i floor
#include <iostream>
#include <vector>
#include<string>
#include<stack>
#include<algorithm>
#include <fstream>
#include <sstream>
#include<queue>
struct Customer{
    std::string first_name;
    std::string second_name;
    std::string email;
    long long AD_ID;
    Customer(const std::string& fName, const std::string& lName, const std::string& mail, int adID)
            : first_name(fName), second_name(lName), email(mail), AD_ID(adID) {}
};

struct Node{

    std::vector<long long> ID;
    std::vector<Customer*> customer;
    std::vector<Node*> children;
    bool leaf;
    Node* parent;
    explicit Node(bool isleaf):leaf(isleaf),parent(nullptr){}

};

class BStarTree{
public:

    explicit BStarTree(int new_m);

    ~BStarTree();

    void parser(std::ifstream& file);

    void print_Node(Node* tren,long long i){
        if(!tren)
            return;
        std::cout<<tren->ID[i]<<"|"<<tren->customer[i]->first_name<<"|"<<tren->customer[i]->second_name<<"|"<<tren->customer[i]->email<<"|"<<tren->customer[i]->AD_ID<<std::endl;

    }
    void print_tabs(int number){
        for(int i=0;i<number;i++)
        {
            std::cout<<"\t";
        }
    }
    void propagacija_na_gore(Node* element);

    void merge(Node* element);

    void merge2(Node* parent,int i);

    void merge3(Node* parent,int i);

    Node* find_key(long long key);

    void take_from_younger(Node* parent,int k,int j);

    void take_from_older(Node* parent,int k,int j);

    void insert_one();

    void delete_one();

    void Insert(long long key,Customer* customer);

    void Delete(long long key);

    void giving(Node *tren,Node *brat);

    void Print_keys();

    void find_key_call();

    int koraci(Node* element,long long key);

    void k_search();
    void find_name();

private:
    Node* root;
    void delete_Node(Node* node);
    Node* find_brother_insert(Node* element);
    Node*find_brother_delete(Node*element);
    int m;
    int min_root=1;
    int max_root;
    int min_rest;
    int max_rest;
};
#endif //UNTITLED14_B_STAR_TREE_H
