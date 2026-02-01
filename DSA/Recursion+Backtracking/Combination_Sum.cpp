class Solution {
public:
    void solve(vector<vector<int>>&ans, vector<int>&arr,int target, vector<int>&candidates,int index,int &sum){
            if(sum==target){
                ans.push_back(arr);
                return; 
            }
            else if(sum>target){
                return; 
            }
        for(int i =index;i<candidates.size(); i++){
            // we have the option to include candidate[index] multiple tiems
            sum+=candidates[i]; 
            arr.push_back(candidates[i]); 
            solve(ans,arr,target,candidates,i,sum); 
            sum-=arr.back() ;
            arr.pop_back(); 
           // solve(ans,arr,target,candidates,i+1,sum); 
        }
        return; 
            
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans; 
        vector<int>arr; 
        int sum=0; 
        int index=0; 
        solve(ans,arr,target,candidates,index,sum) ;
        return ans ; 
    }
};
