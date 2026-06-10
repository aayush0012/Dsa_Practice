class Solution {
  public:
  void insert(stack<int>&st,int x){
      if(st.empty() || x>=st.top()){
          st.push(x);
          return; 
      } 
    int var = st.top(); 
    st.pop();
    insert(st,x) ;
    st.push(var); 
    return; 
  }
  void sort(stack<int>&st){
     if(st.size()==1)return ;
     int top = st.top(); 
     st.pop(); 
     sort(st);
     insert(st,top); 
     return  ; 
  }
    void sortStack(stack<int> &st) {
        sort(st); 
        
    }
};
