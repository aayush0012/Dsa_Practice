class Solution {
  public:
 int solve(vector<int>& nums, int index,
        vector<vector<int>>& dp, int last) {
        if(index == nums.size()) {
            return 0;
        }
        if(dp[index][last+1] != 0)
            return dp[index][last+1];
        int take = 0;
        if(last==-1 || nums[index]>nums[last]) {
            take = 1 + solve(nums, index + 1, dp, index);
        }
        int leave = solve(nums, index + 1, dp, last);
        return dp[index][last+1] = max(take,leave) ; 
        
      }
      // dp state-> take = 1+dp[i+1][i] ;
      // leave = dp[i+1][j]; 
        
    vector<int> getLIS(vector<int>& arr) {
        // Code here
        int n = arr.size(); 
        vector<vector<int>>dp(n+1,vector<int>(n+1,0)); 
        for(int index = n-1; index>=0; index--){
            for(int last=n;last>=-1; last--){
                int take =0;
                int leave =0 ;
                if(last==-1 || arr[index]>arr[last]){
                    take = 1+dp[index+1][index+1]; 
                }
                leave = dp[index+1][last+1];
                dp[index][last+1]=max(take,leave); 
            }
            
        }
         
    }
};
