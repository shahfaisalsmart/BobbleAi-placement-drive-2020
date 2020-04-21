/*
    Problem 2: Swap to type

    Name:: Mohammad Faisal
    Date:: 21/04/2020

    Email:: mohammad.faisal78612@gmail.com
 
*/

// #include<bits/stdc++.h>
#include<fstream>
#include <sstream>
#include<pair>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<string>
#include<map>

using namespace std;

#define sz (26)

#define toInt(ch) ((int)ch - (int)'A')
#define lop(i,n) for(int i=0;i<n;i++)


//int row=0, col=0;
vector<string> answer;
struct trie
{
    trie *child[sz];

    bool leaf;
};

trie *newNode(){
    trie* node = new trie;
    node->leaf = false;
    for(int ind=0;ind<sz;ind++){
        node->child[ind] = NULL;
    }
    return node;
}

void insertion(trie *root, string val){
    
    int n = (int)val.size();

    trie *tempChild = root;

    lop(i,n){
        
        int ind = toInt(val[i]);

        if(tempChild->child[ind]==NULL){
            tempChild->child[ind] = newNode();
        }

        tempChild = tempChild->child[ind];
    }
    tempChild->leaf = true;
}

bool isValid(int i, int j, vector<vector<bool>> visited, int row, int col){
    
    return (i>=0 && i<row && j>=0 && j<col && !visited[i][j]);
}

void solve(trie *root, vector<vector<char>> mat, int i, int j,vector<vector<bool>> visited, string str,int row, int col){
    
    if(root->leaf){
        answer.push_back(str);
    }
    
    if(isValid(i,j,visited,row, col)){
        visited[i][j] = true;
        lop(ind,sz){
            if(root->child[ind]!=NULL){

                char ch = (char)ind + (char)'A';

                if(isValid(i-1,j,visited,row, col) && mat[i-1][j] == ch)
                {
                    solve(root->child[ind],mat,i-1,j,visited,str+ch,row, col);
                }
                if(isValid(i-1,j-1,visited,row, col) && mat[i-1][j-1] == ch)
                {
                    solve(root->child[ind],mat,i-1,j-1,visited,str+ch,row, col);
                }
                if(isValid(i,j-1,visited,row, col) && mat[i][j-1] == ch)
                {
                    solve(root->child[ind],mat,i,j-1,visited,str+ch,row, col);
                }
                if(isValid(i+1,j-1,visited,row,col) && mat[i+1][j-1] == ch)
                {
                    solve(root->child[ind],mat,i+1,j-1,visited,str+ch,row, col);
                }
                if(isValid(i+1,j,visited,row,col) && mat[i+1][j] == ch)
                {
                    solve(root->child[ind],mat,i+1,j,visited,str+ch,row,col);
                }
                if(isValid(i-1,j+1,visited,row,col) && mat[i-1][j+1] == ch)
                {
                    solve(root->child[ind],mat,i-1,j+1,visited,str+ch,row,col);
                }
                if(isValid(i,j+1,visited,row,col) && mat[i][j+1] == ch)
                {
                    solve(root->child[ind],mat,i,j+1,visited,str+ch,row,col);
                }
                if(isValid(i+1,j+1,visited,row, col) && mat[i+1][j+1] == ch)
                {
                    solve(root->child[ind],mat,i+1,j+1,visited,str+ch,row,col);
                }
            }
        }
        visited[i][j] = true;
    }
}

void Nearest(vector<vector<char>> mat, trie *root){
//    bool visited[row][col];
    vector<vector<bool>> visited;
    lop(i,(int)mat.size()){
        vector<bool> tempVisited;
    lop(j,(int)mat[i].size()){
        tempVisited.push_back(false);
    }
        visited.push_back(tempVisited);
    }
    
    trie *tempChild = root;

    string ans = "";

    lop(i,(int)mat.size()){
        int leftBoundary = (int)mat.size();
        lop(j,(int)mat[i].size()){
            int rightBoundary = (int)mat[i].size();
            if(tempChild->child[toInt(mat[i][j])]){
                ans = ans + mat[i][j];
                solve(tempChild->child[toInt(mat[i][j])], mat, i, j, visited, ans,leftBoundary, rightBoundary);
                ans = "";
            }
        }
    }

}

int main()
{
    
    ifstream ip("EnglishDictionary.csv");
    
    if(!ip.is_open())
        cout<<"Error.... File is damaged. :("<<endl;
    
    string words;
    string freq;
    unordered_map<string, int> dict;

    while(ip.good()){
        
        getline(ip,words,' ');
        getline(ip,freq,'\n');
        
        stringstream geek(freq);
        int num = 0;
        geek >> num;
        
        dict[words] = num;
    }
    
    trie * root = newNode();

//    int len = sizeof(dict)/sizeof(dict[0]);

    for(auto &k: dict){
        string t = k.first;
        insertion(root,t);
    }
    
    string inp;
    cin >> inp;
    
    transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
    
    
    vector<vector<char>> mat;
    
    
    // filling default values
    vector<char> arr;
    
    for(int i='a'; i<='z';i++){
        arr.push_back((char)i);
    }
    mat.push_back(arr);
    arr.clear();
    
    lop(i,(int)inp.size()){
        arr.push_back((char)inp[i]);
    }
    mat.push_back(arr);
    arr.clear();
    
    lop(i,(int)inp.size()){
        arr.push_back((char)inp[i]);
    }
    mat.push_back(arr);
    arr.clear();
    
    for(int i='a'; i<='z';i++){
        arr.push_back((char)i);
    }
    mat.push_back(arr);
    arr.clear();

    Nearest(mat,root);
    
    vector<pair<int,string>> finalAnswer;
    for(auto &ind: answer){
        finalAnswer.push_back(make_pair(dict[ind],ind));
    }
    
    stable_sort(finalAnswer.begin(),finalAnswer.end());
    
    
    
    // BEST FIVE NEAREST INTEGERS
    
    int cnt=0;
    for(auto &k: finalAnswer){
        
        if(cnt==5){
            break;
        }
        cout<<k.second<<" ";
        cnt++;
    }
    return 0;
}








